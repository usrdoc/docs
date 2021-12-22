/* Program to illustrate the lifecycle of a thread. The main thread does not
 * wait for the thread to finish. But however, the main thread exits and thus
 * the thread peacefully completes. */

#include <pthread.h>
#include <unistd.h>

#include "errors.h"

void *
thr_func(void *arg)
{
        sleep(20);
        printf("Printing in thread\n");
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

        /* Exit the main thread, thus allowing the thread to complete peacefully.  */
        /* Essentially, either call pthread_exit or call pthread_join or sleep longer? */
        pthread_exit(&thread_result);
        printf("Will this print?\n"); /* No it will not. */
        /* Is this similar to pthread_join()? No, join() gets the status of
         * thread, this does not. Though main is blocked, it is not much
         * bothered about the exit status of the thread. */

        if (thread_result == NULL) /* We sent null, got null in return. */
                return(0);
        else
                return(1);
}
