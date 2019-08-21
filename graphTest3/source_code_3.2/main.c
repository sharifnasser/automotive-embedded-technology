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

int main(int argc, char *argv[]) {
	int ret;
	pthread_t tid;
	pthread_attr_t tattr;

	/* Initialize link with graphs in channel */
	init_graph_link();

	/* Create second thread for TFT display updating */
	pthread_attr_init(&tattr);
	pthread_attr_setdetachstate(&tattr, PTHREAD_CREATE_DETACHED);
	ret = pthread_create(&tid, &tattr, update_graph, NULL); //CAMBIAR FUNCION
	if(ret != SUCCESS) {
		printf("error: could not start thread for graphs update\n");
	}

	while(1) {
		receive_datapool();
	}

	/* Ends link with graphs */
	end_graph_link();

	return SUCCESS;
}