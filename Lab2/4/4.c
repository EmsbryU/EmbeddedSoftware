/*
C-implementation of the following forsyde model

module SDF_Application where

import ForSyDe.Shallow

system :: Signal Int -> Signal Int -> Signal Int
system s_in1 s_in2 = s_out where
    s_1 = actor_a s_in1
    s_2 = actor_b s_in2
    s_3 = actor_c s_1 s_4_delayed
    (s_4, s_out) = actor_d s_2 s_3
    s_4_delayed = delaySDF [0] s_4

actor_a :: Signal Int -> Signal Int
actor_a = actor11SDF 2 1 f_1 where
    f_1 [x, y] = [x + y]

actor_b :: Signal Int -> Signal Int
actor_b = actor11SDF 1 2 f_2 where
    f_2 [x] = [x, x + 1]

actor_c :: Signal Int -> Signal Int -> Signal Int
actor_c = actor21SDF (2, 1) 1 f_3 where
    f_3 [x, y] [z] = [x + y + z]

actor_d :: Signal Int -> Signal Int -> (Signal Int, Signal Int)
actor_d = actor22SDF (2, 1) (1, 2) f_4 where
    f_4 [x, y] [z] = ([x + y + z], [x + y, x + y + z])
*/

#include <stdio.h>
#include "circular_buffer.h"
#include "actors.h"

// actor_a = actor11SDF 2 1 f_1 where
// f_1 [x, y] = [x + y]
void f_1(token *in, token *out)
{
    out[0] = in[0] + in[1];
}

// actor_b = actor11SDF 1 2 f_2 where
// f_2 [x] = [x, x + 1]
void f_2(token *in, token *out)
{
    out[0] = in[0];
    out[1] = in[0] + 1;
}

// actor_c = actor21SDF (2, 1) 1 f_3 where
//     f_3 [x, y] [z] = [x + y + z]
void f_3(token *in1, token *in2, token *out)
{
    out[0] = in1[0] + in1[1] + in2[0];
}

// actor_d = actor22SDF (2, 1) (1, 2) f_4 where
//     f_4 [x, y] [z] = ([x + y + z], [x + y, x + y + z])
void f_4(token *in1, token *in2, token *out1, token *out2)
{
    out1[0] = in1[0] + in1[1] + in2[0];
    out2[0] = in1[0] + in1[1];
    out2[1] = in1[0] + in1[1] + in2[0];
}

int main()
{
    token input;
    token output;
    int i;
    /* Create FIFO-Buffers for signals */

    /* Buffer s_in1: Size: 4 */
    token *buffer_s_in1 = malloc(4 * sizeof(token));
    channel s_in1 = createFIFO(buffer_s_in1, 4);

    /* Buffer s_in2: Size: 1 */
    token *buffer_s_in2 = malloc(1 * sizeof(token));
    channel s_in2 = createFIFO(buffer_s_in2, 1);

    /* Buffer s_1: Size: 2 */
    token *buffer_s_1 = malloc(2 * sizeof(token));
    channel s_1 = createFIFO(buffer_s_1, 2);

    /* Buffer s_2: Size: 2 */
    token *buffer_s_2 = malloc(2 * sizeof(token));
    channel s_2 = createFIFO(buffer_s_2, 2);

    /* Buffer s_3: Size: 1 */
    token *buffer_s_3 = malloc(1 * sizeof(token));
    channel s_3 = createFIFO(buffer_s_3, 1);

    /* Buffer s_4: Size: 1 */
    token *buffer_s_4 = malloc(1 * sizeof(token));
    channel s_4 = createFIFO(buffer_s_4, 1);

    /* Buffer s_out: Size: 2 */
    token *buffer_s_out = malloc(2 * sizeof(token));
    channel s_out = createFIFO(buffer_s_out, 2);

    /* Put initial tokens in channel s_4 */
    writeToken(s_4, 0);

    /* Repeating Schedule: P_A, P_A, P_B, P_C, P_D*/
    while (1)
    {
        /* Read input tokens */
        printf("Read 4 input tokens to s_in1:\n");
        for (i = 0; i < 4; i++)
        {
            scanf("%d", &input);
            writeToken(s_in1, input);
        }

        printf("Read 1 input token to s_in2:\n");
        scanf("%d", &input);
        writeToken(s_in2, input);

        /* P_A x 2*/
        for (i = 0; i < 2; i++)
        {
            actor11SDF(2, 1, &s_in1, &s_1, f_1);
        }

        
        /* P_B */
        actor11SDF(1, 2, &s_in2, &s_2, f_2);
        
        /* P_C */
        actor21SDF(2, 1, 1, &s_1, &s_4, &s_3, f_3);
        
        /* P_D */
        actor22SDF(2, 1, 1, 2, &s_2, &s_3, &s_4, &s_out, f_4);
        
        /* Write output tokens */
        printf("Output: ");
        for (i = 0; i < 2; i++)
        {
            readToken(s_out, &output);
            printf("%d ", output);
        }
        printf("\n");
    }
}