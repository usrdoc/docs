/* Are two pthread_t types equal before initialization?  */

#include <stdio.h>
#include <pthread.h>

int
main(void)
{
        pthread_t t1, t2;

        if (pthread_equal(t1, t2)) {
                printf("Threads are equal\n");
        } else {
                printf("Threads are not equal\n");
        }
        return(0);
}
