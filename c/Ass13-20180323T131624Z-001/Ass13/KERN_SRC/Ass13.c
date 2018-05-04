/*
===============================================================================
Driver Name		:		Ass13
Author			:		HONEY
License			:		GPL
Description		:		LINUX DEVICE DRIVER PROJECT
===============================================================================
*/

#include"Ass13.h"
#include<linux/cdev.h>
#include<linux/kdev_t.h>
#include<linux/circ_buf.h>
#include<linux/slab.h>
#include<linux/uaccess.h>
#include<linux/fs.h>
#include<linux/wait.h>
#include<linux/sched.h>
#include<linux/ioctl.h>
#include"mygioctl.h"


MODULE_LICENSE("GPL");
MODULE_AUTHOR("HONEY");
#define DEVMINORS 3
#define CBUFFSIZE 256
struct md {
	int minor;
	struct cdev dev;
	struct circ_buf kcbuff;
	wait_queue_head_t wtq;
};
dev_t first;

struct md device[DEVMINORS];
struct md *devp;
int open(struct inode *inode, struct file *file) 
{
	//TODO Auto-generated function stub

	PINFO("In  open() function");
	devp=container_of(inode->i_cdev,struct md,dev);
	file->private_data=devp;


	return 0;
}

ssize_t read(struct file *file, char *ubuff, size_t count, loff_t *loff)
{
	int i,a;
	char ch;
	struct md *cdevp;
	pr_info("In read fn\n");
	cdevp = file->private_data;
		wait_event_interruptible(cdevp->wtq,CIRC_CNT(cdevp->kcbuff.head,cdevp->kcbuff.tail,CBUFFSIZE));

		a=min(CIRC_CNT(cdevp->kcbuff.head,cdevp->kcbuff.tail,CBUFFSIZE),(int)count);
			printk(" a value in read is %d", a);
	for (i=0;i<a;i++){
		if (CIRC_CNT(cdevp->kcbuff.head,cdevp->kcbuff.tail,CBUFFSIZE)>=1){
			ch=cdevp->kcbuff.buf[cdevp->kcbuff.tail];
		//	pr_info("%c",ch);
			cdevp->kcbuff.tail=(cdevp->kcbuff.tail+1)&(CBUFFSIZE-1);
		}
	copy_to_user(&ubuff[i],&ch,1);
}
return a;
}

ssize_t write(struct file *file, const char *ubuff, size_t count, loff_t *loff)
{
	//TODO Auto-generated function stub
	int i,a;
	char ch;
	struct md *cdevp;
	PINFO("In write() function");
	cdevp = file->private_data;

		a=min(CIRC_SPACE(cdevp->kcbuff.head,cdevp->kcbuff.tail,CBUFFSIZE),(int)count);
			printk(" a value in read is %d", a);
	for (i=0;i<a;i++){
		copy_from_user(&ch,&ubuff[i],1);

		if (CIRC_SPACE(cdevp->kcbuff.head,cdevp->kcbuff.tail,CBUFFSIZE)>=1){
			cdevp->kcbuff.buf[cdevp->kcbuff.head]=ch;
		//	pr_info("%c",ch);
			cdevp->kcbuff.head=(cdevp->kcbuff.head+1)&(CBUFFSIZE-1);
		}
	}
	wake_up_interruptible(&cdevp->wtq);
	return a;

}

int close(struct inode *inode, struct file *file) 
{
	//TODO Auto-generated function stub

	PINFO("In close() function");

	return 0;
}

long int ioctl(struct file *filp, unsigned int cmd, unsigned long int arg)
{
	int ret,disp,i,headnew,tailnew;
		struct md *cdevp;
		pr_info("In ioctl function");
		cdevp=filp->private_data;
		switch(cmd){
		case BUF_CNT:
			pr_info("In BUF_CNT");
			ret=__put_user(CIRC_CNT(cdevp->kcbuff.head,cdevp->kcbuff.tail,CBUFFSIZE),(int __user*)arg);
			break;
		case BUF_CLR:
			pr_info("In BUF_CLR");
			if (!capable(CAP_SYS_ADMIN))
				return -EPERM;
			cdevp->kcbuff.head=cdevp->kcbuff.tail=0;
			memset(cdevp->kcbuff.buf,'\0',CBUFFSIZE);
			break;
		case BUF_DISP:
			pr_info("In BUF_DISP");
			disp=CIRC_CNT(cdevp->kcbuff.head,cdevp->kcbuff.tail,CBUFFSIZE);
			headnew=cdevp->kcbuff.head;
			tailnew=cdevp->kcbuff.tail;
			for (i=0;i<disp;i++) {
				pr_info("%c",cdevp->kcbuff.buf[tailnew]);
				tailnew=(tailnew+1) & (CBUFFSIZE-1);
			}
	}
		return 0;
}

struct file_operations fops = {
		.owner=THIS_MODULE,
		.open=open,
		.read=read,
		.write=write,
		.unlocked_ioctl=ioctl,
		.release=close
};


static int __init Ass13_init(void)
{
	/* TODO Auto-generated Function Stub */
	int i;
	dev_t curr_dev;

		if (alloc_chrdev_region(&first,0,DEVMINORS,"muldevice")!=0) {
				printk("Failed to allocate device numbers\n");
				return -EFAULT;
		}
		for (i=0;i<DEVMINORS;i++) 
		{
			cdev_init(&device[i].dev,&fops);
			device[i].kcbuff.buf=( char *)kmalloc(CBUFFSIZE,GFP_KERNEL);
			init_waitqueue_head(&device[i].wtq);

			curr_dev=MKDEV(MAJOR(first),MINOR(first)+i);
			pr_info(" Major num: %d\tMinor num: %d\n", MAJOR(curr_dev),MINOR(curr_dev));
			if (cdev_add(&device[i].dev,curr_dev,1)!=0) {
				printk("Error in adding devices to kernel\n");
				return -EFAULT;
			}
		}
		return 0;
}

static void __exit Ass13_exit(void)
{	
	int i;
	/* TODO Auto-generated Function Stub */
	for (i=0;i<DEVMINORS;i++) {
		kfree(device[i].kcbuff.buf);
		cdev_del(&device[i].dev);
	}
	unregister_chrdev_region(first,DEVMINORS);
}

module_init(Ass13_init);
module_exit(Ass13_exit);

