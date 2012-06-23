#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/timer.h>
#include <linux/kernel.h>

struct timer_list stimer;                                       //定义定时器
int timeout = 4 * HZ;

static void timer_handler(unsigned long data){                  //定时器处理函数，执行该函数获取挂起进程的pid，唤醒该进程
    struct task_struct *p = (struct task_struct *)data;         //参数为挂起进程pid
    wake_up_process(p);                                         //唤醒进程
    printk("timer_handler: current jiffies is %ld\n", jiffies); //打印当前jiffies
}

static int __init timer_init(void){                             //定时器初始化过程
    printk("My module worked!\n");

    init_timer(&stimer);
    stimer.data = (unsigned long)current;                       //将当前进程的pid作为参数传递; function就是时间到了以后的回调函数，它的参数就是timer_list中的data
    stimer.expires = jiffies + timeout;                         //设置到期时间
    stimer.function = timer_handler;
    add_timer(&stimer);
    printk("timer_init: current jiffies is %ld\n", jiffies);
    set_current_state(TASK_INTERRUPTIBLE);
    schedule();                                                 //挂起该进程
    del_timer(&stimer);                                         //删除定时器
    
    return 0;
}

static void __exit timer_exit(void){
    printk("Unloading my module.\n");
    return;
}

module_init(timer_init);    //加载模块
module_exit(timer_exit);    //卸载模块

MODULE_AUTHOR("fyf");
MODULE_LICENSE("GPL");
