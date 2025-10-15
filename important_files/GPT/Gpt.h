/*  Abram Gad   -   Amr Mohamed   -  Mahmude Hamdy  -  Naira Youssef */
/*  TEAM  8  */


#ifndef GPT_H
#define GPT_H


void GPT_Init(void);
void GPT_StartTimer(uint64 OverFlowTicks);
uint8 GPT_CheckTimeIsElapsed(void);
uint64 GPT_GetElapsedTime(void);
uint64 GPT_GetRemainingTime(void);
void GPT_StopTimer(void);
void delay_ms(uint32 ms);


#endif
