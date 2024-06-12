#include <linux/module.h>
#include <linux/init.h>
#include <linux/pci.h>


// These have to match a physical device attached to a PCIe slot
#define PCITTL32IO_VENDOR_ID 0x8086
#define PCITTL32IO_DEVICE_ID 0x09ab


/* Meta Information */

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Shakil Ahmed");
MODULE_DESCRIPTION("A PCIe LKM");

static struct pci_device_id pcittl32io_ids[]={
    {PCI_DEVICE(PCITTL32IO_VENDOR_ID, PCITTL32IO_DEVICE_ID)},
    { }
};

MODULE_DEVICE_TABLE(pci, pcittl32io_ids);



/* @brief This function is called, when a pci device is registered into the kernel
  *
  *@param dev
  *@param id
  *@return 
*/

static int pcittl32io_probe(struct pci_dev *dev, const struct pci_device_id *id){
    printk("pcittl32io - Now in the probe function");
    return 0;
}

/* @brief This function is called, when a pci device is unregistered from the kernel
  *
  *@param dev
*/
static void pcittl32io_remove(struct pci_dev *dev){
    printk("pcittl32io - Now in the remove function");
}


/*PCI driver struct*/

static struct pci_driver pcittl32io_driver = {
    .name = "pcittl32io",
    .id_table = pcittl32io_ids,
    .probe = pcittl32io_probe,
    .remove = pcittl32io_remove
};


/*This function is called when the module is loaded into the kernel*/
static int __init my_init(void){
    printk("pcittl32io - Registering the PCI device \n");
    return pci_register_driver(&pcittl32io_driver);
}

/*This function is called when the module is removed from the kernel*/

static void __exit my_exit(void){
    printk("pcittl32io - Unregistering the PCI device \n");
    pci_unregister_driver(&pcittl32io_driver);
}

module_init(my_init);
module_exit(my_exit);