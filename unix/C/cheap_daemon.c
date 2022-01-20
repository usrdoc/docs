#include <unistd.h>

/* Cheap daemon: This program illustrates daemonizing without using the
 * daemon(3) syscall. This is a very lazy one, doesn't change the working dir
 * or redirect the stdout, stderr, or stdin. It just returns from the process
 * which is holding the terminal (i.e parent), the child carries on. */

void infinite_loop(void);

int
main(void)
{
    pid_t pid;

    pid = fork();

    switch(pid) {
        case 0:                 /* Child */
            infinite_loop();
            break;
        default:
            break;
    }
    return(0);
}


void
infinite_loop(void)
{
    while(1)
        ;
}
