/* Ignore a signal without actually catching it. Or to change the default
 * action of a signal */

#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

int
main(int argc, char **argv)
{
    struct sigaction sa;
    int i;

    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = SIG_IGN;

    /* Assuming all happy cases, thus ommitting error checks. */
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);

    for (i = 1; ;i++) {
        /* Keep counting untill killed, just a way of letting know that
         * I'm alive. */
        printf("%d\n", i);
        sleep(2);
    }

    return(0);
}
