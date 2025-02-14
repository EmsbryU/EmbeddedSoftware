#ifndef ACTORS_H_
#define ACTORS_H_

#include "circular_buffer.h"

typedef cbuf_handle_t channel;

int readToken(channel ch, token *data);

void writeToken(channel ch, token data);

channel createFIFO(token *buffer, size_t size);

void actor11SDF(int consum, int prod, 
    channel *ch_in, channel *ch_out, 
    void (*f)(token *, token *));

void actor12SDF(int consum, int prod1, int prod2, 
    channel *ch_in, channel *ch_out1, channel *ch_out2, 
    void (*f)(token *, token *, token *));

void actor21SDF(int consum1, int consum2, int prod, 
    channel *ch_in1, channel *ch_in2, channel *ch_out, 
    void (*f)(token *, token *, token *));

void actor22SDF(int consum1, int consum2, int prod1, int prod2, 
    channel *ch_in1, channel *ch_in2, channel *ch_out1, channel *ch_out2, 
    void (*f)(token *, token *, token *, token *));



int readToken(channel ch, token *data)
{
    return circular_buf_get(ch, data);
}
void writeToken(channel ch, token data)
{
    circular_buf_put(ch, data);
}

/* Definition of function 'createFIFO' */
channel createFIFO(token *buffer, size_t size)
{
    return circular_buf_init(buffer, size);
}

/* Definition of SDF actors */

void actor11SDF(int consum, int prod,
                channel *ch_in, channel *ch_out,
                void (*f)(token *, token *))
{
    token input[consum], output[prod];
    int i;

    for (i = 0; i < consum; i++)
    {
        readToken(*ch_in, &input[i]);
    }
    f(input, output);
    for (i = 0; i < prod; i++)
    {
        writeToken(*ch_out, output[i]);
    }
}

void actor12SDF(int consum, int prod1, int prod2,
                channel *ch_in, channel *ch_out1, channel *ch_out2,
                void (*f)(token *, token *, token *))
{
    token input[consum], output1[prod1], output2[prod2];
    int i;

    for (i = 0; i < consum; i++)
    {
        readToken(*ch_in, &input[i]);
    }
    f(input, output1, output2);
    for (i = 0; i < prod1; i++)
    {
        writeToken(*ch_out1, output1[i]);
    }
    for (i = 0; i < prod2; i++)
    {
        writeToken(*ch_out2, output2[i]);
    }
}

void actor21SDF(int consum1, int consum2, int prod, channel *ch_in1, channel *ch_in2, channel *ch_out, void (*f)(token *, token *, token *))
{
    token input1[consum1], input2[consum2], output[prod];
    int i;

    for (i = 0; i < consum1; i++)
    {
        readToken(*ch_in1, &input1[i]);
    }
    for (i = 0; i < consum2; i++)
    {
        readToken(*ch_in2, &input2[i]);
    }
    f(input1, input2, output);
    for (i = 0; i < prod; i++)
    {
        writeToken(*ch_out, output[i]);
    }
}

void actor22SDF(int consum1, int consum2, int prod1, int prod2, 
    channel *ch_in1, channel *ch_in2, channel *ch_out1, channel *ch_out2, 
    void (*f)(token *, token *, token *, token *)) 
{
    token input1[consum1], input2[consum2], output1[prod1], output2[prod2];
    int i;

    for (i = 0; i < consum1; i++)
    {
        readToken(*ch_in1, &input1[i]);
    }
    for (i = 0; i < consum2; i++)
    {
        readToken(*ch_in2, &input2[i]);
    }
    f(input1, input2, output1, output2);
    for (i = 0; i < prod1; i++)
    {
        writeToken(*ch_out1, output1[i]);
    }
    for (i = 0; i < prod2; i++)
    {
        writeToken(*ch_out2, output2[i]);
    }
}

#endif //ACTORS_H_