/* Array of integers vs array of pointers */

int
main()
{
        /* Array of integers */
        int arr[] = { 22, 9, 13, 7, 10, 11, 21, 27, 1, 2
        };
        int *i;

        /* Array of character pointers */
        char *strs[] = { "Illegal Month", "January", "February", "March",
                "April", "May", "June", "July", "August", "September",
                "October", "November", "December"
        };
        char **s;

        /* Array of integer pointers */
        int one = 1, two = 2, three = 3;
        int *ints[] = { &one, &two, &three };
        int **ip;

        /* Array of characters */
        char name[] = "Dennis Ritchie";
        char *n;

        i = arr;
        s = strs;
        ip = ints;
        n = name;

        return 0;
}
