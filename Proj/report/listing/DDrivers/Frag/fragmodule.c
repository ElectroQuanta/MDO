#include <linux/cdev.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/init.h>
#include <linux/module.h>
#include <asm/io.h>
#include <linux/timer.h>
#include <linux/device.h>
#include <linux/err.h>
#include <linux/mm.h>
#include <linux/io.h>

#include "utils.h"

#define DEVICE_NAME "frag0"
#define CLASS_NAME "fragClass"

MODULE_LICENSE("GPL");
MODULE_INFO(intree, "Y");

/* Device variables */
struct class* fragDevice_class = NULL;
static dev_t fragDevice_majorminor;
static struct cdev c_dev;  // Character device structure

struct GpioRegisters *s_pGpioRegisters;
static const int fragGpioPin = 26;

ssize_t frag_device_write(struct file *pfile, const char __user *pbuff, size_t len, loff_t *off) {
	struct GpioRegisters *pdev; 
	
	pr_alert("%s: called (%u)\n",__FUNCTION__,len);

	
	if(unlikely(pfile->private_data == NULL))
		return -EFAULT;

	pdev = (struct GpioRegisters *)pfile->private_data;
	if (pbuff[0]=='0')
		SetGPIOOutputValue(pdev, fragGpioPin, 0);
	else
		SetGPIOOutputValue(pdev, fragGpioPin, 1);
	return len;
}

static struct file_operations fragDevice_fops = {
	.owner = THIS_MODULE,
	.write = frag_device_write,
	.read = frag_device_read,
	.release = frag_device_close,
	.open = frag_device_open,
};
