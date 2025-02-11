#include <stdio.h>
int main()
{
    //inputs
    unsigned char a; /* Integers are used as booleans here */
    unsigned char b;
    //internal s
    unsigned char s;
    //outputs
    unsigned char x;
    unsigned char y;
    unsigned char state; /* State variable for S0-S2 */
                         /* Initial State S0 */
    state = 0;


    //Mimic I/O of lustre program
    int step = 0;
    printf("#inputs \"a\":bool \"b\":bool\n#outputs \"x\":bool \"y\":bool\n");
    while (1)
    {
        scanf("%hhu %hhu", &a, &b);
        if(a & b)
            state = 255;
        switch (state)
        {
        case 0:
            x = 0;
            y = 0;
            s = 0;
            state = 1;
            break;
        //pre(s) = 0
        case 1:
            x = b;
            y = 0;
            if(a == 1) {
                s = 1;
                state = 2;
            }
            else {
                s = 0;
                state = 1;
            }
            break;
        //pre(s) = 1
        case 2:
            x = (b || a);
            y = b;
            if(a == 0 && b == 0) {
                s = 1;
                state = 2;
            }
            else {
                s = 0;
                state = 1;
            }
            break;
        default:
            printf("Error: State %hhu should not occur!", state);
        }
        printf("#step %d\n", ++step);
        printf("%hhu %hhu #outs %hhu %hhu\n", a, b, x, y);
    }
    return 0;
}