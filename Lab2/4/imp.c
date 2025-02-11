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
        // s_in1: x y z w
        // s_in2: u
        // A1 = (x + y) A2 = (z + w)
        // B1 = (u) B2 = (u+1)
        // C = (A1 + A2 + delay)
        // dlay = (B1 + B2 + C) out1 = (B1 + B2) out2 = delay

        // delay = (B1 + B2 + C)
        // delay = (u) + (u+1) + (A1 + A2 + delay)
        // delay,out2 = (u) + (u+1) + ((x + y) + (z + w) + delay)
        // out1 = ((u) + (u+1))
    }

}