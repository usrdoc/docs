/* Illustrating the static initialization of condition variables */

#include <pthread.h>

/* Initialize a condition variable statically */
struct my_struct_tag {
        pthread_mutex_t mutex;
        pthread_cond_t  cond;
        int             data;
};

typedef struct my_struct_tag my_struct_t;

my_struct_t foo = { PTHREAD_MUTEX_INITIALIZER,
                    PTHREAD_COND_INITIALIZER,
                    0
};


int
main(int argc, char **argv)
{
        return(0);
}
