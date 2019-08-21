#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"

/*****************************************************************************/
int config_load_db(const char *filename, int *num_msgs, struct message_t *messages)
{
    FILE *fp;
    int ret, i, j;
    char buffer[25];

    ret = SUCCESS;
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("error: configuration file could not be opened (%s)\n", filename);
        ret = FAILURE;
    }
    else
    {
        /* Get number of messages */
        fscanf(fp, "%d\n", num_msgs);
        /* Get empty line */
        fscanf(fp, "\n");
        if (*num_msgs > 0 && *num_msgs < MAX_NUM_MESSAGES)
        {
            for (i = 0; i < *num_msgs; i++)
            {
                /* Read message name */
                fscanf(fp, "%s\n", buffer);
                messages[i].name = strdup(buffer);
                /* Read message id */
                fscanf(fp, "%d\n", &messages[i].id);
                /* Read message length */
                fscanf(fp, "%d\n", &messages[i].length);
                /* Get number of signals */
                fscanf(fp, "%d\n", &messages[i].num_signals);
                /* Get empty line */
                fscanf(fp, "\n");
                if (messages[i].num_signals > 0 && messages[i].num_signals < MAX_NUM_SIGNALS)
                {
                    for (j = 0; j < messages[i].num_signals; j++)
                    {
                        /* Read signal  name */
                        fscanf(fp, "%s\n", buffer);
                        messages[i].signals[j].name = strdup(buffer);
                        /* Get signal start bit */
                        fscanf(fp, "%d\n", &messages[i].signals[j].start_bit);
                        /* Get signal length */
                        fscanf(fp, "%d\n", &messages[i].signals[j].length);
                        /* Get signal factor */
                        fscanf(fp, "%f\n", &messages[i].signals[j].factor);

                        /* Get empty line */
                        fscanf(fp, "\n");
                    }
                }
            }
        }
    }

    return ret;
}
