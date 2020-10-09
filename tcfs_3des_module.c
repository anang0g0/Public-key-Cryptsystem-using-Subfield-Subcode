#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/kerneld.h>
#include <linux/module.h>
#include <linux/malloc.h>
#include <linux/kdes.h>
#include <linux/tcfs/tcfsapi.h>

static void *init_key (char *key)
{
	des_key_schedule *ks;

	ks=(des_key_schedule *)kmalloc (2*sizeof (des_key_schedule), GFP_KERNEL);
	if (!ks) {
		printk ("TCFS: unable to get a free page\n");
		return NULL;
	}

	des_set_key ((des_cblock *)key, ks[0]);
	des_set_key ((des_cblock *)(key+8), ks[1]);

	return (void *)ks;
}

static void mkendes(char *block, int nb, void *key)
{
	unsigned long * xi;
	int i;
	char *tmp;
	des_key_schedule *ks=(des_key_schedule *)key;

#ifdef TCFS_DEBUG
	{       
                int i;  
                char *pnt;
    
		printk("TCFS_debug: in mkendes\n");
                printk("TCFS_debug: input key: ");
    
                pnt=(char *)&ks[0];
                for(i=0;i<16;i++,pnt++){
                        printk("%x:",(unsigned int)*pnt);
                }       
    		printk("\n");
	} 
#endif

	xi=(long *)block;
	tmp=block;
	des_ecb_encrypt((des_cblock *)tmp,(des_cblock *)tmp, ks,DES_ENCRYPT);
	tmp+=8;
	for (i=1;i<nb/8;i++) {
		*(xi+2)^=*xi;
		*(xi+3)^=*(xi+1);
		des_ecb_encrypt((des_cblock *)tmp,(des_cblock *)tmp,ks,DES_ENCRYPT);
		tmp+=8;
		xi+=2;
	}
#ifdef TCFS_DEBUG
	printk ("TCFS_debug: exiting mkendes\n");
#endif
}

static void mkdedes(char *block, int nb, void *key)
{
	unsigned long * xi,xo[2],xa[2];
	int i;
	char *tmp;
	des_key_schedule *ks=(des_key_schedule *)key;

	xi=(long *)block;
	tmp=block;
	xo[0]=*xi; xo[1]=*(xi+1);
	des_ecb_encrypt((des_cblock *)tmp,(des_cblock *)tmp,ks,DES_DECRYPT);
	tmp+=8;
	xi=(long *)tmp;
	for (i=1;i<nb/8;i++) {
		xa[0]=*xi; xa[1]=*(xi+1);
		des_ecb_encrypt((des_cblock *)tmp,(des_cblock *)tmp,ks,DES_DECRYPT);
		*(xi)^=xo[0];
		*(xi+1)^=xo[1];
		xo[0]=xa[0];  
		xo[1]=xa[1];
		tmp+=8;
		xi+=2;
	}
}

static struct tcfs_cipher_operations tcfs_default_ops = {
	init_key,
	NULL,
	mkendes,
	mkdedes
};

int
init_module (void)
{
	tcfs_register_cipher ("default", &tcfs_default_ops);

	return 0;
}

void
cleanup_module (void)
{

	tcfs_unregister_cipher ("default");

	return ;
}
