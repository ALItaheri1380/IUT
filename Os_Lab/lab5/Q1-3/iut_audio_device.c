#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/random.h>
#include <linux/slab.h>   

#define DEVICE_NAME "iut_audio_device"
MODULE_LICENSE("GPL");

static int iut_open(struct inode*, struct file*);
static int iut_release(struct inode*, struct file*);
static ssize_t iut_read(struct file*, char*, size_t, loff_t*);
static ssize_t iut_write(struct file*, const char*, size_t, loff_t*);

static struct file_operations fops = {
   .open = iut_open,
   .read = iut_read,
   .write = iut_write,
   .release = iut_release,
};

static int major;

static int __init iut_init(void) {
    major = register_chrdev(0, DEVICE_NAME, &fops);
    if (major < 0) {
        printk(KERN_ALERT "iut_device load failed.\n");
        return major;
    }
    printk(KERN_INFO "iut_device module loaded: %d\n", major);
    return 0;
}

static void __exit iut_exit(void) {
    unregister_chrdev(major, DEVICE_NAME);
    printk(KERN_INFO "iut_device module unloaded.\n");
}

static int iut_open(struct inode *inodep, struct file *filep) {
   printk(KERN_INFO "iut_device opened.\n");
   return 0;
}

static int iut_release(struct inode *inodep, struct file *filep) {
   printk(KERN_INFO "iut_device closed.\n");
   return 0;
}

static ssize_t iut_read(struct file *filep, char *buffer, size_t len, loff_t *offset) {
    char *random_data;
    int i;
    ssize_t result;
    
    random_data = kzalloc(len, GFP_KERNEL);
    if (!random_data) {
        printk(KERN_ERR "memory allocation failed.\n");
        return -ENOMEM;
    }
    for (i = 0; i < len; i++) get_random_bytes(&random_data[i], 1);
    result = copy_to_user(buffer, random_data, len) ? 
                     (printk(KERN_ERR "could not send random data to user.\n"), -EFAULT) : 
                     (printk(KERN_INFO "data read from iut_device.\n"), len);
    
    kfree(random_data);
    return result;
}
static ssize_t iut_write(struct file *filep, const char *buffer, size_t len, loff_t *offset) {
    char *msg_buffer;
    int errors;
    msg_buffer = kzalloc(len + 1, GFP_KERNEL);
    if (!msg_buffer) {
        printk(KERN_ERR "memory allocation failed.\n");
        return -ENOMEM;
    }
    errors = copy_from_user(msg_buffer, buffer, len);
    if (errors != 0) {
        printk(KERN_ERR "colud not copy data from user.\n");
        kfree(msg_buffer);
        return -EFAULT;
    }

    msg_buffer[len] = '\0';
    printk(KERN_INFO "playing Hayede: %s\n", msg_buffer);

    kfree(msg_buffer);
    return len;
}


module_init(iut_init);
module_exit(iut_exit);
