/*  Abram Gad   -   Amr Mohamed   -  Mahmude Hamdy  -  Naira Youssef */
/*  TEAM  8  */

#ifndef GPT_PRIVET_H_
#define GPT_PRIVET_H_


typedef struct {
	uint32 CR1;
	uint32 CR2;
	uint32 SMCR;
	uint32 DIER;
	uint32 SR;
	uint32 EGR;
	uint32 CCMR1;
	uint32 CCMR2;
	uint32 CCER;
	uint32 CNT;
	uint32 PSC;
	uint32 ARR;
	uint32 reserved;
	uint32 CCR1;
	uint32 CCR2;
	uint32 CCR3;
	uint32 CCR4;
	uint32 reserved2;
	uint32 DCR;
	uint32 DMAR;
	uint32 OR;
} TimerType;


#define TIM2 ((TimerType *)0x40000000)




#endif /* GPT_PRIVET_H_ */
