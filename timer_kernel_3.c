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
static char* msg = "tomxue1: hello world";

int count_tomxue = 0;

static void print_func(unsigned long lparam){
    char* str = (char*)lparam;
    printk("tomxue1: %s %ld\n",str,jiffies);

    init_timer(&timer);
    timer.expires = jiffies + 2*HZ;
    timer.function = print_func;
    timer.data = (unsigned long) msg; 
    add_timer(&timer);

    count_tomxue = count_tomxue + 1;
    printk("tomxue1: count_tomxue = %d\n", count_tomxue);
}

static int hello_init(void){
    printk("tomxue1: timer test\n");
    init_timer(&timer);
    timer.data = (unsigned long) msg;
    timer.expires = jiffies + 1*HZ; 	//start below function 1 second later, by Tom Xue
    timer.function = print_func;	
    add_timer(&timer);

    return 0;
}

static void hello_exit(void){
    del_timer(&timer);
    printk("tomxue1: good bye\n");
 
}

module_init(hello_init);
module_exit(hello_exit);
