#define CLUSTERUPDATE_EVENT "ClusterUpdate"
#define CLUSTERUPDATE_FMT "2s1 Speed 1u1 TurnRSignal 1u1 TurnLeftSignal"
typedef struct {
	int16_t 		Speed;
	uint8_t 		TurnRSignal;
	uint8_t 		TurnLeftSignal;
} clusterupdate_event_t;

