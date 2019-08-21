#ifndef I2C_DATAPOOL_H_INCLUDED
#define I2C_DATAPOOL_H_INCLUDED

#define POOLSIZE 8
#define DATASIZE 5

#define _ENG_SPEED_ 0
#define _ENG_RPM_ 0
#define _ENG_OIL_LEVEL_ 0

struct datapool{
	char *name;
	int id;	
	int length;
	int data[5];
};

int delay(long int milliseconds);
void *receive_datapool(void *arg);

#endif // I2C_DATAPOOL_H_INCLUDED