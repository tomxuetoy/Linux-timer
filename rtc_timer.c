#include <linux/rtc.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <err.h>

int main(void)
{
    unsigned long i = 0;
    unsigned long data = 0;
    time_t timep;
    int fd = open("/dev/rtc0", O_RDONLY);

    if ( fd < 0 )
        errx(1, "open() fail");

    /* set the freq as 4Hz
    其中 ioctl(fd, RTC_IRQP_SET, 4) 的第三个参数只能是 2, 4, 8, 16, 32 之一，表示 xx Hz */
    if ( ioctl(fd, RTC_IRQP_SET, 4) < 0 )
        errx(1, "ioctl(RTC_IRQP_SET) fail");

    /* enable periodic interrupts */
    if ( ioctl(fd, RTC_PIE_ON, 0) < 0 )
        errx(1, "ioctl(RTC_PIE_ON)");

    for ( i = 0; i < 100; i++ ) {
        if ( read(fd, &data, sizeof(data)) < 0 )
            errx(1, "read() error");

        time(&timep);
        printf("Current time is %s", asctime(gmtime(&timep)));
        printf("data %d\n", data);
    }

    /* disable periodic interrupts */
    if ( ioctl(fd, RTC_PIE_OFF, 0) < 0 )
        errx(1, "ioctl(RTC_PIE_OFF)");

    close(fd);
    return 0;
}
