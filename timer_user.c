#include <stdio.h>  
#include <time.h>  
#include <sys/time.h>  
#include <stdlib.h>  
#include <signal.h>  
    
static int count = 0;  
static struct itimerval oldtv;  
    
void set_timer()  
{  
    struct itimerval itv;  
    itv.it_interval.tv_sec = 1;  
    itv.it_interval.tv_usec = 0;  
    itv.it_value.tv_sec = 1;  
    itv.it_value.tv_usec = 0;  
    setitimer(ITIMER_REAL, &itv, &oldtv); //ITIMER_REAL : 以系统真实的时间来计算
}  
      
void signal_handler(int m)  
{  
    count ++;  
    printf("%d\n", count);  
}  
      
int main()  
{  
    signal(SIGALRM, signal_handler);    //SIGALRM信号对应signal_handler 
    set_timer();                        //它送出SIGALRM信号
    while(count < 10000);  
    
    exit(0);  
    return 1;  
}  
