/* Implementation of alarm using posix threads */

#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "errors.h"


typedef struct alarm_tag {
        int seconds;
        char message[64];
} alarm_t;


void *
alarm_thread (void *arg)
{
        alarm_t *alarm = (alarm_t *)arg;
        int status;

        status = pthread_detach(pthread_self()); /* We dont't care about return
                                                  * status */
        if (status != 0)
                ERR_ABORT(status, "Detach thread");
        sleep(alarm->seconds);
        printf("(%d) %s\n", alarm->seconds, alarm->message);
        free(alarm);
        return NULL;
}

int
main(int argc, char **argv)
{
        alarm_t *alarm;
        int     status;
        char    line[128];
        pthread_t thread;

        while (1) {
                printf("Alarm> ");

                if (fgets(line, sizeof(line), stdin) == NULL)
                        exit(0);

                if (strlen(line) <= 1)
                        continue;

                alarm = (alarm_t *)malloc(sizeof(alarm_t));

                if (alarm == NULL)
                        ERRNO_ABORT("Allocate alarm");

                if (sscanf(line, "%d %64[^\n]", &alarm->seconds,
                           alarm->message) < 2) {
                        fprintf(stderr, "usage: seconds message\n");
                        free(alarm);
                } else {
                        status = pthread_create(&thread, NULL, alarm_thread, alarm);
                        if (status != 0)
                                ERR_ABORT(status, "Create alarm thread");
                }
        }
        return(0);
}
