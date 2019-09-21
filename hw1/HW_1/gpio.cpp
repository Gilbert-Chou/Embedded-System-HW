#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>

using namespace std;

class Gpio
{
public:
    Gpio(unsigned int gpio):_gpio(gpio)
    {
        gpio_export();
        gpio_set_dir("out");

    }
    ~Gpio()
    {
        gpio_unexport();
    }

    int gpio_export()
    {
        int fd , len;
        char buf[64];

        fd = open("/sys/class/gpio/export" , O_WRONLY);
        if(fd < 0){
            perror("gpio/export");//open_failed
            return fd;
        }

        len = snprintf(buf, sizeof(buf), "%d", _gpio);
        write(fd, buf, len);
        close(fd);

        return 0;
    }

    int gpio_unexport()
    {
        int fd , len;
        char buf[64];

        fd = open("/sys/class/gpio/unexport" , O_WRONLY);
        if(fd < 0){
            perror("gpio/unexport");//open_failed
            return fd;
        }

        len = snprintf(buf, sizeof(buf), "%d", _gpio);
        write(fd, buf, len);
        close(fd);

        return 0;
    }

    int gpio_set_dir(string dirStatus)
    {
        int fd;
        char buf[64];

        snprintf(buf, sizeof(buf), "/sys/class/gpio/gpio%d/direction", _gpio);

        fd = open(buf , O_WRONLY);
        if(fd < 0){
            perror("gpio/direction");//open_failed
            return fd;
        }

        if(dirStatus == "out")
            write(fd, "out", 4);
        else
            write(fd, "in", 3);

        close(fd);
        return 0;
    }

    int gpio_set_value(int value)
    {
        int fd;
        char buf[64];

        snprintf(buf, sizeof(buf), "/sys/class/gpio/gpio%d/value", _gpio);

        fd = open(buf , O_WRONLY);
        if(fd < 0){
            perror("gpio/set_value");//open_failed
            return fd;
        }

        if(value == 0)
            write(fd, "0", 2);
        else
            write(fd, "1", 2);

        close(fd);
        return 0;
    }
private:
    unsigned int _gpio;
};
