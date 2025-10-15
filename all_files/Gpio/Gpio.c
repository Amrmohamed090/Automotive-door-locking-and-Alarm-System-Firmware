/*  Abram Gad   -   Amr Mohamed   -  Mahmude Hamdy  -  Naira Youssef */
/*  TEAM  8  */

#include "Gpio.h"
#include "Gpio_Private.h"


void Gpio_ConfigPin(uint8 PortName, uint8 PinNum, uint8 PinMode,
                    uint8 DefaultState)
{
  switch (PortName)
  {
  case GPIO_A:
    GPIOA->MODER &= ~(0x03 << (PinNum * 2));
    GPIOA->MODER |= (PinMode << (PinNum * 2));
    switch (PinMode)
    {
    case GPIO_OUTPUT:
      GPIOA->OTYPER &= ~(0x01 << PinNum);
      GPIOA->OTYPER |= (DefaultState << PinNum);

      break;
    case GPIO_INPUT:
      GPIOA->PUPDR &= ~(0x03 << (PinNum * 2));
      GPIOA->PUPDR |= (DefaultState << (PinNum * 2));
      break;
    default:
      break;
    }
    break;
  case GPIO_B:
    GPIOB->MODER &= ~(0x03 << (PinNum * 2));
    GPIOB->MODER |= (PinMode << (PinNum * 2));

    switch (PinMode)
    {
    case GPIO_OUTPUT:
      GPIOB->OTYPER &= ~(0x01 << PinNum);
      GPIOB->OTYPER |= (DefaultState << PinNum);

      break;
    case GPIO_INPUT:
      GPIOB->PUPDR &= ~(0x03 << (PinNum * 2));
      GPIOB->PUPDR |= (DefaultState << (PinNum * 2));
      break;
    default:
      break;
    }

    break;
  case GPIO_C:
    // TODO:
    GPIOC->MODER &= ~(0x03 << (PinNum * 2));
    GPIOC->MODER |= (PinMode << (PinNum * 2));

    switch (PinMode)
    {
    case GPIO_OUTPUT:
      GPIOC->OTYPER &= ~(0x01 << PinNum);
      GPIOC->OTYPER |= (DefaultState << PinNum);

      break;
    case GPIO_INPUT:
      GPIOC->PUPDR &= ~(0x03 << (PinNum * 2));
      GPIOC->PUPDR |= (DefaultState << (PinNum * 2));
      break;
    default:
      break;
    }
    break;
  case GPIO_D:
    // TODO:
    GPIOD->MODER &= ~(0x03 << (PinNum * 2));
    GPIOD->MODER |= (PinMode << (PinNum * 2));

    switch (PinMode)
    {
    case GPIO_OUTPUT:
      GPIOD->OTYPER &= ~(0x01 << PinNum);
      GPIOD->OTYPER |= (DefaultState << PinNum);

      break;
    case GPIO_INPUT:
      GPIOD->PUPDR &= ~(0x03 << (PinNum * 2));
      GPIOD->PUPDR |= (DefaultState << (PinNum * 2));
      break;
    default:
      break;
    }
    break;
  case GPIO_E:
    // TODO:
    GPIOE->MODER &= ~(0x03 << (PinNum * 2));
    GPIOE->MODER |= (PinMode << (PinNum * 2));

    switch (PinMode)
    {
    case GPIO_OUTPUT:
      GPIOE->OTYPER &= ~(0x01 << PinNum);
      GPIOE->OTYPER |= (DefaultState << PinNum);

      break;
    case GPIO_INPUT:
      GPIOE->PUPDR &= ~(0x03 << (PinNum * 2));
      GPIOE->PUPDR |= (DefaultState << (PinNum * 2));
      break;
    default:
      break;
    }
    break;
  case GPIO_H:
    // TODO:
    GPIOH->MODER &= ~(0x03 << (PinNum * 2));
    GPIOH->MODER |= (PinMode << (PinNum * 2));

    switch (PinMode)
    {
    case GPIO_OUTPUT:
      GPIOH->OTYPER &= ~(0x01 << PinNum);
      GPIOH->OTYPER |= (DefaultState << PinNum);

      break;
    case GPIO_INPUT:
      GPIOH->PUPDR &= ~(0x03 << (PinNum * 2));
      GPIOH->PUPDR |= (DefaultState << (PinNum * 2));
      break;
    default:
      break;
    }
    break;
  default:
    break;
  }
}

uint8 Gpio_WritePin(uint8 PortName, uint8 PinNum, uint8 Data)
{

  // TODO: check if the pin is output
  switch (PortName)
  {
  case GPIO_A:
    if ((GPIOA->MODER & (3 << (PinNum * 2))) >> (PinNum * 2) == 1)
    {
      GPIOA->ODR &= ~(0x1 << PinNum);
      GPIOA->ODR |= (Data << PinNum);
      return OK;
    }
    else
    {
      return NOK;
    }

    break;
  case GPIO_B:
    if ((GPIOB->MODER & (3 << (PinNum * 2))) >> (PinNum * 2) == 1)
    {
      GPIOB->ODR &= ~(0x1 << PinNum);
      GPIOB->ODR |= (Data << PinNum);
      return OK;
    }
    else
    {
      return NOK;
    }
    break;

  case GPIO_C:
    // TODO:
    if ((GPIOC->MODER & (3 << (PinNum * 2))) >> (PinNum * 2) == 1)
    {
      GPIOC->ODR &= ~(0x1 << PinNum);
      GPIOC->ODR |= (Data << PinNum);
      return OK;
    }
    else
    {
      return NOK;
    }
    break;
  case GPIO_D:
    // TODO:
    if ((GPIOD->MODER & (3 << (PinNum * 2))) >> (PinNum * 2) == 1)
    {
      GPIOD->ODR &= ~(0x1 << PinNum);
      GPIOD->ODR |= (Data << PinNum);
      return OK;
    }
    else
    {
      return NOK;
    }
    break;
  case GPIO_E:
    // TODO:
    if ((GPIOE->MODER & (3 << (PinNum * 2))) >> (PinNum * 2) == 1)
    {
      GPIOE->ODR &= ~(0x1 << PinNum);
      GPIOE->ODR |= (Data << PinNum);
      return OK;
    }
    else
    {
      return NOK;
    }
    break;
  case GPIO_H:
    // TODO:
    if ((GPIOH->MODER & (3 << (PinNum * 2))) >> (PinNum * 2) == 1)
    {
      GPIOH->ODR &= ~(0x1 << PinNum);
      GPIOH->ODR |= (Data << PinNum);
      return OK;
    }
    else
    {
      return NOK;
    }
    break;
  default:
    break;
  }
}

uint8 GPIO_ReadPin(uint8 PortName, uint8 PinNum)
{
  uint8 value = LOW;
  switch (PortName)
  {
  case GPIO_A:
    /* code */
    value = (GPIOA->IDR & (1 << PinNum)) >> PinNum;
    break;
  case GPIO_B:
    /* code */
    value = (GPIOB->IDR & (1 << PinNum)) >> PinNum;
    break;
  case GPIO_C:
    /* code */
    value = (GPIOC->IDR & (1 << PinNum)) >> PinNum;
    break;
  case GPIO_D:
    /* code */
    value = (GPIOD->IDR & (1 << PinNum)) >> PinNum;
    break;
  case GPIO_E:
    /* code */
    value = (GPIOE->IDR & (1 << PinNum)) >> PinNum;
    break;
  case GPIO_H:
    /* code */
    value = (GPIOH->IDR & (1 << PinNum)) >> PinNum;
    break;
  default:
    break;
  }
  return value;
}
