/* Description: app that links code with graph in channel cluster, updates graphs and ends link
* Author: Sharif Nasser Kadamani
* ID: A00820367
* Semester I - TEA AD18
*/

#include <stdio.h>
#include <stdint.h>
#include <greio.h>
#include <string.h>
#include <time.h>

#include "graph_link.h"
#include "i2c_datapool.h"
#include "ClusterIO_events.h"

#define TRUE 1
#define FALSE 0

#define SPEED_LIMIT (200)

extern struct datapool pool[POOLSIZE];

gre_io_t                    *send_handle;
gre_io_serialized_data_t    *nbuffer = NULL;
cluster_update_event_t 		event_data;

int init_graph_link(void) {
	/* Connect to a channel to send messages */
	send_handle = gre_io_open("cluster", GRE_IO_TYPE_WRONLY);					
	if(send_handle == NULL) {
		printf("can't open send handle ClusterIO.gapp\n");
		return FALSE;
	}
	return TRUE;
}

void *update_graph(void *arg) {
	while(1) {
		printf("Graph link loop... press CTRL + C to end\n");
		int	ret = 0;
		memset(&event_data, 0, sizeof(event_data));

		/* Current value variables */
		static int16_t speed = 0;
		static int16_t rpm = 0;
		static int16_t fuel = 0;
		static int16_t odometer = 0;
		static int16_t trip = 0;

		/* Update value variables */
		int16_t speedI2C = pool[0].data[0];
		
		
		event_data.speed = speed;
		event_data.rpm = rpm;
		event_data.fuel = fuel;
		event_data.odometer = odometer;
		event_data.trip = trip;
		
		if(speedI2C > speed && speed <= SPEED_LIMIT) {
			speed++;
			delay(20);
		}
		
		if(speedI2C < speed && speed <= SPEED_LIMIT) {
			speed--;
			delay(20);
		}
		
		/* Send a named event with an additional string payload */
		nbuffer = gre_io_serialize(nbuffer, NULL,
	            CLUSTER_UPDATE_EVENT,
	            CLUSTER_UPDATE_FMT,
	            &event_data,
	            sizeof(event_data));

		if (!nbuffer) {
			fprintf(stderr, "can't serialized data to buffer, exiting\n");
		} 
		else {
			gre_io_send(send_handle, nbuffer);
			if (ret < 0) {
				fprintf(stderr, "send failed, exiting\n");
			}
	   	}
	}
}

void end_graph_link(void) {
	/* Release the buffer memory, close the send handle */
	gre_io_free_buffer(nbuffer);
	gre_io_close(send_handle);
}
