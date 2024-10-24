#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/string.h>
#include <linux/sysfs.h>
#include <linux/platform_device.h>

#define MSG_BUFFER_SIZE 100
#define STATUS_BUFFER_SIZE 10
#define VERSION_BUFFER_SIZE 20
#define MODE_BUFFER_SIZE 10

//---------------sysfs attributes management----------------//

static struct device_driver hello_driver = {
    .name = "hello_world_driver",
    .owner = THIS_MODULE, 
    .bus = &platform_bus_type, 
};

// Buffers to hold the message, status, version, and mode attributes
static char message[MSG_BUFFER_SIZE];
static char status[STATUS_BUFFER_SIZE] = "off";
static char version[VERSION_BUFFER_SIZE] = "v1.0";
static char mode[MODE_BUFFER_SIZE] = "default";

//---------------attr functions ----------------//
// Define attr functions 
static ssize_t status_show(struct device_driver *driver, char *buf) {
    return snprintf(buf, PAGE_SIZE, "%s\n", status);
}

//msg read
static ssize_t message_show(struct device_driver *driver, char *buf) {
    return snprintf(buf, PAGE_SIZE, "%s\n", message);
}

//msg write
static ssize_t message_store(struct device_driver *driver, const char *buf, size_t count) {
    strncpy(message, buf, sizeof(message) - 1);
    message[sizeof(message) - 1] = '\0'; 
    return count;
}

static ssize_t version_show(struct device_driver *driver, char *buf) {
    return snprintf(buf, PAGE_SIZE, "%s\n", version);
}

static ssize_t mode_store(struct device_driver *driver, const char *buf, size_t count) {
    strncpy(mode, buf, sizeof(mode) - 1);
    mode[sizeof(mode) - 1] = '\0'; 
    return count;
}

static ssize_t mode_show(struct device_driver *driver, char *buf) {
    return snprintf(buf, PAGE_SIZE, "%s\n", mode);
}

// Create driver attributes
static DRIVER_ATTR_RO(status);    
static DRIVER_ATTR_RW(message);    
static DRIVER_ATTR_RO(version);    
static DRIVER_ATTR_RW(mode);       

//------------core functions-------------//

static void cleanup_sysfs(void) {
    driver_remove_file(&hello_driver, &driver_attr_mode);
    driver_remove_file(&hello_driver, &driver_attr_version);
    driver_remove_file(&hello_driver, &driver_attr_message);
    driver_remove_file(&hello_driver, &driver_attr_status);
}

static int __init helloworld_init(void) {
    int ret;

    // Register the driver
    ret = driver_register(&hello_driver);
    if (ret) {
        pr_err("Failed to register driver\n");
        return ret;
    }

    //----------create sysfs attributes files ----------------//
    ret = driver_create_file(&hello_driver, &driver_attr_status);
    if (ret) {
        pr_err("Failed to create sysfs status entry\n");
        cleanup_sysfs();

        return ret;
    }

    ret = driver_create_file(&hello_driver, &driver_attr_message);
    if (ret) {
        pr_err("Failed to create sysfs message entry\n");
        cleanup_sysfs();

        return ret;
    }

    ret = driver_create_file(&hello_driver, &driver_attr_version);
    if (ret) {
        pr_err("Failed to create sysfs version entry\n");
        cleanup_sysfs();

        return ret;
    }

    ret = driver_create_file(&hello_driver, &driver_attr_mode);
    if (ret) {
        pr_err("Failed to create sysfs mode entry\n");
        cleanup_sysfs();

        return ret;
    }

    // Update status to "active"
    strncpy(status, "active", sizeof(status) - 1);
    status[sizeof(status) - 1] = '\0'; 
    
    //------------what the driver do-------------//
    pr_info("Hello World, I'm the Simple Kernel Module with Attributes\n");
    return 0;
}

static void __exit helloworld_cleanup(void) {
    // Update status to "inactive"
    strncpy(status, "inactive", sizeof(status) - 1);
    status[sizeof(status) - 1] = '\0'; 

    // Remove sysfs attributes files
    cleanup_sysfs();
    
    // Unregister the driver
    driver_unregister(&hello_driver);
    //------------what the driver do-------------//
    pr_info("Goodbye World, I'm the Simple Simple Kernel Module with Attributes\n");
}

module_init(helloworld_init);
module_exit(helloworld_cleanup);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Alessandro Scalambrino");
MODULE_DESCRIPTION("Kernel Hello World - out-of-tree module with sysfs attributes");
MODULE_INFO(board, "BeagleBone");
