#ifndef _CONFIG_H_
#define _CONFIG_H_
/*****************************************************************************/
#include <stdio.h>
#include <stdint.h>

/*****************************************************************************/
#define CONFIG_FILENAME "config.txt" 

#define MAX_NUM_SIGNALS  10 /* Max number of signals allowed per message */
#define MAX_NUM_MESSAGES 10 /* Max number of messages allowed in the confiuration */

#define SUCCESS 0
#define FAILURE 1

/*****************************************************************************/
struct signal_t
{
    char *name;
    int start_bit;
    int length;
    float factor;
};

struct message_t
{
    char *name;
    int id;
    int length;
    int num_signals;
    struct signal_t signals[MAX_NUM_SIGNALS];
};

/*****************************************************************************/
int config_load_db(const char *filename, int *num_msgs, struct message_t *messages);

/*****************************************************************************/
#endif