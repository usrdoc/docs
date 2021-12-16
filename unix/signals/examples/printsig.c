/* Catch a signal and print its signal number */

#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

static void print_signal(int);


int
main(int argc, char **argv)
{
    int i;
    struct sigaction act;

    if (memset(&act, 0, sizeof(act)) == NULL) {
        printf("memset failed\n");
    }

    act.sa_handler = print_signal;

    if (sigaction(SIGINT, &act, NULL) == -1) {
        printf("sigaction: %s\n", strerror(errno));
        return(1);
    }

    for(i = 1; ; i++) {
        sleep(2);
        printf("%d\n", i);
    }
    return(0);
}

static void
print_signal(int sig)
{
    printf("Caught signal %d\n", sig);
/* We do not exit deliberately and want the program to continue */
}
