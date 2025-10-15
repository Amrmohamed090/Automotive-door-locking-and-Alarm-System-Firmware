/*  Abram Gad   -   Amr Mohamed   -  Mahmude Hamdy  -  Naira Youssef */
/*  TEAM  8  */
#ifndef EXTI_H
#define EXTI_H

typedef struct
{
	uint32 IMR;
	uint32 EMR;
	uint32 RTSR;
	uint32 FTSR;
	uint32 SWIER;
	uint32 PR;
} ExtiType;

typedef struct
{
	uint32 MEMRMP;
	uint32 PMC;
	uint32 EXTICR1;
	uint32 EXTICR2;
	uint32 EXTICR3;
	uint32 EXTICR4;
} SYSCFGType;

typedef enum
{
	EXTI_DETECT_FALLING,
	EXTI_DETECT_RISING,
	EXTI_DETECT_CHANGE
} EXTI_EdgeType;

#define EXTI ((ExtiType *)0x40013C00)
#define SYSCFG ((SYSCFGType *)0x40013800)
#define NVIC_ISER0 (*(uint32 *)0xE000E100)

#define PORTA_SELECTION 0x00
#define PORTB_SELECTION 0x01
#define PORTC_SELECTION 0x02
#define PORTD_SELECTION 0x03

void Exti_Init(uint8 port_name, uint8 pin_num, EXTI_EdgeType edge, void (*callback)(void));
void Exti_Enable( uint8 pin_num);
void Exti_Disable( uint8 pin_num);

#endif
