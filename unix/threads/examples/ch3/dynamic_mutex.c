/* This program illustrates initializing a dynamic mutex */

#include <pthread.h>
#include <stdlib.h>

#include "errors.h"

/* Declare a structure with mutex and data */

struct useless_mutex {
        pthread_mutex_t mutex;
        int data;
};
typedef struct useless_mutex useless_mutex_t;

int
main(int argc, char **argv)
{
        int status;

        /* Locally initializing in main() assuming there will be no other
         * functions using this mutex. If so, do it globally. */
        useless_mutex_t *umutex = malloc(sizeof(useless_mutex_t));

        /* Initialize the mutex */
        status = pthread_mutex_init(&umutex->mutex, NULL);
        if (status != 0)
                err_abort(status, "mutext init");
        status = pthread_mutex_init(&umutex->mutex, NULL);
        if (status != 0)
                err_abort(status, "mutext init");

        return(0);
}
