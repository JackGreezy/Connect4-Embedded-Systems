// Sound.c
// Runs on MSPM0
// Sound assets in sounds/sounds.h
// Jonathan Valvano
// 11/15/2021 
#include <stdint.h>
#include <ti/devices/msp/msp.h>
#include "Sound.h"
#include "sounds/sounds.h"
#include "DAC5.h"
#include "../inc/Timer.h"

const uint8_t *pt;
uint32_t length = 0;

void SysTick_IntArm(uint32_t period, uint32_t priority){
	 SysTick->CTRL = 0x00;
	  SysTick->LOAD = period-1;
	 SCB->SHP[1] = (SCB->SHP[1]&(~0xC0000000))|priority<<30;
	  SysTick->VAL=0;
	 SysTick->CTRL=0x07;
}

//period = 11 khz



// initialize a 11kHz SysTick, however no sound should be started
// initialize any global variables
// Initialize the 5 bit DAC
void Sound_Init(void){
	SysTick_IntArm(0,1);
	DAC5_Init();
}

void SysTick_Handler(void){
	static int32_t i=0;
	DAC5_Out(pt[i]);
	if(i == length){
		  SysTick->LOAD = 0;
		  i = 0;
	}
	i++;


	// called at 11 kHz
  // output one value to DAC if a sound is active
	//call Dac5Out with whichever element I am on in the array, increment it and if at end stop interrupt


}

//******* Sound_Start ************
// This function does not output to the DAC. 
// Rather, it sets a pointer and counter, and then enables the SysTick interrupt.
// It starts the sound, and the SysTick ISR does the output
// feel free to change the parameters
// Sound should play once and stop
// Input: pt is a pointer to an array of DAC outputs
//        count is the length of the array
// Output: none
// special cases: as you wish to implement


void Sound_Shoot(void){
	SysTick->LOAD = 7271;
	pt = shoot;
	length = 4080;
}
void Sound_Killed(void){
// write this

}
void Sound_Explosion(void){
	SysTick->LOAD = 7271;
	pt = explosion;
	length = 2000;
}

void Sound_Fastinvader1(void){

}
void Sound_Fastinvader2(void){

}
void Sound_Fastinvader3(void){

}
void Sound_Fastinvader4(void){

}
void Sound_Highpitch(void){

}
