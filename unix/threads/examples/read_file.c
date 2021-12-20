/* This is a buggy program */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void *
countlines(void *result)
{
    int i, nbytes;
    char buffer[8192];
    int sum = 0;

    while ((nbytes = read(0, buffer, sizeof(buffer))) > 0) {
        for (i = 0; i < nbytes; i++) {
            if (buffer[i] == '\n')
                sum++;
        }
    }
    *(int *) result = sum;
    return(NULL);
}

int
main(int argc, char **argv)
{
    int nthreads;
    pthread_t t[10];
    int sum[10];
    int i;
    int n = 0;

    nthreads = atoi(argv[1]);

    for (i = 0; i < nthreads; i++)
        pthread_create(&t[i], NULL, countlines, &sum[i]);

    for (i = 0; i < nthreads; i++)
        pthread_join(t[i], NULL);

    for (i = 0; i < nthreads; i++)
        n += sum[i];

    printf("Using %d threads, counted %d newlines\n", nthreads, n);

    return(0);
}

