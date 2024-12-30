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
static char buffer[1000];
static int buffer_pos = 0;

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
static ssize_t iut_write(struct file *filep, const char *user_message, size_t len, loff_t *offset) {
    int bytes_to_copy = min(len, (size_t)(sizeof(buffer) - buffer_pos));
    int errors = copy_from_user(&buffer[buffer_pos], user_message, bytes_to_copy);

    if (errors != 0) {
        printk(KERN_ERR "Could not copy data from user.\n");
        return -EFAULT;
    }

    buffer_pos += bytes_to_copy;

    if (buffer_pos >= 200) {
        buffer[buffer_pos] = '\0';  // اضافه کردن پایان رشته برای چاپ
        printk(KERN_INFO "Buffered data: %s\n", buffer);
        buffer_pos = 0;
    }

    return bytes_to_copy;
}


module_init(iut_init);
module_exit(iut_exit);
