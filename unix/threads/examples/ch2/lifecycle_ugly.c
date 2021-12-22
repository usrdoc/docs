/* Program to illustrate the lifecycle of a thread. In this ugly implementation,
 * main goes to sleep() longer than the thread. Which allows enough time for the
 * thread to finish.
 */

#include <pthread.h>
#include <unistd.h>

#include "errors.h"

void *
thr_func(void *arg)
{
        sleep(12);
        printf("Printing in thread after a 12 second sleep.\n");
        return arg;

}

int
main(int argc, char **argv)
{
        pthread_t thread_id;
        int status;

        status = pthread_create(&thread_id, NULL, thr_func, NULL);

        if (status != 0)
                err_abort(status, "thread create");

        sleep(20);
        /* Sleeping longer than the thread. Ugly ugh! */
        printf("Printing in main after 20 second sleep.\n");

        return(1);
}
