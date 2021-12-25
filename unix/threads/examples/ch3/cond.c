/* A program to illustrate the condition variables concept */

#include <pthread.h>
#include <unistd.h>
#include <time.h>

#include "errors.h"

typedef struct my_struct_tag {
        pthread_mutex_t  mutex;
        pthread_cond_t   cond;
        int              value;
} my_struct_t;

my_struct_t data = { PTHREAD_MUTEX_INITIALIZER,
                     PTHREAD_COND_INITIALIZER,
                     0 };

int hibernation = 1;

/* Set main thread's predicate and signal the condition variable */
void *
wait_thread(void *arg)
{
        int status;

        printf("Going into hibernation for %d seconds.\n", hibernation);
        sleep(hibernation);
        status = pthread_mutex_lock(&data.mutex);
        if (status != 0)
                err_abort(status, "mutex lock");
        printf("wait_thread(): holding lock.\n");
        /* Set the predicate */
        data.value = 1;
        /* Signal that the job is done */
        status = pthread_cond_signal(&data.cond);
        if (status != 0)
                err_abort(status, "signal condition");
        pthread_mutex_unlock(&data.mutex);
        printf("wait_thread(): releasing lock.\n");
        if (status != 0)
                err_abort(status, "mutex unlock");
        return(NULL);
}

int
main(int argc, char **argv)
{
        int status;
        pthread_t wait_thread_id;
        struct timespec timeout;

        if (argc > 1)
                hibernation = atoi(argv[1]);

        status = pthread_create(&wait_thread_id, NULL, wait_thread, NULL);
        if (status != 0)
                err_abort(status, "pthread create");

        timeout.tv_sec = time(NULL) + 2;
        timeout.tv_nsec = 0;
        status = pthread_mutex_lock(&data.mutex);
        if (status != 0)
                err_abort(status, "mutex lock");
        printf("main() got the lock.\n");
        /* Will it ever reach this? data.value is set to 1 by wait_thread */
        while (data.value == 0) {
                printf("Going into timedwait\n");
                /* This is where main relinquishes the lock and the thread
                 * acquires lock */
                status = pthread_cond_timedwait(&data.cond, &data.mutex, &timeout);
                printf("status is %d\n", status);
                if (status == ETIMEDOUT) {
                        printf("Condition wait timed out\n");
                        break;
                } else if (status != 0)
                        err_abort(status, "Wait on condition");
        }
        if (data.value != 0)
                printf("Condition was signaled\n");
        status = pthread_mutex_unlock(&data.mutex);
        printf("main(): releasing lock.\n");
        if (status != 0)
                err_abort(status, "Unlock mutex");
        return(0);
}

