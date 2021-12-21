/* This is a variant of earlier alarm program. It spawns new process and
 * sleeps, while the main process continues to listen for new messages */

#include <sys/types.h>
#include <sys/wait.h>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>

#include "errors.h"

int
main(int argc, char **argv)
{
        char line[128];
        char message[64];
        int seconds;
        pid_t pid;

        while(1) {
                printf("Alarm> ");
                if (fgets(line, sizeof(line), stdin) == NULL)
                        exit(0);
                if (strlen(line) <= 1) /* accomodating just the newline */
                        continue;
                if (sscanf(line, "%d %64[^\n]", &seconds, message) < 2) {
                        fprintf(stderr, "usage: seconds message\n");
                } else {
                        pid = fork();
                        if (pid == (pid_t) -1)
                                ERRNO_ABORT("Fork");
                        if (pid == (pid_t) 0) {
                                sleep(seconds);
                                printf("(%d) %s\n", seconds, message);
                                exit(0); /* Exit from child */
                        } else {
                                do {
                                        /* In parent, reap the children */
                                        pid = waitpid((pid_t) -1, NULL, WNOHANG);
                                        if (pid == (pid_t) -1)
                                                ERRNO_ABORT("Wait for child");
                                } while(pid != (pid_t)0);
                        }
                }
        }
        return(0);
}
