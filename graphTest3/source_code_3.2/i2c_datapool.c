/* Description: Code in charge of I2C communication for datapool actualization
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

#include "i2c_datapool.h"

#define I2C_ADDR 0x49
#define ID_INDEX 0

extern struct datapool pool[POOLSIZE];

int delay(long int milliseconds) {
	struct timespec t;
    // seconds
    t.tv_sec = milliseconds / 1000;
    // nanoseconds
    t.tv_nsec = (milliseconds % 1000) * 1000000;
    return nanosleep(&t, NULL);	
}

int get_position_datapool(int id) {
	for(int pos = 0; pos < POOLSIZE; pos++) {
		if(pool[pos].id == id) {
			return pos;
		}
	}
	return -1; /* Si no encuentra el ID */
}

void receive_datapool() {
	while(1) {
		char buff_i2c, *filename_i2c = "/dev/i2c-2";
		int file_i2c, i, j;
		int index_data = ID_INDEX;

		file_i2c = open(filename_i2c, O_RDWR);

		if(file_i2c < 0) {
			printf("error opening file: %s \n", strerror(errno));
		}
		else if(ioctl(file_i2c, I2C_SLAVE, I2C_ADDR) < 0){
			printf("ioctl error: %s \n", strerror(errno));
		}
		else {
			for(i = 0; i < POOLSIZE; i++) {
				buff_i2c = index_data;
				write(file_i2c, &buff_i2c, 1);
				read(file_i2c, &buff_i2c, 1);
				pool[i].id = buff_i2c;
				for(j = 0; j < DATASIZE; j++) {
					index_data++;
					buff_i2c = index_data;
					write(file_i2c, &buff_i2c, 1);
					read(file_i2c, &buff_i2c, 1);
					pool[i].data[j]= buff_i2c;
				}	

			printf("ID: %x DATA: %x / %x / %x / %x / %d\n", pool[i].id, pool[i].data[0], pool[i].data[1], pool[i].data[2], pool[i].data[3], pool[i].data[4]);
			index_data = ID_INDEX;		
			}
			printf("\n");
		}
		close(file_i2c);
		delay(500);
	}
}