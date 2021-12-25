/* A program to illustrate deadlocks, avoiding deadlocks. */
/* The locks are not used to control data or critical sections, they are just
 * held for illustration purposes */

#include <pthread.h>

#include "errors.h"

#define ITERATIONS 10

/* Lazy to give three unique names. Call, mutex[0], mutex[1] ... */
pthread_mutex_t mutex[3] = {
        PTHREAD_MUTEX_INITIALIZER,
        PTHREAD_MUTEX_INITIALIZER,
        PTHREAD_MUTEX_INITIALIZER
};

int backoff = 1;                /* Set 0 to illustrate deadlocks */
/* I don't care much about yield (yet!) */
//int yeild_flag = 0;             /* 0: no yield, > 0: yiled, < 0: sleep */

/* Lock the 3 mutexes, in order */
void *
lock_forward(void *arg)
{
        int i, iterate;
        int backoffs;           /* Count the lock failures */
        int status;

        for (iterate = 0; iterate < ITERATIONS; iterate++) {
                backoffs = 0;
                /* Lock the mutexes */
                for (i = 0; i < 3; i++) {
                        if (i == 0) {
                                status = pthread_mutex_lock(&mutex[i]);
                                if (status != 0)
                                        err_abort(status, "first mutex lock");
                        } else {
                                if (backoff) /* If backoff, use trylock */
                                        status = pthread_mutex_trylock(
                                                &mutex[i]);
                                else
                                        status = pthread_mutex_lock(&mutex[i]);
                                /* status can be EBUSY or non-zero */
                                if (status == EBUSY) {
                                        backoffs++;
                                        printf("forward locker backing off at %d\n", i);
                                        for (i--; i >= 0; i--) {
                                                status = pthread_mutex_unlock(
                                                        &mutex[i]);
                                                if (status != 0)
                                                        err_abort(status, "Backoff");
                                        }
                                } else if(status != 0) {
                                        printf("forward locker failed at mutex #%d\n", i);
                                        err_abort(status, "mutex lock");

                                }
                        }
                }
                printf("forward locker got all the locks, there were %d "
                       "backoffs\n", backoffs);
                /* unlock in reverse order */
                for (i = 2; i >= 0; i--)
                        pthread_mutex_unlock(&mutex[i]);
        }
        return(NULL);
}

/* This function locks the mutexes in reverse order */
void *
lock_backward(void *arg)
{
        int i, iterate;
        int backoffs;           /* Count the lock failures */
        int status;

        for (iterate = 0; iterate < ITERATIONS; iterate++) {
                backoffs = 0;
                /* Lock the mutexes */
                for (i = 2; i >=0; i--) {
                        if (i == 2) {
                                status = pthread_mutex_lock(&mutex[i]);
                                if (status != 0)
                                        err_abort(status, "first mutex lock");
                        } else {
                                if (backoff) /* If backoff, use trylock */
                                        status = pthread_mutex_trylock(
                                                &mutex[i]);
                                else
                                        status = pthread_mutex_lock(&mutex[i]);
                                /* status can be EBUSY or non-zero */
                                if (status == EBUSY) {
                                        backoffs++;
                                        printf("forward locker backing off at %d\n", i);
                                        for (i++; i < 3; i++) {
                                                status = pthread_mutex_unlock(
                                                        &mutex[i]);
                                                if (status != 0)
                                                        err_abort(status, "Backoff");
                                        }
                                } else if(status != 0) {
                                        printf("forward locker failed at mutex #%d\n", i);
                                        err_abort(status, "mutex lock");

                                }
                        }
                }
                printf("forward locker got all the locks, there were %d "
                       "backoffs\n", backoffs);
                /* unlock in reverse order */
                for (i = 0; i <= 2; i++)
                        pthread_mutex_unlock(&mutex[i]);
        }
        return(NULL);
}

int
main(int argc, char **argv)
{
        pthread_t forward, backward;
        int status;

        if (argc > 1)
                backoff = atoi(argv[1]);

        /* Create both threads */
        status = pthread_create(&forward, NULL, lock_forward, NULL);
        if (status != 0)
                err_abort(status, "forward create");
        status = pthread_create(&backward, NULL, lock_backward, NULL);
        if (status != 0)
                err_abort(status, "backward create");

        /* Why not call pthread_join()? */
        pthread_exit(NULL);

        return(0);
}
