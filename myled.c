#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/io.h>
MODULE_AUTHOR("Osanai Yoshito");
MODULE_DESCRIPTION("driver for LED control");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.1");

static dev_t dev;
static struct cdev cdv;
static struct class *cls = NULL;
static volatile u32 *gpio_base = NULL;

static unsigned int send_gpios[] = {23, 22, 25, 18, 4};

static ssize_t led_write(struct file* flip, const char* buf, size_t count, loff_t* pos) {
	const int clear = 10;
	const int active = 7;
	char c;

	printk(KERN_INFO "Write is called. ");

	if(copy_from_user(&c,buf,sizeof(char)))
	return -EFAULT;

	if(c == '0'){
		int i;
		for(i = 0; i < 5; i++) {
			gpio_base[clear] = 1 << send_gpios[i];
		}
		printk(KERN_INFO "TURN OFF");
	}
	else if(c == '1'){
		int i;
		for(i = 0; i < 5; i++) {
			gpio_base[clear] = 1 << send_gpios[i];
		}
		gpio_base[active] = 1 << send_gpios[0];	
		printk(KERN_INFO "TURN ON: %c", c);
	}
	else if(c == '2'){
		int i;
		for(i = 0; i < 5; i++) {
			gpio_base[clear] = 1 << send_gpios[i];
		}
		gpio_base[active] = 1 << send_gpios[1];	
		printk(KERN_INFO "TURN ON: %c", c);
	}
	else if(c == '3'){
		int i;
		for(i = 0; i < 5; i++) {
			gpio_base[clear] = 1 << send_gpios[i];
		}
		gpio_base[active] = 1 << send_gpios[2];	
		printk(KERN_INFO "TURN ON: %c", c);
	}
	else if(c == '4'){
		int i;
		for(i = 0; i < 5; i++) {
			gpio_base[clear] = 1 << send_gpios[i];
		}
		gpio_base[active] = 1 << send_gpios[3];	
		printk(KERN_INFO "TURN ON: %c", c);
	}
	else if(c == '5'){
		int i;
		for(i = 0; i < 5; i++) {
			gpio_base[clear] = 1 << send_gpios[i];
		}
		gpio_base[active] = 1 << send_gpios[4];	
		printk(KERN_INFO "TURN ON: %c", c);
	}
        return 1;
}

void gpio_setup(int gpio_num) {
	u32 led, index, shift, mask;

	gpio_base = ioremap_nocache(0x3F200000, 0xA0);
	led = (u32)gpio_num;
	index = (u32)(led / 10);
	shift = (led % 10) * 3;
	mask = ~(0x7 << shift);
	gpio_base[index] = (gpio_base[index] & mask) | (0x001 << shift);
}
/*
static ssize_t sushi_read(struct file* filp, char* buf, size_t count, loff_t* pos)
{
    int size = 0;
     char sushi[] = {0xF0,0x9F,0x8D,0xA3,0x0A}; //寿司の絵文字のバイナリ
     if(copy_to_user(buf+size,(const char *)sushi, sizeof(sushi))){
        printk( KERN_INFO "sushi : copy_to_user failed\n" );
     return -EFAULT;
     }
     size += sizeof(sushi);
    return size;
}
*/

static struct file_operations led_fops = {
        .owner = THIS_MODULE,
        .write = led_write
//	.read = sushi_read
};

static int __init init_mod(void)
{
	int retval;
	int i;	

	for(i = 0; i < 5; i ++) {
		gpio_setup(send_gpios[i]);
	}

	retval = alloc_chrdev_region(&dev, 0, 1, "myled");
	if(retval < 0){
		printk(KERN_ERR "alloc_chrdev_region failed.\n");
		return 0;
	}
	printk(KERN_INFO "%s is loaded. major:%d\n",__FILE__,MAJOR(dev));
	
	cdev_init(&cdv, &led_fops);
	retval = cdev_add(&cdv, dev, 1);
	if(retval < 0){
		printk(KERN_ERR "cdev_add failed. major:%d, minor:%d",MAJOR(dev),MINOR(dev));
		return retval;
        }

	cls = class_create(THIS_MODULE,"myled");
	if(IS_ERR(cls)){
		printk(KERN_ERR "class_create failed.");
		return PTR_ERR(cls);
	}
	device_create(cls, NULL, dev, NULL, "myled%d",MINOR(dev));
	return 0;

}

static void __exit cleanup_mod(void)
{
	cdev_del(&cdv);
	device_destroy(cls, dev);
	class_destroy(cls);
	unregister_chrdev_region(dev, 1);
	printk(KERN_INFO "%s is unloaded. mojor:%d\n",__FILE__,MAJOR(dev));
}

module_init(init_mod);
module_exit(cleanup_mod);
