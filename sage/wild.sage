#!/usr/bin/env sage

import sys

q=7
m=3
n=228
s=12
t=2

if 1 < len(sys.argv): q = int(sys.argv[1])
if 2 < len(sys.argv): m = int(sys.argv[2])
if 3 < len(sys.argv): n = int(sys.argv[3])
if 4 < len(sys.argv): s = int(sys.argv[4])
if 5 < len(sys.argv): t = int(sys.argv[5])

u = s + (q-1)*t
k = n - m*u
w = floor((s + q*t)/2)

print "kilobytes =",k*(n-k)*log(q*1.0)/(1024*log(256.0))
print "q =",q
print "m =",m
print "n =",n
print "s =",s
print "t =",t
print "u =",u
print "k =",k
print "w =",w

Fq.<genq> = GF(q)
Fqm.<genqm> = GF(q^m)
Fqmx.<x> = Fqm[]

embed = genq.charpoly().roots(Fqm,False)[0]

p = Fq.characteristic()
Fp = GF(p)
logpq = Fq.degree()

embed = genq.charpoly().roots(Fqm,False)[0]

Fmap = [Fqm(genqm^i*embed^j)._vector_().list() for i in range(m) for j in range(logpq)]
Fmapinv = MatrixSpace(Fp,m*logpq,m*logpq)(Fmap).inverse()

if p == q:
  def Fqembed(u):
    return Fqm(u)
else:
  def Fqembed(u):
    # Fq -> Fqm defined by genq |-> embed
    v = u._vector_().list()
    return sum([v[i]*embed^i for i in range(logpq)])

if p == q:
  def Fqvector(u):
    return u._vector_().list()
else:
  def Fqvector(u):
    # return [c0,c1,...,c[m-1]], vector over Fq
    # such that u = c0 + genqm c1 + ... + genqm^(m-1) c[m-1]
    # where Fq -> Fqm is defined by genq |-> embed
    v = u._vector_() * Fmapinv
    return [sum([v[j*logpq+i]*genq^i for i in range(logpq)]) for j in range(m)]

def Fqunembed(u):
  return Fqvector(u)[0]

def myirred(f):
  return f.is_irreducible()

tries = 0
while True:
  a = []
  while len(a) < n:
    ai = Fqm.random_element()
    if not ai in a: a.append(ai)

  def badroots(g):
    for ai in a:
      if g(ai) == 0: return 1
    return 0

  if s == 0:
    f = 1
  else:
    while True:
      f = x^s + Fqmx.random_element(s-1)
      if myirred(f) and not badroots(f): break

  if t == 0:
    g = 1
  else:
    while True:
      g = x^t + Fqmx.random_element(t-1)
      if myirred(g) and not badroots(g): break
      
  def mypower(ai,d):
    if d == 0: return Fqm(1)
    return ai^d
    # some sage nitwit raises exception for GF(...)(0)^0
  
  apower = [[mypower(ai,d) for d in range(u)] for ai in a]

  goppa = f*g^(q-1)
  biggoppa = f*g^q
  u = goppa.degree()
  goppaval = [1/goppa(ai) for ai in a]
  Hshort = [ [j for d in range(u) for j in Fqvector(apower[i][d]*goppaval[i])] for i in range(m*u)]

  if MatrixSpace(Fq,m*u,m*u)(Hshort).is_invertible(): break
  tries += 1
  if tries >= 20: exit(111)
  

H = [ [j for d in range(u) for j in Fqvector(apower[i][d]*goppaval[i])] for i in range(n)]
M = MatrixSpace(Fq,n,m*u)(H)
Mt = M.transpose()
E = Mt.echelon_form()
T = Mt.solve_left(E)
publickey = [E[i][m*u:n] for i in range(m*u)]


plaintext = [Fq(0) for i in range(n)]
for i in range(w):
  while True:
    r = randrange(0,n)
    if plaintext[r] == 0: break
  while True:
    plaintext[r] = Fq.random_element()
    if plaintext[r] != 0: break


ciphertext = [plaintext[i] + sum([publickey[i][j-m*u] * plaintext[j] for j in range(m*u,n)]) for i in range(m*u)]
print "ciphertext =",ciphertext
sys.stdout.flush()


v = M.solve_left(T.inverse() * vector(ciphertext)).list()

# one way to retrospectively check for codeword:
# c = [v[i] - plaintext[i] for i in range(n)]
# Fqmxh.<xmodgoppa> = Fqmx.quotient(goppa)
# print sum([c[i]/(xmodgoppa - a[i]) for i in range(n)])

def fastsum(q):
  if len(q) == 0: return 0
  if len(q) == 1: return q[0]
  cutoff = floor(len(q) / 2)
  first = fastsum(q[0:cutoff])
  second = fastsum(q[cutoff:len(q)])
  return [first[0]*second[1]+first[1]*second[0],first[1]*second[1]]

h = prod(x-ai for ai in a)
dh = h.derivative()
q = [[Fqembed(v[i])/biggoppa(a[i]),x-a[i]] for i in range(n)]
phi = fastsum(q)[0]

def eea(u1,u2,deg): 
  l0 = vector([u1,1,0])
  l1 = vector([u2,0,1])
  while l1[0].degree() >= deg:
    l2 = l0-(l0[0]//l1[0])*l1
    l0 = l1
    l1 = l2
  return l1

l = eea(h,phi,n-w)
v0 = l[1]
v1 = -l[2]
f = phi*biggoppa-((v0*h*biggoppa)//v1)

decipheredtext = [v[i] - Fqunembed(f(a[i])/dh(a[i])) for i in range(n)]

print "recovered_plaintext_using_secret_key =",decipheredtext == plaintext


for j in range(0,n-m*u):
  print "pubkeycol"+str(j+m*u),"=",[publickey[i][j] for i in range(m*u)]
