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
void printf_config(int num_msgs, struct message_t *messages);
int delay(long int milliseconds);

void *receive_can_values(void *arg);

/*****************************************************************************/
int num_msgs;
struct message_t messages[MAX_NUM_MESSAGES];

/*****************************************************************************/
int main(int argc, char *argv[])
{
    int ret;

    pthread_t tid;
    pthread_attr_t tattr;


    // Tur off leds
    leds_all_turn_off();

    // Load configuration
    ret = config_load_db(CONFIG_FILENAME, &num_msgs, messages);
    if (ret == SUCCESS)
    {
        // TODO: Print configuration in a separate function
        printf_config(num_msgs, messages);
    }

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
	char buffer[1];
	char buffer2[1];
	int fd, i, j;
	int con=0;
	char r[3]="-r";
	/*num=atoi(argv[2]);*/
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
			buffer[0]=con;
			write(fd, buffer,1);
			read(fd, buffer2,1);
			pool[i].id=buffer2[0];	
			con++;				
			for(j=0;j<5;j++){
				buffer[0] = con;
				write(fd,buffer,1);
				read(fd, buffer,1);
				pool[i].data[j]=buffer[0];	
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

void printf_config(int num_msgs, struct message_t *messages)
{
    int i, j;

    printf("num_messages = %d\n", num_msgs);
    for (i = 0; i < num_msgs; i++)
    {
        printf("***********************************\n");
        printf("Message %d\n", i+1);
        printf("name = %s\n", messages[i].name);
        printf("id = %d\n", messages[i].id);
        printf("length = %d\n", messages[i].length);
        printf("number of signals = %d\n", messages[i].num_signals);
        for (j = 0; j < messages[i].num_signals; j++)
        {
            printf("  ---------------------------\n");
            printf("  Signal %d\n", j+1);
            printf("  name = %s\n", messages[i].signals[j].name);
            printf("  start_bit = %d\n", messages[i].signals[j].start_bit);
            printf("  length = %d\n", messages[i].signals[j].length);
            printf("  factor = %.2f\n", messages[i].signals[j].factor);
        }
    }
}


#if 0
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
  
int main(int argc, char *argv[])
{
    int fd;
    char buffer[10];
	TestGre_Init();
	TestGre_App();
    fd = open("/dev/i2c-2", O_RDWR);
    if (fd > 0)
    {
        if (ioctl(fd, I2C_SLAVE, 0xa40) > 0)
        {
            buffer[0] = 0x10;
            buffer[1] = 0x43;
            buffer[2] = 0x65;
            if (write(fd, buffer, 3) != 3)
            {
                printf("write transaction failed\n");
            }
            else
            {
                if (read(fd, buffer, 1) != 1)
                {
                    printf("read transaction failed\n");
                }
                else
                {
                    printf("byte read = %X\n", buffer[0]);
                }
            }
        }
        else
        {
            printf("error setting the slave address\n");
        }
    }
    else
    {
        printf("error opening the path i2c device\n");
    }
    return 0;
}




#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include "button.h"
#include "leds.h"
/********************************************************************************/
int delay(long int milliseconds);
void button_pressed(void);

/********************************************************************************/
int main(int argc, char *argv[])
{
    leds_all_turn_off();

    // if (input_pb1_pressed_sync() == 1)
    // {
    //     printf("Button 1 pressed\n");
    // }

    input_pb1_pressed_async(button_pressed);

    while (1)
    {
        delay(10);
    };

    return 0;
}

void button_pressed(void)
{
    static int on = 1;
    printf("%s, Button 1 pressed\n", __FUNCTION__);
    if (on)
    {
        leds_green_turn_on();
    }
    else
    {
        leds_green_turn_off();
    }
    on = !on;
}

/*!
 *  @brief  Suspends the execution of the calling thread
 *  @param  milliseconds    The amount of milliseconds the thread is suspended
 *
 *  @retval  0 Successfully sleeeping
 *  @retval -1 An error happened
 */
int delay(long int milliseconds)
{
    struct timespec t;
    // seconds
    t.tv_sec = milliseconds / 1000;
    // nanoseconds
    t.tv_nsec = (milliseconds % 1000) * 1000000;
    return nanosleep(&t, NULL);
}

#endif
