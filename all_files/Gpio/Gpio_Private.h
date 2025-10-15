/*  Abram Gad   -   Amr Mohamed   -  Mahmude Hamdy  -  Naira Youssef */
/*  TEAM  8  */

#ifndef GPIO_PRIVATE_H
#define GPIO_PRIVATE_H


typedef struct{
	uint32 MODER;
	uint32 OTYPER;
	uint32 OSPEEDR;
	uint32 PUPDR;
	uint32 IDR;
	uint32 ODR;
	uint32 BSRR;
	uint32 LCKR;
	uint32 AFRL;
	uint32 AFRH;
}GPIO_Type;


#define GPIOA ((GPIO_Type *)0x40020000)

#define GPIOB ((GPIO_Type *)0x40020400)

#define GPIOC ((GPIO_Type *)0x40020800)

#define GPIOD ((GPIO_Type *)0x40020C00)

#define GPIOH ((GPIO_Type *)0x40021C00)

#define GPIOE ((GPIO_Type *)0x40021000)


#endif /* GPIO_PRIVATE_H */
