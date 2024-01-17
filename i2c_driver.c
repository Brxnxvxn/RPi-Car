#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/slab.h>
#include <linux/uaccess.h>

#include <asm/io.h>

#define BCM2837_I2C_ADDRESS     0x3F205000
#define BCM2837_GPIO_ADDRESS    0x3F200000
#define LCD_SLAVE_ADDRESS       0x27


//registers
#define C                       i2c_registers
#define S                       (unsigned int*)((char*)i2c_registers + 0x4)
#define DLEN                    (unsigned int*)((char*)i2c_registers + 0x8)
#define A                       (unsigned int*)((char*)i2c_registers + 0xC)
#define FIFO                    (unsigned int*)((char*)i2c_registers + 0x10)
#define DIV                     (unsigned int*)((char*)i2c_registers + 0x14)
#define DEL                     (unsigned int*)((char*)i2c_registers + 0x18)
#define CLKT                    (unsigned int*)((char*)i2c_registers + 0x1C)

//macros for control(C) register
#define I2CEN                   (1 << 15)   //enable or disable bsc controller
#define READ                    1           // read = 1, write = 0
//#define CLEAR_FIFO
#define INTD                    (1 << 8)    //generate interrupt when transfer is done
#define INTT                    (1 << 9)    //generate interrupt when FIFO is empty with write transfer incomplete
#define ST                      (1 << 7)    //start transfer

//macros for status(S) register
#define S_CLKT                  (1 << 9)    // Clock stretch timeout
#define ERR                     (1 << 8)    //ERR ACK Error
#define RXF                     (1 << 7)    //FIFO is FULL
#define TXE                     (1 << 6)    //FIFO is empty
#define RXD                     (1 << 5)    //FIFO contains data
#define TXD                     (1 << 4)    //FIFO cannot accept data
#define TXW                     (1 << 2)    //FIFO needs writing
#define DONE                    (1 << 1)    //Checks if transfer is done
#define TA                      1           //Checks if transfer is active

                
static struct proc_dir_entry *proc = NULL;
static unsigned int *i2c_registers = NULL;
static unsigned int *gpio_registers = NULL;

static void write()


ssize_t i2c_start_transfer(struct file *file, const char __user *user, size_t size, loff_t *offset) {

    //set address
    //set DLEN for msg length
    //set interrupt flags DONE and INTT for write
    //set st and I2CEN bits to start transfer

    return size;
}

//function for interrupt service routine
//function to fill FIFO when INTT bit is set and ISR is called


static struct file_operations fops = {
    write: i2c_write,
};

static int __init i2c_driver_init(void) {
    printk("i2c driver has been installed\n");

    i2c_registers = (int *)ioremap(BCM2837_I2C_ADDRESS, PAGE_SIZE);
    if(i2c_registers == NULL) {
        printk("Failed to map I2C memory to driver\n");
        return -1;
    }

    printk("Mapped I2C memory to driver successfully\n");

    gpio_register = (int *)ioremap(BCM2837_GPIO_ADDRESS, PAGE_SIZE);
    if(gpio_register == NULL) {
        printk("Failed to map GPIO memory to driver\n");
        return -1;
    }

    prink("Mapped GPIO memory to driver successfully");

    proc = proc_create("i2c_driver", 0666, NULL, &fops);
    if(proc == NULL) {
        return -1;
    }

    //enable bsc controller
    i2c_registers |= (1 << 15);
    
    //set clock rate
    



    return 0;
}

static void __exit i2c_driver_exit(void) {
    printk("Leavind driver\n");
    return;
}

module_init(i2c_driver_init);
module_exit(i2c_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Branavan Keethabaskaran");
MODULE_DESCRIPTION("Writing I2C driver for RPi");
MODULE_VERSION("1.0");