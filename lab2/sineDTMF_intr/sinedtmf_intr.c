//sinedtmf_intr.c DTMF tone generation using lookup table
#include "DSK6713_AIC23.h"	          // codec support
#include "stdio.h"
Uint32 fs=DSK6713_AIC23_FREQ_16KHZ;	    //set sampling rate
#define DSK6713_AIC23_INPUT_MIC 0x0015
#define DSK6713_AIC23_INPUT_LINE 0x0011
Uint16 inputsource=DSK6713_AIC23_INPUT_MIC; // select input
#include <math.h>
#define PI 3.14159265358979

#define TABLESIZE 512        // size of look up table
#define SAMPLING_FREQ 16000
#define STEP_770 (float)(770 * TABLESIZE)/SAMPLING_FREQ
#define STEP_1336 (float)(1336 * TABLESIZE)/SAMPLING_FREQ
#define STEP_697 (float)(697 * TABLESIZE)/SAMPLING_FREQ
#define STEP_852 (float)(852 * TABLESIZE)/SAMPLING_FREQ
#define STEP_941 (float)(941 * TABLESIZE)/SAMPLING_FREQ
#define STEP_1209 (float)(1209 * TABLESIZE)/SAMPLING_FREQ
#define STEP_1477 (float)(1477 * TABLESIZE)/SAMPLING_FREQ
#define STEP_1633 (float)(1633 * TABLESIZE)/SAMPLING_FREQ

short sine_table[TABLESIZE];
float loopindexlow = 0.0;   	    // look up table index
float loopindexhigh = 0.0;
short i;

int inLoop = 0;
int toneCounter = 0;
int startCounter = 0;
int dip0state = 1;
int dip1state = 1;
int dip2state = 1;
int dip3state = 1;

#define LEFT  0
#define RIGHT 1
union {Uint32 uint; short channel[2];} AIC23_data;

interrupt void c_int11()    //interrupt service routine
{
  // THIS CODE IS FOR THE FIRST AND SECOND PARTS
  output_left_sample((sine_table[(short)loopindexlow] + sine_table[(short)loopindexhigh])/10);
  //AIC23_data.channel[LEFT] = sine_table[(short)loopindexlow];
  //AIC23_data.channel[RIGHT] = sine_table[(short)loopindexhigh];
  //output_sample(AIC23_data.uint);
  //output_left_sample(sine_table[(short)loopindexlow]);
  //output_right_sample(sine_table[(short)loopindexhigh]);
  /*loopindexlow += STEP_697;
  if (loopindexlow > (float)TABLESIZE)
    loopindexlow -= (float)TABLESIZE;
  loopindexhigh += STEP_1477;
  if (loopindexhigh > (float)TABLESIZE)
    loopindexhigh -= (float)TABLESIZE;*/

  // THIS CODE IS FOR THE THIRD PART
  //printf("Inside the interrupt\n");
  if(inLoop == 1)
  {
	  output_left_sample(sine_table[(short)loopindexlow] + sine_table[(short)loopindexhigh]);
	  if( ( dip0state == 1 ) && ( dip1state == 1 ) && ( dip2state == 1 ) && ( dip3state == 1 ) )
	  {
		  // output a 0
		  loopindexlow += STEP_941;
		  if (loopindexlow > (float)TABLESIZE)
			  loopindexlow -= (float)TABLESIZE;
		  loopindexhigh += STEP_1336;
		  if (loopindexhigh > (float)TABLESIZE)
			  loopindexhigh -= (float)TABLESIZE;
	  }
	  else if( ( dip0state == 1 ) && ( dip1state == 1 ) && ( dip2state == 1 ) && ( dip3state == 0 ) )
	  {
		  // output a 1
		  loopindexlow += STEP_697;
		  if (loopindexlow > (float)TABLESIZE)
			  loopindexlow -= (float)TABLESIZE;
		  loopindexhigh += STEP_1209;
		  if (loopindexhigh > (float)TABLESIZE)
			  loopindexhigh -= (float)TABLESIZE;
	  }
	  else if( ( dip0state == 1 ) && ( dip1state == 1 ) && ( dip2state == 0 ) && ( dip3state == 1 ) )
	  {
		  // output a 2
		  loopindexlow += STEP_697;
		  if (loopindexlow > (float)TABLESIZE)
			  loopindexlow -= (float)TABLESIZE;
		  loopindexhigh += STEP_1336;
		  if (loopindexhigh > (float)TABLESIZE)
			  loopindexhigh -= (float)TABLESIZE;
	  }
	  else if( ( dip0state == 1 ) && ( dip1state == 1 ) && ( dip2state == 0 ) && ( dip3state == 0 ) )
	  {
		  // output a 3
		  loopindexlow += STEP_697;
		  if (loopindexlow > (float)TABLESIZE)
			  loopindexlow -= (float)TABLESIZE;
		  loopindexhigh += STEP_1477;
		  if (loopindexhigh > (float)TABLESIZE)
			  loopindexhigh -= (float)TABLESIZE;
	  }
	  else if( ( dip0state == 1 ) && ( dip1state == 0 ) && ( dip2state == 1 ) && ( dip3state == 1 ) )
	  {
		  // output a 4
		  loopindexlow += STEP_770;
		  if (loopindexlow > (float)TABLESIZE)
			  loopindexlow -= (float)TABLESIZE;
		  loopindexhigh += STEP_1209;
		  if (loopindexhigh > (float)TABLESIZE)
			  loopindexhigh -= (float)TABLESIZE;
	  }
	  else if( ( dip0state == 1 ) && ( dip1state == 0 ) && ( dip2state == 1 ) && ( dip3state == 0 ) )
	  {
		  // output a 5
		  loopindexlow += STEP_770;
		  if (loopindexlow > (float)TABLESIZE)
			  loopindexlow -= (float)TABLESIZE;
		  loopindexhigh += STEP_1336;
		  if (loopindexhigh > (float)TABLESIZE)
			  loopindexhigh -= (float)TABLESIZE;
	  }
	  else if( ( dip0state == 1 ) && ( dip1state == 0 ) && ( dip2state == 0 ) && ( dip3state == 1 ) )
	  {
		  // output a 6
		  loopindexlow += STEP_770;
		  if (loopindexlow > (float)TABLESIZE)
			  loopindexlow -= (float)TABLESIZE;
		  loopindexhigh += STEP_1477;
		  if (loopindexhigh > (float)TABLESIZE)
			  loopindexhigh -= (float)TABLESIZE;
      }
	  else if( ( dip0state == 1 ) && ( dip1state == 0 ) && ( dip2state == 0 ) && ( dip3state == 0 ) )
	  {
		  // output a 7
		  loopindexlow += STEP_852;
		  if (loopindexlow > (float)TABLESIZE)
			  loopindexlow -= (float)TABLESIZE;
		  loopindexhigh += STEP_1209;
		  if (loopindexhigh > (float)TABLESIZE)
			  loopindexhigh -= (float)TABLESIZE;
	  }
	  else if( ( dip0state == 0 ) && ( dip1state == 1 ) && ( dip2state == 1 ) && ( dip3state == 1 ) )
	  {
		  // output a 8
		  loopindexlow += STEP_852;
		  if (loopindexlow > (float)TABLESIZE)
			  loopindexlow -= (float)TABLESIZE;
		  loopindexhigh += STEP_1336;
		  if (loopindexhigh > (float)TABLESIZE)
			  loopindexhigh -= (float)TABLESIZE;
	  }
	  else if( ( dip0state == 0 ) && ( dip1state == 1 ) && ( dip2state == 1 ) && ( dip3state == 0 ) )
	  {
		  // output a 9
		  loopindexlow += STEP_852;
		  if (loopindexlow > (float)TABLESIZE)
			  loopindexlow -= (float)TABLESIZE;
		  loopindexhigh += STEP_1477;
		  if (loopindexhigh > (float)TABLESIZE)
			  loopindexhigh -= (float)TABLESIZE;
	  }
	  else if( ( dip0state == 0 ) && ( dip1state == 1 ) && ( dip2state == 0 ) && ( dip3state == 1 ) )
	  {
		  // output a *
		  loopindexlow += STEP_941;
		  if (loopindexlow > (float)TABLESIZE)
			  loopindexlow -= (float)TABLESIZE;
		  loopindexhigh += STEP_1209;
		  if (loopindexhigh > (float)TABLESIZE)
			  loopindexhigh -= (float)TABLESIZE;
	  }
	  else if( ( dip0state == 0 ) && ( dip1state == 1 ) && ( dip2state == 0 ) && ( dip3state == 0 ) )
	  {
		  // output a #
		  loopindexlow += STEP_941;
		  if (loopindexlow > (float)TABLESIZE)
			  loopindexlow -= (float)TABLESIZE;
		  loopindexhigh += STEP_1477;
		  if (loopindexhigh > (float)TABLESIZE)
			  loopindexhigh -= (float)TABLESIZE;
	  }
	  else
	  {
		  // invalid input
	  }
	  toneCounter++;
	  if( toneCounter > 32000 )
	  {
		  toneCounter = 0;
		  inLoop = 0;
	  }
  }
  else
  {
	  if( ( DSK6713_DIP_get(0) == dip0state ) && ( DSK6713_DIP_get(1) == dip1state ) && ( DSK6713_DIP_get(2) == dip2state ) && ( DSK6713_DIP_get(3) == dip3state ) )
	  {
		  startCounter++;
	  }
	  else
	  {
		  startCounter = 0;
		  dip0state = DSK6713_DIP_get(0);
		  dip1state = DSK6713_DIP_get(1);
		  dip2state = DSK6713_DIP_get(2);
		  dip3state = DSK6713_DIP_get(3);
	  }

	  if( startCounter > 32000 )
	  {
		  startCounter = 0;
		  inLoop = 1;
		  loopindexlow = 0.0;
		  loopindexhigh = 0.0;
	  }
  }

  return;					//return from interrupt
}

void main()
{
  comm_intr();              // initialise DSK
  printf("Hello\n");
  for (i=0 ; i< TABLESIZE ; i++)
    sine_table[i] = (short)(10000.0*sin(2*PI*i/TABLESIZE));
  while(1);
}
