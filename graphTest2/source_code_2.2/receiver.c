#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#include "config.h"
#include "leds.h"
#include "gremain.h"

#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <string.h>
#include <linux/i2c-dev.h>
#include <errno.h>

#include "receiver.h"

#define I2C_ADDR 0x49


/*****************************************************************************/
int main(int argc, char *argv[])
{
    int ret;
    pthread_t tid;
    pthread_attr_t tattr;


    // Tur off leds
    leds_all_turn_off();

	/* Create thread */
    pthread_attr_init(&tattr);
    pthread_attr_setdetachstate(&tattr, PTHREAD_CREATE_DETACHED);
    ret = pthread_create(&tid, &tattr, receive_can_values, NULL);
    if (ret != SUCCESS)
    {
        printf("error: could not start thread\n");
    } 
	TestGre_Init();
	
    while (1)
    {
	char buffer;
	char buffer2;
	int fd, i, j;
	int con=0;
	char r[3]="-r";
	fd=open("/dev/i2c-2",O_RDWR);

	if(fd<0){
		printf("Error opening file: %s \n", strerror(errno));
		return 1;
	}
	if(ioctl(fd,I2C_SLAVE, I2C_ADDR)<0){
		printf("ioctl error: %s \n", strerror(errno));
		return 1;
	}

	if(strcmp(argv[1],r)==0){
		for(i=0; i<8;i++){			
			buffer=con;
			write(fd, &buffer,1);
			read(fd, &buffer2,1);
			pool[i].id=buffer2;	
			con++;				
			for(j=0;j<5;j++){
				buffer = con;
				write(fd,&buffer,1);
				read(fd, &buffer,1);
				pool[i].data[j]=buffer;	
				con++;				
			}			
		printf("ID: %d Data: %d / %d / %d / %d / %d\n", pool[i].id, pool[i].data[0], pool[i].data[1], pool[i].data[2], pool[i].data[3], pool[i].data[4]);
		con=0;		
		}
	}
	else {
		printf("Anexar a la linea de comando '-r' para leer datapool mandado del SAMD21 \n");
	}

        printf("Main loop... press CTRL + C to end\n");
        TestGre_App(pool);
        delay(100);
    }
	TestGre_Close();
    return SUCCESS;
}

/*****************************************************************************/
int delay(long int milliseconds)
{
    struct timespec t;
    // seconds
    t.tv_sec = milliseconds / 1000;
    // nanoseconds
    t.tv_nsec = (milliseconds % 1000) * 1000000;
    return nanosleep(&t, NULL);
}

void *receive_can_values(void *arg)
{
    // TODO: Infinitie loop tor read CAN messages from Arduino shield
    //       using I2C protocol

    int value = 0;
    while (1)
    {
        if (value == 0)
        {
            leds_red_turn_off();
        }
        else
        {
            leds_red_turn_on();
        }
        value = !value;

        delay(1000);
    }
}
