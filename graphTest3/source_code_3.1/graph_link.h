#ifndef _GRAPH_LINK_H_
#define _GRAPH_LINK_H_

#define TRUE 1
#define FALSE 0

#define SPEED_LIMIT (200)
#define RPM_LIMIT (10000)

int init_graph_link(void);
void *update_graph(void *arg);
void end_graph_link(void);

#endif // _GRAPH_LINK_H_
