#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h> 
#include <unistd.h>
#include <stdint.h>
#include <linux/input.h>
#include "leds.h"

/********************************************************************************/
#define RED_LED_BRIGHTNESS   "/sys/class/leds/red/brightness"
#define GREEN_LED_BRIGHTNESS "/sys/class/leds/green/brightness"
#define BLUE_LED_BRIGHTNESS  "/sys/class/leds/blue/brightness"

#define LED_ON  1
#define LED_OFF 0

/********************************************************************************/
int leds_turn(char *path, int on)
{
    int fd, ret;

    ret = 0;
    fd = open(path, O_WRONLY);
    if (fd > 0)
    {
        if (on == 1)
        {
            write (fd, "1", 2);
        }
        else
        {
            write (fd, "0", 2);
        }
        ret = 1;
    }
    else
    {
        printf("%s, errro: could not open led path\n", __FUNCTION__);
    }
    return ret;
}

int leds_red_turn_on(void)
{
    return leds_turn(RED_LED_BRIGHTNESS, LED_ON);
}

int leds_red_turn_off(void)
{
    return leds_turn(RED_LED_BRIGHTNESS, LED_OFF);
}

int leds_green_turn_on(void)
{
    return leds_turn(GREEN_LED_BRIGHTNESS, LED_ON);
}

int leds_green_turn_off(void)
{
    return leds_turn(GREEN_LED_BRIGHTNESS, LED_OFF);
}

int leds_blue_turn_on(void)
{
    return leds_turn(BLUE_LED_BRIGHTNESS, LED_ON);
}

int leds_blue_turn_off(void)
{
    return leds_turn(BLUE_LED_BRIGHTNESS, LED_OFF);
}

void leds_all_turn_off(void)
{
    leds_red_turn_off();
    leds_green_turn_off();
    leds_blue_turn_off();
}