#include <stdio.h>
#include <stdlib.h>
int main() {
    unsigned char x;
    unsigned char state;
    char nothing[] = "Nothing";
    char bottle[] = "Bottle";
    char ret[] = "Return";


    state = 0;
    while(1) {
        printf("Enter an input (10, 5, 0): ");
        scanf("%hhu", &x);
        if(x != 0 && x != 5 && x != 10) {
            printf("Error: Bad input\n");
            exit(1);
        }
        switch(state) {
            //no prev bottle, no prev 5 coin / default behaviour
            case 0:
                if(x == 5) {
                    printf("Output: %s\n", nothing);
                    state = 1;
                }
                else if(x == 10) {
                    printf("Output: %s\n", bottle);
                    state = 0;
                }
                else {
                    printf("Output: %s\n", nothing);
                    state = 0;
                }
                break;
            //no prev bottle, prev 5 coin
            case 1:
                if(x == 5) {
                    printf("Output: %s\n", bottle);
                    state = 2;
                }
                else if(x == 10) {
                    printf("Output: %s, %s\n", bottle, ret);
                    state = 0;
                }
                else {
                    printf("Output: %s\n", ret);
                    state = 0;
                }
                break;
            //prev bottle, prev 5 coin
            case 2:
                if(x == 5) {
                    printf("Output: %s\n", nothing);
                    state = 1;
                }
                else if(x == 10) {
                    printf("Output: %s\n", bottle);
                    state = 0;
                }
                else {
                    printf("Output: %s\n", nothing);
                    state = 0;
                }
                break;
            default:
                printf("Error: State %hhu should not occur!", state);
                exit(1);
        }
    }
}