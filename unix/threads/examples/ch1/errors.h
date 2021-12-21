#include <stdio.h>
#include <errno.h>


#define ERR_ABORT(code, text) do { \
                fprintf(stderr, "%s at \"%s\":%d: %s\n",                \
                        text, __FILE__, __LINE__, strerror(code));     \
                abort();                                                \
        } while(0);


#define ERRNO_ABORT(text) do { \
                fprintf(stderr, "%s at \"%s\":%d: %s\n",                \
                        text, __FILE__, __LINE__, strerror(errno));     \
                abort();                                                \
        } while(0);
