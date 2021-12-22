/* Program to illustrate the lifecycle of a thread */
/* This program shows that the main thread is blocked after the thread_join() is
 * called. */

#include <pthread.h>
#include <unistd.h>

#include "errors.h"

void *
thr_func(void *arg)
{
        sleep(10);
        printf("This prints first, main is blocked till this is printed.\n");
        return arg;
}

int
main(int argc, char **argv)
{
        pthread_t thread_id;
        void *thread_result;
        int status;

        status = pthread_create(&thread_id, NULL, thr_func, NULL);

        if (status != 0)
                err_abort(status, "thread create");

        /* Join the thread, to ensure it finishes  */
        status = pthread_join(thread_id, &thread_result);
        printf("This is printed, after the thread exits.\n");

        if (status != 0)
                err_abort(status, "join thread");

        if (thread_result == NULL) /* We sent null, got null in return. */
                return(0);
        else
                return(1);
}
