/*  Abram Gad   -   Amr Mohamed   -  Mahmude Hamdy  -  Naira Youssef */
/*  TEAM  8  */

#ifndef GPIOFILE_H
#define GPIOFILE_H
#include "Std_Types.h"

/*PortName*/
#define GPIO_A 'A'
#define GPIO_B 'B'
#define GPIO_C 'C'
#define GPIO_D 'D'
#define GPIO_H 'H'
#define GPIO_E 'E'

/*PinMode*/
#define GPIO_INPUT 0x00
#define GPIO_OUTPUT 0x01
#define GPIO_AF 0x02
#define GPIO_ANALOG 0x03

/*DefaultState Output */
#define GPIO_PUSH_PULL 0x00
#define GPIO_OPEN_DRAIN 0x01

/*DefaultState input */
#define GPIO_INPUT_PULL_UP 0x01
#define GPIO_INPUT_PULL_DOWN 0x02
#define GPIO_INPUT_NO_PULL 0x00

/*Data*/
#define LOW 0x00
#define HIGH 0x01

/*state*/
#define OK 0x00
#define NOK 0x01

void Gpio_ConfigPin(uint8 PortName, uint8 PinNum, uint8 PinMode, uint8 DefaultState);

uint8 Gpio_WritePin(uint8 PortName, uint8 PinNum, uint8 Data);
uint8 GPIO_ReadPin(uint8 PortName, uint8 PinNum);

#endif /* GPIO_H */
