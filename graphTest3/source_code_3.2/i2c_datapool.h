#ifndef I2C_DATAPOOL_H_INCLUDED
#define I2C_DATAPOOL_H_INCLUDED

#define POOLSIZE 10
#define DATASIZE 5

#define ENG_SPEED_ID (0x15)
#define ENG_RPM_ID (0x16)
#define ENG_OIL_LEVEL_ID (0x20)
#define ENG_OIL_PRESSURE_ID (0x21)
#define ENG_TEMP_ID (0x25)
#define ENG_GEAR_POS_ID (0x26)
#define BD_ID (0x30)
#define SAF_ID (0x32)
#define INF_OT_ID (0x64)
#define ENG_FUEL_ID (0x22)

#define ENG_SPEED_INDEX get_position_datapool(ENG_SPEED_ID)
#define ENG_RPM_INDEX get_position_datapool(ENG_RPM_ID)
#define ENG_OIL_LEVEL_INDEX get_position_datapool(ENG_OIL_LEVEL_ID)
#define ENG_OIL_PRESSURE_INDEX (ENG_OIL_PRESSURE_ID)
#define ENG_TEMP_INDEX get_position_datapool(ENG_TEMP_ID)
#define ENG_GEAR_POS_INDEX get_position_datapool(ENG_GEAR_POS_ID)
#define BD_INDEX get_position_datapool(BD_ID)
#define SAF_INDEX get_position_datapool(SAF_ID)
#define INF_OT_INDEX get_position_datapool(INF_OT_ID)
#define ENG_FUEL_INDEX get_position_datapool(ENG_FUEL_ID)

struct datapool{
	char *name;
	int id;	
	int length;
	int data[5];
};

int delay(long int milliseconds);
int get_position_datapool(int id);
void receive_datapool();

#endif // I2C_DATAPOOL_H_INCLUDED