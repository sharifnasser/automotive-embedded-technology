/* Description: main app 
* Author: Sharif Nasser Kadamani
* ID: A00820367
* Semester I - TEA AD18
*/

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <string.h>
#include <linux/i2c-dev.h>
#include <errno.h>
#include <pthread.h>

#include "graph_link.h"
#include "i2c_datapool.h"

#define SUCCESS 0

struct datapool pool[POOLSIZE];
int seconds = 0, minutes = 0, hours = 0, state = 0;

void *get_time(void *arg) {
	while(1) {
		seconds++;
		state = !state;
		if(seconds == 60) {
				minutes++;
				seconds = 0;
		}
		if (minutes == 60)
		{
			hours++;
			minutes = 0;
		}
		if (hours == 24)
		{
			hours = 0;
		}
		delay(1000);
	}
}

int main(int argc, char *argv[]) {
	int ret;
	pthread_t tid;
	pthread_attr_t tattr;

	/* Create second thread for TFT display updating */
	pthread_attr_init(&tattr);
	pthread_attr_setdetachstate(&tattr, PTHREAD_CREATE_DETACHED);
	ret = pthread_create(&tid, &tattr, get_time, NULL); //CAMBIAR FUNCION
	if(ret != SUCCESS) {
		printf("error: could not start thread for time update\n");
	}

	/* Initialize link with graphs in channel */
	ret = init_graph_link();

	while(1) {
		receive_datapool();
		if(ret == 1) {
			update_graph();
		}
		else {
			printf("error: could not init graph linkage\n");	
		}
		delay(100);
	}

	/* Ends link with graphs */
	end_graph_link();

	return SUCCESS;
}