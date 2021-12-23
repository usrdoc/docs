/* Program to illustrate the block caused due to mutex lock. */
/* Call mutex_lock and print a message and sleep for a few seconds, try to
 * acquire lock from another thread. That thread is blocked until the mutex
 * unlocks.  */

#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#include "errors.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int number = 0;

void *
print_message(void *arg)
{
        /* This function will lock a mutex and sleep for 2 seconds */
        int status;
        time_t seconds;

        status = pthread_mutex_lock(&mutex);
        seconds = time(NULL);
        printf("Mutex locked @ %s", ctime(&seconds));

        if (status != 0)
                err_abort(status, "mutex lock");

        sleep(2);
        status = pthread_mutex_unlock(&mutex);
        seconds = time(NULL);
        printf("Mutex unlocked @ %s", ctime(&seconds));

        if (status != 0)
                err_abort(status, "mutex lock");

        return arg;
}


int
main(int argc, char **argv)
{
        pthread_t thread;

        printf("Starting thread #1\n");
        pthread_create(&thread, NULL, print_message, NULL);
        printf("Starting thread #2\n");
        pthread_create(&thread, NULL, print_message, NULL);
        printf("Starting thread #3\n");
        pthread_create(&thread, NULL, print_message, NULL);
        /* Join the last thread, and wait for it to finish */
        pthread_join(thread, NULL);
        exit(0);
}
