#include <stdio.h>
#include <stdint.h>
#include <greio.h>
#include <string.h>
#include <time.h>

#include "gremain.h"

#include "ClusterIO_events.h"


gre_io_t                    *send_handle;
gre_io_serialized_data_t    *nbuffer = NULL;
cluster_update_event_t 		event_data;

#define SPEED_LIMIT (200)

void TestGre_Init(void)
{
	/*
	* Connect to a channel to send messages.
	*/
	send_handle = gre_io_open("cluster", GRE_IO_TYPE_WRONLY);
								
	if(send_handle == NULL) 
	{
		printf("Can't open send handle ClusterIO.gapp\n");
		return;
	}
	
	
}

void TestGre_App(struct datapool pool[])
{
	int	ret =0;
	static int16_t SpeedValue = 0;
	int16_t speedI2C = pool[0].data[0];
	memset(&event_data, 0, sizeof(event_data));
	
	event_data.speed = SpeedValue;
	
	if(speedI2C > SpeedValue && SpeedValue <= SPEED_LIMIT) {
		SpeedValue++;
		delay(50);
	}
	if(speedI2C < SpeedValue && SpeedValue <= SPEED_LIMIT) {
		SpeedValue--;
		delay(50);
	}
	
	/*
	* Send a named event with an additional string payload
	*/
	nbuffer = gre_io_serialize(nbuffer, NULL,
             CLUSTER_UPDATE_EVENT,
             CLUSTER_UPDATE_FMT,
             &event_data,
             sizeof(event_data));
   if (!nbuffer) 
   {
     	fprintf(stderr, "Can't serialized data to buffer, exiting\n");
   } else {

	gre_io_send(send_handle, nbuffer);
	if (ret < 0) 
	{
		fprintf(stderr, "Send failed, exiting\n");
	}
   }
		
}

void TestGre_Close(void)
{
	//Release the buffer memory, close the send handle
	gre_io_free_buffer(nbuffer);
	gre_io_close(send_handle);
}
