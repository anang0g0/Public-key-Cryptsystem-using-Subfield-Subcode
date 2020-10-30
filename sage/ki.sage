BIN.<X> = GF(16)[]
B.<X> = GF(2)[]
while 1:
      poly = B.random_element(8);
      if poly.is_irreducible():
      	 break;
print(poly)
 
