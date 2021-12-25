/* A program to illustrate the dynamic creation and initialization of condition
 * variables. */

#include <pthread.h>
#include <stdlib.h>

#include "errors.h"

struct cond_data {
        pthread_mutex_t mutex;
        pthread_cond_t  cond;
        int             data;
};

typedef struct cond_data cond_data_t;


int
main(int argc, char **argv)
{
        cond_data_t *d;
        int ret;


        d = (cond_data_t *)malloc(sizeof(cond_data_t));
        /* create some */
        ret = pthread_cond_init(&d->cond, NULL);
        if (ret != 0)
                err_abort(ret, "condition init");
        ret = pthread_mutex_init(&d->mutex, NULL);
        if (ret != 0)
                err_abort(ret, "mutex init");

        /* destroy some */
        ret = pthread_cond_destroy(&d->cond);
        if (ret != 0)
                err_abort(ret, "condition destroy");
        ret = pthread_mutex_destroy(&d->mutex);
        if (ret != 0)
                err_abort(ret, "mutex destroy");
        free(d);
        return(0);
}
