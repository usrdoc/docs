/* Program to illustrate the lifecycle of a thread. The main thread does not
 * wait for the thread to finish. The thread function does not complete */

#include <pthread.h>
#include <unistd.h>

#include "errors.h"

void *
thr_func(void *arg)
{
        sleep(10);
        /* This will never print since the main thread does not wait but just
         * returns */
        printf("Printing in thread\n");
        return arg;

}

int
main(int argc, char **argv)
{
        pthread_t thread_id;
        /* void *thread_result; */
        int status;

        status = pthread_create(&thread_id, NULL, thr_func, NULL);

        if (status != 0)
                err_abort(status, "thread create");

        /* Join the thread, to ensure it finishes  */
        /* We comment out the join part, to illustrate the death of threads */

        /*
         * status = pthread_join(thread_id, &thread_result);
         * if (status != 0)
         *     err_abort(status, "join thread");
         */

        // if (thread_result == NULL) /* We sent null, got null in return. */
        //     return(0);
        printf("Hello from main, I'm not waiting for the thread.\n");

        return(0);
}
