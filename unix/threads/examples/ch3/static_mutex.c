/* This program illustrates initializing a static mutex */

#include <pthread.h>

#include "errors.h"

/* Declare a structure with mutex and data */

struct static_mutex {
        pthread_mutex_t smutex;
        int data;
};
typedef struct static_mutex static_mutex_t;

int
main(int argc, char **argv)
{
        /* Locally initializing in main() assuming there will be no other
         * functions using this mutex. If so, do it globally. */
        static_mutex_t smutex = {
                PTHREAD_MUTEX_INITIALIZER,
                0
        };
        return(0);
}
