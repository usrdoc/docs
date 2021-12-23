/* This is a slightly advanced program than the ch1/alarm.c */

#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include "errors.h"

struct alarm_tag {
        struct alarm_tag *link;
        int              seconds;
        time_t           time;  /* time_now + seconds */
        char             message[64];
};
typedef struct alarm_tag alarm_t;

/* Static mutex initializer */
pthread_mutex_t alarm_mutex = PTHREAD_MUTEX_INITIALIZER;
alarm_t         *alarm_list = NULL;

void *
alarm_thread(void *arg)
{
        alarm_t *alarm;
        int     sleep_time;
        time_t  now;
        int     status;

        while(1) {
                status = pthread_mutex_lock(&alarm_mutex);

                if (status != 0)
                        err_abort(status, "mutex lock");
                alarm = alarm_list; /* In the first run initializes the alarm
                                     * structure pointer. In the second run
                                     * gives the next item in the linked
                                     * list. Linked list is managed in main */

                if (alarm == NULL)
                        sleep_time = 1; /* Why? Gives a one second window for
                                         * the main function to insert an
                                         * alarm. */
                else {
                        alarm_list = alarm->link;
                        now = time(NULL);
                        /* alarm->time is initialized in main by adding sleep
                         * seconds to then current time. */
                        if (alarm->time <= now)
                                sleep_time = 0;
                        else
                                sleep_time = alarm->time - now;
                }

                status = pthread_mutex_unlock(&alarm_mutex);

                if (status != 0)
                        err_abort(status, "mutex unlock");
                if (sleep_time > 0) {
                        sleep(sleep_time);
                } else {
#ifdef __APPLE__
                        pthread_yield_np();
#elif __linux__
                        pthread_yield();
#endif
                }
                if (alarm != NULL) {
                        printf("(%d) %s\n", alarm->seconds, alarm->message);
                        free(alarm);
                }
        }
}

/* Main does quite a lot of work. */
int
main(int argcc, char **argv)
{
        /* Note that it does not call the thread create from within the while
         * loop. But it just creates one thread and uses it. */

        pthread_t thread;
        int       status;
        char      line[128];
        alarm_t   *alarm, *next, **last;

        /* We are creating a thread at the beginning of main. A very basic
         * configuration as of now. We do not bother about attributes yet. */
        status = pthread_create(&thread, NULL, alarm_thread, NULL);

        if (status != 0)
                err_abort(status, "pthread create");

        while(1) {
                printf("alarm> ");

                if (fgets(line, sizeof(line), stdin) == NULL)
                        exit(0);

                if (strlen(line) <= 1)
                        continue;

                if ((alarm = malloc(sizeof(alarm_t))) == NULL)
                        errno_abort("Allocate alarm");

                if (sscanf(line, "%d %64[^\n]", &alarm->seconds,
                           alarm->message) < 2) {
                        fprintf(stderr, "usage: seconds message\n");
                        free(alarm);
                } else {        /* This is the newer part */
                        status = pthread_mutex_lock(&alarm_mutex);
                        if (status != 0)
                                err_abort(status, "mutex lock");
                        alarm->time = time(NULL) + alarm->seconds;

                        /* This is the actual meat of the solution. Add the
                         * alarm structure to the linked list and sort */
                        last = &alarm_list; /* In this first run this is NULL
                                             * and in the subsequent runs this
                                             * is the last one  */
                        next = *last;
                        while (next != NULL) {
                                if (next->time >= alarm->time) {
                                        alarm->link = next;
                                        *last = alarm;
                                        break;
                                }
                                last = &next->link;
                                next = next->link;
                        }

                        if (next == NULL) {
                                *last = alarm;
                                alarm->link = NULL;
                        }
                        status = pthread_mutex_unlock(&alarm_mutex);
                        if (status != 0)
                                err_abort(status, "mutex unlock");
                }
        }
}
