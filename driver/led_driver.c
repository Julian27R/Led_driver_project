#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/gpio.h>
#include <linux/device.h>

#define DEVICE_NAME "leddev"
#define GPIO_LED 113

static int major;
static struct class *led_class;
static struct device *led_device;
static int led_state = 0;

static int led_open(struct inode *inode, struct file *file) {
    printk(KERN_INFO "leddev: Dispositivo abierto\n");
    return 0;
}

static int led_release(struct inode *inode, struct file *file) {
    printk(KERN_INFO "leddev: Dispositivo cerrado\n");
    return 0;
}

static ssize_t led_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos) {
    char value;
    if (copy_from_user(&value, buf, 1))
        return -EFAULT;

    led_state = (value == '1') ? 1 : 0;
    gpio_set_value(GPIO_LED, led_state);

    printk(KERN_INFO "leddev: LED %s\n", led_state ? "ENCENDIDO" : "APAGADO");
    return count;
}

static ssize_t led_read(struct file *file, char __user *buf, size_t count, loff_t *ppos) {
    char state_str[2] = { led_state ? '1' : '0', '\n' };
    if (*ppos > 0) return 0;

    if (copy_to_user(buf, state_str, 2))
        return -EFAULT;

    *ppos = 2;
    return 2;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = led_open,
    .release = led_release,
    .write = led_write,
    .read = led_read,
};

static int __init led_init(void) {
    int ret;

    major = register_chrdev(0, DEVICE_NAME, &fops);
    if (major < 0) {
        printk(KERN_ALERT "leddev: Fallo al registrar dispositivo\n");
        return major;
    }

    ret = gpio_request(GPIO_LED, "led_gpio");
    if (ret) {
        unregister_chrdev(major, DEVICE_NAME);
        printk(KERN_ALERT "leddev: gpio_request falló\n");
        return ret;
    }

    gpio_direction_output(GPIO_LED, 0);

    led_class = class_create(DEVICE_NAME);  // SOLO pasa el nombre
    if (IS_ERR(led_class)) {
        gpio_free(GPIO_LED);
        unregister_chrdev(major, DEVICE_NAME);
        printk(KERN_ALERT "leddev: Fallo al crear clase\n");
        return PTR_ERR(led_class);
    }

    led_device = device_create(led_class, NULL, MKDEV(major, 0), NULL, DEVICE_NAME);
    if (IS_ERR(led_device)) {
        class_destroy(led_class);
        gpio_free(GPIO_LED);
        unregister_chrdev(major, DEVICE_NAME);
        printk(KERN_ALERT "leddev: Fallo al crear dispositivo\n");
        return PTR_ERR(led_device);
    }

    printk(KERN_INFO "leddev: Módulo cargado con major = %d\n", major);
    return 0;
}

static void __exit led_exit(void) {
    gpio_set_value(GPIO_LED, 0);
    gpio_free(GPIO_LED);

    device_destroy(led_class, MKDEV(major, 0));
    class_destroy(led_class);
    unregister_chrdev(major, DEVICE_NAME);

    printk(KERN_INFO "leddev: Módulo descargado\n");
}

module_init(led_init);
module_exit(led_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Julian Gutierrez - Felipe Idarraga");
MODULE_DESCRIPTION("Driver GPIO LED actualizado para kernel moderno");

