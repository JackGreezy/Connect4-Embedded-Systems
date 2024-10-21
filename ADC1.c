/*
 * ADC1.c
 *
 *  Your lab 8 solution
 */
#include <stdio.h>
#include <stdint.h>
#include <ti/devices/msp/msp.h>
#include "../inc/Clock.h"

void ADCinit(void){
    ADC1->ULLMEM.GPRCM.RSTCTL = 0xB1000003;
    ADC1->ULLMEM.GPRCM.PWREN = 0x26000001;
    Clock_Delay(24);
    ADC1->ULLMEM.GPRCM.CLKCFG = 0xA9000000;
    ADC1->ULLMEM.CLKFREQ = 7;
    ADC1->ULLMEM.CTL0 = 0X03010000;
    ADC1->ULLMEM.CTL1 = 0X00000000;
    ADC1->ULLMEM.CTL2 = 0X00000000;
    ADC1->ULLMEM.MEMCTL[0] = 5;
    ADC1->ULLMEM.SCOMP0 = 0;
    ADC1->ULLMEM.GEN_EVENT.IMASK = 0;



// write code to initialize ADC1 channel 5, PB18
// Your measurement will be connected to PB18
// 12-bit mode, 0 to 3.3V, right justified
// software trigger, no averaging

}

uint32_t ADCin(void){
    ADC1->ULLMEM.CTL0 |= 0X00000001;
    ADC1->ULLMEM.CTL1 |= 0X00000100;
    uint32_t volatile delay =ADC1->ULLMEM.STATUS;
    while((ADC1->ULLMEM.STATUS&0x01) == 0x01){};
    return ADC1->ULLMEM.MEMRES[0];



  // write code to sample ADC1 channel 5, PB18 once
  // return digital result (0 to 4095)
}


// your function to convert ADC sample to distance (0.001cm)
// use main2 to calibrate the system fill in 5 points in Calibration.xls
//    determine constants k1 k2 to fit Position=(k1*Data + k2)>>12

uint32_t Convert(uint32_t input){
    uint32_t k1 = 1950;
    uint32_t k2 = -48;
    uint32_t position = 0;
    position = ((k1*input)>>12) + k2;
    return position;
}

void OutFix(uint32_t n){
// resolution is 0.001cm
// n is integer 0 to 2000
// output to ST7735 0.000cm to 2.000cm

}
