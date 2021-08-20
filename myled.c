#define USER_LED      374       /*GPIO LED  GPIO4_22*/  

static const struct of_device_id myled_ids[] = {  



    { .compatible = "fsl,myled", },  

    { },  

};  

static struct platform_driver myled_driver={  

    .probe  = myled_probe,  

    .remove = myled_remove,  

    .driver = {  

        .name  = "myled",  

        .of_match_table = myled_ids,  

    }  

};  

static int __init myled_init(void)  

{  

    /*2. 注册平台驱动*/  

    platform_driver_register(&myled_driver);  

    return 0;  

}  

static void __exit myled_exit(void)  

{  

    /*3. 注销平台驱动*/  

    platform_driver_unregister(&myled_driver);    

}  

static  int myled_probe(struct platform_device *pdev)  

{  

    int ret;  

    ret = gpio_request(USER_LED, "LED");//第一个参数，为要申请的引脚，第二个为你要定义的名字  

    if (ret)   

    {  

        printk("[pual] gpio_request error %s - %d -- \n",__func__,__LINE__);  

        return ret;  

    }  

    gpio_direction_output(USER_LED, 1);  

    gpio_set_value(USER_LED, 1);  

    major = register_chrdev(0,"myled",&myled_drv_fops);  



    //创建设备信息，执行后会出现 /sys/class/myled  

    myled_class = class_create(THIS_MODULE, "myled");  



    //创建设备节点，就是根据上面的设备信息来的  

    myled_class_devs = device_create(myled_class, NULL, MKDEV(major, 0), NULL, "myled"); /* /dev/myled */  



    return 0;     

}  

static long myled_drv_ioctl(struct file *file, unsigned int cmd, unsigned long arg)  

{     

    printk("gpio_ioctl\n");  

    switch(cmd) {  

        case 1:  

            if(arg == 0)  

            {  

                gpio_set_value(USER_LED, 0);  

                printk("led is off\n");  

                break;  

            }else  

                {  

                        gpio_set_value(USER_LED, 1);  

                            printk("led is on\n");  

                            break;  

                }  

        default:  

                return -EINVAL;  

    }  

    return 0;  

}  