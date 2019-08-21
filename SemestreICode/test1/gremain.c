#include <stdio.h>
#include <stdint.h>
#include <greio.h>
#include <string.h>

#include "ClusterDemo_events.h"


gre_io_t                    *send_handle;
gre_io_serialized_data_t    *nbuffer = NULL;
clusterupdate_event_t 		event_data;

#define SPEED_LIMIT (200)
#define TT_LIMIT	(255)

void TestGre_Init(void)
{
	/*
	* Connect to a channel to send messages.
	*/
	send_handle = gre_io_open("application", GRE_IO_TYPE_WRONLY);
								
	if(send_handle == NULL) 
	{
		printf("Can't open send handle ClusterDemo.gapp\n");
		return;
	}
	
	
}

void TestGre_App(void)
{
	int	ret =0;
	static int16_t SpeedValue = 0;
	static uint8_t TTValue = 0;
	memset(&event_data, 0, sizeof(event_data));
	
	event_data.Speed = SpeedValue;
	event_data.TurnLeftSignal = TTValue;
	event_data.TurnRSignal = TTValue;
	
	if(SpeedValue< SPEED_LIMIT)
	{
		SpeedValue++;
	}else
	{
		SpeedValue = 0;
	}
	
	if(TTValue< TT_LIMIT)
	{
		TTValue++;
	}else
	{
		TTValue = 0;
	}
	
	/*
	* Send a named event with an additional string payload
	*/
	nbuffer = gre_io_serialize(nbuffer, NULL,
             CLUSTERUPDATE_EVENT,
             CLUSTERUPDATE_FMT,
             &event_data,
             sizeof(event_data));
   if (!nbuffer) 
   {
     	fprintf(stderr, "Can't serialized data to buffer, exiting\n");
		return;
	}

	gre_io_send(send_handle, nbuffer);
	if (ret < 0) 
	{
		fprintf(stderr, "Send failed, exiting\n");
		return;
	}
		

	return;
}

void TestGre_Close(void)
{
	//Release the buffer memory, close the send handle
	gre_io_free_buffer(nbuffer);
	gre_io_close(send_handle);
}
