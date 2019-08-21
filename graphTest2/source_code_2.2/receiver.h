#ifndef _RECEIVER_H_
#define _RECEIVER_H_

struct datapool{
	char *name;
	int id;	
	int length;
	int data[5];
};
struct datapool pool[8];

int delay(long int milliseconds);
void *receive_can_values(void *arg);

#endif // _RECEIVER_H_
