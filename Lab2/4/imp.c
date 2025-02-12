#include <stdio.h>
int main()
{
    int s_in1[4], s_in2, s_out[2];
    s_out[1] = 0;
    int i;

    while(1) {
        printf("Read 4 input tokens to s_in1:\n");
        for (i = 0; i < 4; i++)
        {
            scanf("%d", &s_in1[i]);
        }
    
        printf("Read 1 input token to s_in2:\n");
        scanf("%d", &s_in2);

        s_out[0] = s_in2 + s_in2 + 1;
        s_out[1] = s_out[0] + s_in1[0] + s_in1[1] + s_in1[2] + s_in1[3] + s_out[1];

        printf("Output: ");
        for (i = 0; i < 2; i++)
        {
            printf("%d ", s_out[i]);
        }
        printf("\n");
    }
}