#include <linux/init.h>
#include <linux/module.h>
#include <linux/timer.h>

//demo show that how timer.data(msg) is passed to timer.function(print_func)
//to verify that data is passed to function as its argument
/*
 * add_timer - start a timer
 * @timer: the timer to be added
 *
 * The kernel will do a ->function(->data) callback from the
 * timer interrupt at the ->expires point in the future. The
 * current time is 'jiffies'.
 */
MODULE_LICENSE("GPL");

static struct timer_list timer;
static char* msg = "hello world";

static void print_func(unsigned long lparam){
    char* str = (char*)lparam;
    printk("%s %ld\n",str,jiffies);

    init_timer(&timer);
    timer.expires = jiffies + 5*HZ;
    timer.function = print_func;
    timer.data = (unsigned long) msg; 
    add_timer(&timer);
}

static int hello_init(void){
    printk("timer test\n");
    init_timer(&timer);
    timer.data = (unsigned long) msg;
    timer.expires = jiffies + 1*HZ; 	//start below function 1 second later, by Tom Xue
    timer.function = print_func;	
    add_timer(&timer);

    return 0;
}

static void hello_exit(void){
    del_timer(&timer);
    printk("good bye\n");
 
}

module_init(hello_init);
module_exit(hello_exit);
