#include <stdio.h>
int main()
{
    int s_in;
    int s_out = 0;

    while(1) {
        printf("Read 4 input tokens to s_in1:\n");
        scanf("%d", &s_in);
        s_out += s_in;

        scanf("%d", &s_in);
        s_out += s_in;

        scanf("%d", &s_in);
        s_out += s_in; 

        scanf("%d", &s_in);
        s_out += s_in;

        printf("Read 1 input token to s_in2:\n");
        scanf("%d", &s_in);
        s_in = s_in + s_in + 1;
        s_out += s_in;

        printf("Output: ");
        printf("%d ", s_in);
        printf("%d ", s_out);
        printf("\n");
    }
}