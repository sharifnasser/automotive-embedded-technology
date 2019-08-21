#ifndef _GRAPH_LINK_H_
#define _GRAPH_LINK_H_

#define TRUE 1
#define FALSE 0

#define SPEED_LIMIT (200)
#define RPM_LIMIT (10000)
#define FUEL_LIMIT (100)
#define OIL_LIMIT (60)
#define BATTERY_LIMIT (17)
#define ENG_TEMP_MAX (95)
#define ENG_TEMP_MIN (85)

#define DOS16 (255)
#define CUATRO16 (65536)
#define SEIS16 (16777216)

int init_graph_link(void);
void update_graph();
void end_graph_link(void);

#endif // _GRAPH_LINK_H_