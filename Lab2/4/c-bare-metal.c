/*
Bare-metal implementation of the following orignal ForSyDe-model

module SDF_System_Model where

import ForSyDe.Shallow

-- System Netlist
system s_in = s_out where
  s_1 = p_1 s_in s_6_delayed
  (s_2, s_3) = p_2 s_1
  s_6 = p_3 s_3 s_5
  (s_out, s_4) = p_4 s_2
  s_5 = p_5 s_4
  s_6_delayed = delaySDF [0,0] s_6

-- Process Specification
p_1 = actor21SDF (2,1) 1 f_1
  where f_1 [x1,x2] [y] = [x1+x2+y]
p_2 = actor12SDF 1 (1,1) f_2
  where f_2 [x] = ([x],[x+1])
p_3 = actor21SDF (2,2) 2 f_3
  where f_3 [x1,x2] [y1,y2] = [x1+x2,y1+y2]
p_4 = actor12SDF 1 (3,1) f_4
  where f_4 [x] = ([x,x+1,x+2],[x])
p_5 = actor11SDF 1 1 f_5
  where f_5 [x] = [x+1]
*/

#include <stdio.h>
#include "circular_buffer.h" /* defines data type token as uint8_t */

/* Definition of the channel */
typedef cbuf_handle_t channel;

/* Definition of the functions 'readToken' and 'writeToken' */
int readToken(channel ch, token* data) {
  return circular_buf_get(ch, data);
}

void writeToken(channel ch, token data) {
  circular_buf_put(ch, data);
}

/* Definition of function 'createFIFO' */
channel createFIFO(token* buffer, size_t size){
  return circular_buf_init(buffer, size);
}

/* Definition of SDF actors */

void actor11SDF(int consum, int prod,
					 channel* ch_in, channel* ch_out,
					 void (*f) (token*, token*))
{
  token input[consum], output[prod];
  int i;

  for(i = 0; i < consum; i++) {
	 readToken(*ch_in, &input[i]);
  }
  f(input, output);
  for(i = 0; i< prod; i++) {	 
	 writeToken(*ch_out, output[i]);
  }
}

void actor12SDF(int consum, int prod1, int prod2,
					 channel* ch_in, channel* ch_out1, channel* ch_out2,
					 void (*f) (token*, token*, token*))
{
  token input[consum], output1[prod1], output2[prod2];
  int i;

  for(i = 0; i < consum; i++) {
	 readToken(*ch_in, &input[i]);
  }
  f(input, output1, output2);
  for(i = 0; i< prod1; i++) {	 
	 writeToken(*ch_out1, output1[i]);
  }
  for(i = 0; i< prod2; i++) {	 
	 writeToken(*ch_out2, output2[i]);
  }
}

void actor21SDF(int consum1, int consum2, int prod,
					 channel* ch_in1, channel* ch_in2, channel* ch_out,
					 void (*f) (token*, token*, token*))
{
  token input1[consum1], input2[consum2], output[prod];
  int i;

  for(i = 0; i < consum1; i++) {
	 readToken(*ch_in1, &input1[i]);
  }
  for(i = 0; i < consum2; i++) {
	 readToken(*ch_in2, &input2[i]);
  }
  f(input1, input2, output);
  for(i = 0; i< prod; i++) {	 
	 writeToken(*ch_out, output[i]);
  }
}

/* Definition of functions within processes */

/* Function in P_1 */
// p_1 = actor21SDF (2 ,1) 1 f_1
//   where f_1 [ x1 , x2 ] [ y ] = [ x1 + x2 + y ]
void f_1(token* in1, token* in2, token* out) {
  out[0] = in1[0] + in1[1] + in2[0];
}

/* Function in P_2 */
// p_2 = actor12SDF 1 (1 ,1) f_2
//   where f_2 [ x ] = ([ x ] ,[ x +1])
void f_2(token* in, token* out1, token* out2) {
  out1[0] = in[0];
  out2[0] = in[0] + 1;
}

/* Function in P_3 */
// p_3 = actor21SDF (2 ,2) 2 f_3
//   where f_3 [ x1 , x2 ] [ y1 , y2 ] = [ x1 + x2 , y1 + y2 ]
void f_3(token* in1, token* in2, token* out) {
  out[0] = in1[0] + in1[1];
  out[1] = in2[0] + in2[1];
}

/* Function in P_4 */
// p_4 = actor12SDF 1 (3 ,1) f_4
//   where f_4 [ x ] = ([ x , x +1 , x +2] ,[ x ])
void f_4(token* in, token* out1, token* out2) {
  out1[0] = in[0];
  out1[1] = in[0] + 1;
  out1[2] = in[0] + 2;
  out2[0] = in[0];
}

/* Function in P_5 */
// p_5 = actor11SDF 1 1 f_5
//   where f_5 [ x ] = [ x +1]
void f_5(token* in, token* out) {
  out[0] = in[0] + 1;
}

/* Main Program */

int main() {
  token input;
  token output;
  int i, j;

  /* Create FIFO-Buffers for signals */
  
  /* Buffer s_in: Size: 2 */
  token* buffer_s_in  = malloc(2 * sizeof(token));
  channel s_in = createFIFO(buffer_s_in, 2);
  /* Buffer s_out: Size: 3 */
  token* buffer_s_out  = malloc(3 * sizeof(token));
  channel s_out = createFIFO(buffer_s_out, 3);
  /* Buffer s_1: Size: 1 */
  token* buffer_s_1  = malloc(1 * sizeof(token));
  channel s_1 = createFIFO(buffer_s_1, 1);
  /* Buffer s_2: Size: 1 */
  token* buffer_s_2  = malloc(1 * sizeof(token));
  channel s_2 = createFIFO(buffer_s_2, 1);
  /* Buffer s_3: Size: 2 */
  token* buffer_s_3  = malloc(2 * sizeof(token));
  channel s_3 = createFIFO(buffer_s_3, 2);
  /* Buffer s_4: Size: 1 */
  token* buffer_s_4  = malloc(1 * sizeof(token));
  channel s_4 = createFIFO(buffer_s_4, 1);
  /* Buffer s_5: Size: 2 */
  token* buffer_s_5  = malloc(2 * sizeof(token));
  channel s_5 = createFIFO(buffer_s_5, 2);
  /* Buffer s_6: Size: 2 */
  token* buffer_s_6  = malloc(2 * sizeof(token));
  channel s_6 = createFIFO(buffer_s_6, 2);

  /* Put initial tokens in channel s_6 */
  writeToken(s_6, 0);
  writeToken(s_6, 0);

  /* Repeating Schedule: P_1, P_2, P_4, P_5, P_1, P_2, P_4, P_5, P_3 */
  while(1) {
	 for(i = 0; i < 2; i++) {
		/* Read input tokens */
		printf("Read two input tokens: ");
		for(j = 0; j < 2; j++) {
		  scanf("%d", &input);
		  writeToken(s_in, input);
		}
		/* P_1 */
		actor21SDF(2, 1, 1, &s_in, &s_6, &s_1, f_1);
		/* P_2 */
		actor12SDF(1, 1, 1, &s_1, &s_2, &s_3, f_2);
		/* P_4 */
		actor12SDF(1, 3, 1, &s_2, &s_out, &s_4, f_4);
		/* Write output tokens */
		printf("Output: ");
		for(j = 0; j< 3; j++) {
		  readToken(s_out, &output);
		  printf("%d ", output);
		}
		printf("\n");
		/* P_5 */
		actor11SDF(1, 1, &s_4, &s_5, f_5);
	 }
	 /* P_3 */
	 actor21SDF(2, 2, 2, &s_3, &s_5, &s_6, f_3);	
  }
  return 0;
}
