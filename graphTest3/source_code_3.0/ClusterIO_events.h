#define CLUSTER_UPDATE_EVENT "cluster_update"
#define CLUSTER_UPDATE_FMT "8u1 trip 8u1 odometer 2u1 speed 2u1 rpm 2u1 fuel 2u1 battery 2u1 oil 1u1 gear_position 1s1 temp_ext 1u1 l_arrow_ind 1u1 r_arrow_ind 1u1 swerve_ind 1u1 brake_ind 1u1 highbeam_ind 1u1 seatbelt_ind 1u1 abs_ind 1u1 engine_ind"
typedef struct {
	uint64_t 		trip;
	uint64_t 		odometer;
	uint16_t 		speed;
	uint16_t 		rpm;
	uint16_t 		fuel;
	uint16_t 		battery;
	uint16_t 		oil;
	uint8_t 		gear_position;
	int8_t 		temp_ext;
	uint8_t 		l_arrow_ind;
	uint8_t 		r_arrow_ind;
	uint8_t 		swerve_ind;
	uint8_t 		brake_ind;
	uint8_t 		highbeam_ind;
	uint8_t 		seatbelt_ind;
	uint8_t 		abs_ind;
	uint8_t 		engine_ind;
} cluster_update_event_t;
