#include <linux/init.h>      // For module_init and module_exit macros
#include <linux/module.h>    // Core header for loading modules into the kernel
#include <linux/fs.h>        // File operations structure
#include <linux/cdev.h>      // Character device functions
#include <linux/uaccess.h>   // for copy_to_user / copy_from_user
#include <linux/slab.h>      // for kmalloc / kfree
#include <linux/kfifo.h>     // for kfifo API

/* 
 * Define constants for our driver
 * DEVICE_NAME - Name that will appear in /dev/ directory
 * FIFO_SIZE - Size of our buffer in bytes
 */
#define DEVICE_NAME "simple_char"
#define FIFO_SIZE 1024

// Global variables for our driver
static dev_t dev_num;               // Holds the device number (major and minor)
static struct cdev simple_cdev;     // Character device structure
static struct class *simple_class;  // Device class for udev
// Declare a kernel FIFO buffer of FIFO_SIZE bytes
static DECLARE_KFIFO(my_fifo, char, FIFO_SIZE);

// ---------- File operations ----------

/*
 * Called when a process opens our device
 * Similar to open() system call in user space
 */
static int simple_char_open(struct inode *inode, struct file *file)
{
    // Log a message in the kernel ring buffer
    pr_info("simple_char: device opened\n");
    return 0;  // Success
}

/*
 * Called when a process closes our device
 * Similar to close() system call in user space
 */
static int simple_char_release(struct inode *inode, struct file *file)
{
    pr_info("simple_char: device closed\n");
    return 0;  // Success
}

/*
 * Called when a process reads from our device
 * Similar to read() system call in user space
 * Returns number of bytes read or error code
 */
static ssize_t simple_char_read(struct file *file, char __user *buf,
                           size_t len, loff_t *off)
{
    unsigned int copied;  // Number of bytes successfully copied
    int ret;

    // Check if there's data to read
    if (kfifo_is_empty(&my_fifo)) {
        pr_info("simple_char: no data to read\n");
        return 0;  // EOF (end of file)
    }

    // Copy data from kernel space (FIFO) to user space buffer
    ret = kfifo_to_user(&my_fifo, buf, len, &copied);
    if (ret)
        return -EFAULT;  // Bad address error

    pr_info("simple_char: read %u bytes\n", copied);
    return copied;  // Return number of bytes read
}

/*
 * Called when a process writes to our device
 * Similar to write() system call in user space
 * Returns number of bytes written or error code
 */
static ssize_t simple_char_write(struct file *file, const char __user *buf,
                            size_t len, loff_t *off)
{
    unsigned int copied;  // Number of bytes successfully copied
    int ret;

    // Copy data from user space buffer to kernel space (FIFO)
    ret = kfifo_from_user(&my_fifo, buf, len, &copied);
    if (ret)
        return -EFAULT;  // Bad address error

    pr_info("simple_char: wrote %u bytes\n", copied);
    return copied;  // Return number of bytes written
}

// ---------- File operations struct ----------

/*
 * Structure that maps file operations to our driver functions
 * The kernel uses this to call the right function for each operation
 */
static const struct file_operations simple_fops = {
    .owner = THIS_MODULE,            // Prevent module from being unloaded while in use
    .open = simple_char_open,        // Called when device is opened
    .release = simple_char_release,  // Called when device is closed
    .read = simple_char_read,        // Called when device is read from
    .write = simple_char_write,      // Called when device is written to
};

// ---------- Module setup/cleanup ----------

/*
 * Initialization function, called when the module is loaded
 * Returns 0 on success, negative error code on failure
 */
static int __init simple_char_init(void)
{
    int ret;

    // Allocate device number (both major and minor)
    ret = alloc_chrdev_region(&dev_num, 0, 1, DEVICE_NAME);
    if (ret < 0)
        return ret;  // Return error code if allocation fails

    // Initialize the character device structure
    cdev_init(&simple_cdev, &simple_fops);
    // Add the character device to the system
    cdev_add(&simple_cdev, dev_num, 1);

    // Create device class for udev
    simple_class = class_create(THIS_MODULE, DEVICE_NAME);
    // Create device node in /dev directory automatically
    device_create(simple_class, NULL, dev_num, NULL, DEVICE_NAME);

    // Initialize the FIFO buffer
    INIT_KFIFO(my_fifo);

    // Log driver loading with major and minor numbers
    pr_info("simple_char: module loaded (major=%d minor=%d)\n",
            MAJOR(dev_num), MINOR(dev_num));
    return 0;  // Success
}

/*
 * Cleanup function, called when the module is unloaded
 */
static void __exit simple_char_exit(void)
{
    // Remove device from /dev
    device_destroy(simple_class, dev_num);
    // Destroy the device class
    class_destroy(simple_class);
    // Remove character device
    cdev_del(&simple_cdev);
    // Release the device number
    unregister_chrdev_region(dev_num, 1);

    pr_info("simple_char: module unloaded\n");
}

// Register init and exit functions
module_init(simple_char_init);
module_exit(simple_char_exit);

// Module information
MODULE_LICENSE("GPL");                               // Required for most drivers
MODULE_AUTHOR("Your Name");                          // Module author
MODULE_DESCRIPTION("Simple character driver using FIFO");  // Module description
