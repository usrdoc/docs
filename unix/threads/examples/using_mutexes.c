#include <pthread.h>
#include <stdlib.h>

struct data_record {
    pthread_mutex_t data_lock;
    char data[128];
};

struct data_record *
new_record()
{
    struct data_record *recp;

    recp = (struct data_record *) malloc(sizeof(struct data_record));
    pthread_mutex_init(&recp->data_lock, NULL);
    return(recp);
}

void
delete_record(struct data_record *recp)
{
    pthread_mutex_destroy(&recp->data_lock);
    free((void *)recp);
}

int
main(int argc, char **argv)
{
    struct data_record *rec;

    rec = new_record();
    delete_record(rec);

    return(0);
}
