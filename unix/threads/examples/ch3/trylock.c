/* Program to illustrate trylock */

#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

#include "errors.h"

#define SPIN 10000000

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
long counter;
time_t end_time;

/* In a given time frame, repeatedly lock a mutex and increment the counter */
void *
counter_thread(void *arg)
{
        int status;
        int spin;

        while(time(NULL) < end_time) {
                status = pthread_mutex_lock(&mutex);
                if (status != 0)
                        err_abort(status, "mutex lock");
                for(spin = 0; spin < SPIN; spin++)
                        counter++;
                status = pthread_mutex_unlock(&mutex);
                if (status != 0)
                        err_abort(status, "mutex unlock");
                sleep(1);
        }
        printf("Counter is %#lx\n", counter);

        return(NULL);
}

void *
monitor_thread(void *arg)
{
        int status;
        int misses = 0;

        /* Loop until end_time, checking counter every 3 seconds. Count the lock
         * misses. */
        while (time(NULL) < end_time) {
                /* With a 3 second sleep chances of missing the lock is almost
                 * 0. With a 1 second sleep it might miss a couple of
                 * times. Without sleep it will miss lock thousands of times. */
                sleep(3);
                status = pthread_mutex_trylock(&mutex); /* just lock will block
                                                         * the thread */
                if (status != EBUSY) {
                        if (status != 0)
                                err_abort(status, "mutex trylock");
                        printf("Counter is %ld\n", counter/SPIN);
                        status = pthread_mutex_unlock(&mutex);
                        if (status != 0)
                                err_abort(status, "mutex unlock");
                } else
                        misses++;
        }
        printf("Monitor thread missed update %d times.\n", misses);
        return(NULL);
}

int
main(int argc, char **argv)
{
        int status;
        pthread_t counter_thread_id;
        pthread_t monitor_thread_id;

        end_time = time(NULL) + 60; /* One minute run. */
        status = pthread_create(&counter_thread_id, NULL, counter_thread, NULL);
        if (status != 0)
                err_abort(status, "counter thread create");
        status = pthread_create(&monitor_thread_id, NULL, monitor_thread, NULL);
        if (status != 0)
                err_abort(status, "monitor thread create");
        status = pthread_join(counter_thread_id, NULL);
        if (status != 0)
                err_abort(status, "counter thread join");
        status = pthread_join(monitor_thread_id, NULL);
        if (status != 0)
                err_abort(status, "monitor thread join");
        return(0);
}
