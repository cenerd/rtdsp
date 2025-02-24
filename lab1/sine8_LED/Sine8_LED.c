//sine8_LED.c  sine generation with DIP switch control

#include "dsk6713_aic23.h"  	       //codec support
Uint32 fs = DSK6713_AIC23_FREQ_8KHZ;   //set sampling rate
#define DSK6713_AIC23_INPUT_MIC 0x0015
#define DSK6713_AIC23_INPUT_LINE 0x0011
Uint16 inputsource=DSK6713_AIC23_INPUT_MIC;//select input
#define LOOPLENGTH 8
short loopindex = 0;         	      //table index
short loopincr = 1;					  //loop increment value
short gain = 10;			          //gain factor
int timeCounter = 0;
short alternate = 0;
short sine_table[LOOPLENGTH]={0,707,1000,707,0,-707,-1000,-707}; //sine values
short sine_table2[LOOPLENGTH*2]={0,383,707,924,1000,924,707,383,0,-383,-707,-924,-1000,-924,-707,-383}; //cosine values

void main()
{
  comm_poll();              	      //init DSK,codec,McBSP
  DSK6713_LED_init();			      //init LED from BSL
  DSK6713_DIP_init();			      //init DIP from BSL
  while(1) 				              //infinite loop
  {
	//generate 500 Hz cosine wave when DIP3 is pressed
	if(DSK6713_DIP_get(3)==0)
	{
		DSK6713_LED_on(3);	// turn on LED3
		DSK6713_LED_off(0); // turn off other LEDs
		timeCounter = 0;
		alternate = 0;
		loopindex = 0;
		while(timeCounter < 40000)
		{
			output_left_sample(sine_table2[loopindex++]*gain);
			alternate++;
			if(loopindex >= LOOPLENGTH*2) loopindex = 0;
			timeCounter++;
		}
		DSK6713_LED_off(3);
		loopindex = 0;
	}
	else if(DSK6713_DIP_get(0)==0) 		  //=0 if DIP switch #0 pressed
    {
	  //DSK6713_LED_off(3);
      DSK6713_LED_on(0);	   		      //turn LED #0 ON
      output_left_sample(sine_table[loopindex+=loopincr]*gain); //output sample
      if (loopindex >= LOOPLENGTH) loopindex = 0; //reset table index
    }
    else
    {
    	DSK6713_LED_off(0); 		  //turn LED off if not pressed
    	DSK6713_LED_off(3);
    }
  }                                   //end of while(1) infinite loop
}					                  //end of main
