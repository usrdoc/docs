Some quirks

TIL that 'default:' in a switch can happen anywhere. Not necessarily at the
end. For example the below switch is perfectly legal.

```
    switch (input) {
        case 0:
            printf("Got a zero\n");
            break;
        default:
            printf("Input something useful\n");
            break;
        case 1:
            printf("Got a one\n");
            break;
        case 2:
            printf("Got a two\n");
            break;
        case 3:
            printf("Got a three\n");
            break;
    }

```
