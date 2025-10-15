/*  Abram Gad   -   Amr Mohamed   -  Mahmude Hamdy  -  Naira Youssef */
/*  TEAM  8  */

#include "Gpio.h"
#include "Std_Types.h"
#include "Bit_Operations.h"
#include "Rcc.h"
#include "GPT_Privet.h"
#include "Gpt.h"


void GPT_Init(void){
	Rcc_Enable(RCC_TIM2);

	TIM2->CR1 &= ~(0x01<<4); //clear DIR BIT, up counting
	TIM2->CR1 |= (0x01<<7); //TIMx_ARR register is buffered
	TIM2->CR1 &= ~(0x11<<5);
	TIM2->CR1 &= ~(0x01<<8);
	TIM2->CR1 |= (0x01<<9);
	TIM2->PSC = 16000-1;  //set prescaler register to 15 so the clock frequency is 1000hz, each cycle 1ms
}
void GPT_StartTimer(uint64 OverFlowTicks){
	TIM2->ARR = OverFlowTicks-1;
	TIM2->CR1 |= (0x01<<0); //set CEN BIT , enable timer
	TIM2->CNT = 0;

}

uint8 GPT_CheckTimeIsElapsed(void){
	return (TIM2->SR & 0x01);

}
uint64 GPT_GetElapsedTime(void){
	return TIM2->CNT;
}
uint64 GPT_GetRemainingTime(void){
	return (TIM2->ARR - TIM2->CNT);
}

void delay_ms(uint32 ms) {

	GPT_StartTimer(ms+10);

	while (TIM2->CNT < ms)
		;
	TIM2->CR1 &= ~(0x01);
}
