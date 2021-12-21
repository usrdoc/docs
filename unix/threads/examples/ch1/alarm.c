/* Alarm program without threads or multiple processes. This is an
   example of a synchronous program from the book by D. R. Butenhof */

/* Read a line, parse seconds and message. Sleep for seconds and print a
 * message. */

#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>

int
main(int argc, char **argv)
{
        int seconds;
        char line[128];
        char message[64];

        while (1) {
                printf("Alarm> ");
                if (fgets(line, sizeof(line), stdin) == NULL)
                        exit(0);
                if (strlen(line) <= 1)
                        continue;
                if (sscanf(line, "%d %64[^\n]", &seconds, message) < 2) {
                        fprintf(stderr, "usage: seconds message\n");
                } else {
                        sleep(seconds);
                        printf("(%d) %s\n", seconds, message);
                }
        }
        return(0);
}
