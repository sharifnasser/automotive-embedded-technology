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

#define SUCCESS 0

extern struct datapool pool[POOLSIZE];
extern int seconds, minutes, hours, state;

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

void update_graph() {
		/* printf("Graph link loop... press CTRL + C to end\n"); */
		int	ret = 0;
		/* Current value variables */
		static int8_t temp_ext = 0;

		static uint8_t speed = 0;
		static uint8_t fuel = 0;
		static uint8_t oil = 0;
		static uint8_t battery = 0;
		static uint8_t gear_position = 0;
		static uint8_t engine_ind = 0;
		static uint8_t brake_ind = 0;
		static uint8_t l_arrow_ind = 0;
		static uint8_t r_arrow_ind = 0;
		static uint8_t seatbelt_ind = 0;
		static uint8_t highbeam_ind = 0;
		static uint8_t abs_ind = 0;
		static uint8_t swerve_ind = 0;
		static uint8_t seatbelt_state = 0;
		static uint8_t hour_time = 0;
		static uint8_t minute_time = 0;

		static uint16_t rpm = 0;

		static uint64_t trip = 0;
		static uint64_t odometer = 0;


		/* Update value variables */
		int8_t temp_ext_received = pool[INF_OT_INDEX].data[0];

		uint8_t speed_received = pool[ENG_SPEED_INDEX].data[0];
		uint8_t fuel_received = pool[ENG_FUEL_INDEX].data[0];
		uint8_t oil_received = pool[ENG_OIL_PRESSURE_INDEX].data[0];
		uint8_t battery_received = pool[INF_GEN_INDEX].data[0];
		uint8_t gear_position_received = pool[ENG_GEAR_POS_INDEX].data[0];
		uint8_t eng_temp_received = pool[ENG_TEMP_INDEX].data[0];
		uint8_t brake_ind_received = pool[BD_INDEX].data[2];
		uint8_t hour_time_received = pool[INF_TIME_INDEX].data[0];
		uint8_t seatbelt_state_received = pool[SAF_INDEX].data[2];
		uint8_t minute_time_received = pool[INF_TIME_INDEX].data[2];
		uint8_t arrow_received = pool[BD_INDEX].data[4];
		uint8_t swerve_ind_received = pool[INF_GEN_INDEX].data[3];
		uint8_t abs_ind_received = pool[INF_GEN_INDEX].data[4];
		uint8_t highbeam_ind_received = pool[INF_GEN_INDEX].data[2];
		uint16_t rpm_received = pool[ENG_RPM_INDEX].data[0] + (pool[ENG_RPM_INDEX].data[1] * 16 * 16);
		uint64_t odometer_received = pool[INF_ODO_INDEX].data[0] +
									(pool[INF_ODO_INDEX].data[1] * DOS16) +
									(pool[INF_ODO_INDEX].data[2] * CUATRO16) +
									(pool[INF_ODO_INDEX].data[3] * SEIS16);
		uint64_t tip_received = pool[INF_TRIP_INDEX].data[0] +
								(pool[INF_TRIP_INDEX].data[1] * DOS16) +
								(pool[INF_TRIP_INDEX].data[2] * CUATRO16) +
								(pool[INF_TRIP_INDEX].data[3] * SEIS16);

		memset(&event_data, 0, sizeof(event_data));

		event_data.speed = speed;
		event_data.rpm = rpm;
		event_data.fuel = fuel;
		event_data.l_arrow_ind = l_arrow_ind;
		event_data.r_arrow_ind = r_arrow_ind;
		event_data.hour_time = hour_time;
		event_data.minute_time = minute_time;
		event_data.oil = oil;
		event_data.temp_ext = temp_ext;
		event_data.gear_position = gear_position;
		event_data.engine_ind = engine_ind;
		event_data.brake_ind = brake_ind;
		event_data.seatbelt_ind = seatbelt_ind;
		event_data.swerve_ind = swerve_ind;
		event_data.highbeam_ind = highbeam_ind;
		event_data.abs_ind = abs_ind;
		event_data.seatbelt_state = seatbelt_state;
		event_data.odometer = odometer;
		event_data.trip = trip;
		event_data.battery = battery;

		/* Speed update */
		if(speed_received > speed && speed <= SPEED_LIMIT) {
			speed++;
		}

		if(speed_received < speed) {
			speed--;
		}

		/* RPM update */
		if(rpm_received > rpm && rpm <= RPM_LIMIT) {
			rpm = rpm + 100;
		}

		if(rpm_received < rpm) {
			rpm = rpm - 100;
		}

		/* Fuel update */
		if(fuel_received > fuel && fuel <= FUEL_LIMIT) {
			fuel++;
		}

		if(fuel_received < fuel) {
			fuel--;
		}

		/* Fuel update */
		if(oil_received > oil && oil <= OIL_LIMIT) {
			oil++;
		}

		if(oil_received < oil) {
			oil--;
		}

		if(battery_received > battery && battery <= BATTERY_LIMIT) {
			battery++;
		}

		if(battery_received < battery) {
			battery--;
		}

		/* Indicator initialization */
		engine_ind = 0;
		brake_ind = 0;
		seatbelt_ind = 0;
		swerve_ind = 0;
		abs_ind = 0;
		highbeam_ind = 0;

		/* Indicator update */

		if(eng_temp_received > ENG_TEMP_MAX) {
			engine_ind = 255;
		}
		if(brake_ind_received == 1) {
			brake_ind = 255;
		}
		if(seatbelt_state_received >= 1 && seatbelt_state_received <= 3) {
			seatbelt_ind = 255;
		}
		if(abs_ind_received == 1) {
			abs_ind = 255;
		}
		if(swerve_ind_received == 1) {
			swerve_ind = 255;
		}
		if(highbeam_ind_received == 1) {
			highbeam_ind = 255;
		}

		switch(arrow_received) {
			case 0:
				l_arrow_ind = 0;
				r_arrow_ind = 0;
				break;
			case 1:
				l_arrow_ind = state * 255;
				r_arrow_ind = 0;
				break;
			case 2:
				l_arrow_ind = 0;
				r_arrow_ind = state * 255;
				break;
			case 3:
				l_arrow_ind = state * 255;
				r_arrow_ind = state * 255;
				break;
		}

		hour_time = hour_time_received + hours;
		minute_time = minute_time_received + minutes;
		if(hour_time >= 24) {
			hour_time = hour_time - 24;
		}
		if(minute_time >= 60) {
			minute_time = minute_time - 60;
		}

		odometer = odometer_received + trip;
		trip = tip_received;
		seatbelt_state = seatbelt_state_received;
		gear_position = gear_position_received;
		temp_ext = temp_ext_received;

		
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

void end_graph_link(void) {
	/* Release the buffer memory, close the send handle */
	gre_io_free_buffer(nbuffer);
	gre_io_close(send_handle);
}