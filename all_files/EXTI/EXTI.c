/*  Abram Gad   -   Amr Mohamed   -  Mahmude Hamdy  -  Naira Youssef */
/*  TEAM  8  */

#include "Std_Types.h"
#include "Bit_Operations.h"
#include "Gpio.h"
#include "Rcc.h"
#include "EXTI.h"

void (*EXTI0_Callback)(void);
void (*EXTI1_Callback)(void);
void (*EXTI2_Callback)(void);
void (*EXTI3_Callback)(void);
void (*EXTI4_Callback)(void);
void (*EXTI9_5_Callback)(void);
void (*EXTI15_10_Callback)(void);

volatile uint8 pin_number;

void Exti_Init(uint8 port_name, uint8 pin_num, EXTI_EdgeType edge, void (*callback)(void))
{
    Rcc_Enable(RCC_SYSCFG);
    /********************************************************************************************************/
    /*                       Select The Pin In The EXTI Multiplexer Section Start                           */
    /********************************************************************************************************/
        /*******************************************/
        /*    Choose The Proper Selection Value    */
        /*******************************************/
            uint32 selection_value;
            switch (port_name)
            {
            case GPIO_A:
                selection_value = PORTA_SELECTION;
                break;
            case GPIO_B:
                selection_value = PORTB_SELECTION;
                break;
            case GPIO_C:
                selection_value = PORTC_SELECTION;
                break;
            case GPIO_D:
                selection_value = PORTD_SELECTION;
                break;
            default:
                break;
            }
        /*******************************************/
        /*                   END                   */
        /*******************************************/

        /***************************************************/
        /*   Apply Selection Value On The Right Register   */
        /***************************************************/
            switch (pin_num)
            {
            case 0:
            case 1:
            case 2:
            case 3:
                SYSCFG->EXTICR1|=  (selection_value << ((pin_num%4) * 4));
                break;

            case 4:
            case 5:
            case 6:
            case 7:
               SYSCFG->EXTICR2 |= (selection_value << ((pin_num%4) * 4));
                break;
            case 8:
            case 9:
            case 10:
            case 11:
               SYSCFG->EXTICR3 |= (selection_value << ((pin_num%4) * 4));
                break;
            case 12:
            case 13:
            case 14:
            case 15:
                SYSCFG->EXTICR4 |= (selection_value << ((pin_num%4)* 4));
                break;
            default:
                break;
            }
        /***************************************************/
        /*                       END                       */
        /***************************************************/
    /********************************************************************************************************/
    /*                        Select Phe Pin In The EXTI Multiplexer Section End                            */
    /********************************************************************************************************/

     
    /********************************************************************************************************/
    /*                           Select Edge & ISR & GPIO confgration Section Start                         */
    /********************************************************************************************************/
        switch (edge)       
        {
        case EXTI_DETECT_FALLING:
            SET_BIT(EXTI->FTSR, pin_num);
            Gpio_ConfigPin(port_name, pin_num, GPIO_INPUT, GPIO_INPUT_PULL_UP);
            break;
        case EXTI_DETECT_RISING:
            SET_BIT(EXTI->RTSR, pin_num);
            Gpio_ConfigPin(port_name, pin_num, GPIO_INPUT, GPIO_INPUT_PULL_DOWN);
            break;
        case EXTI_DETECT_CHANGE:
        	 SET_BIT(EXTI->FTSR, pin_num);
        	 SET_BIT(EXTI->RTSR, pin_num);
        	 Gpio_ConfigPin(port_name, pin_num, GPIO_INPUT, GPIO_INPUT_PULL_UP);
        	 break;
        default:
            break;
        }
        switch (pin_num)
        {
        case 0:
            EXTI0_Callback = callback;
            break;
        case 1:
            EXTI1_Callback = callback;
            break;
        case 2:
            EXTI2_Callback = callback;
            break;
        case 3:
            EXTI3_Callback = callback;
            break;
        case 4:
            EXTI4_Callback = callback;
            break;
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            EXTI9_5_Callback = callback;
            break;
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
            EXTI15_10_Callback = callback;
            break;
        default:
            break;
        }
        pin_number = pin_num;

     /********************************************************************************************************/
     /*                                  Select Edge & ISR Section End                                       */
     /********************************************************************************************************/

}
void Exti_Enable(uint8 pin_num)
{
    /********************************************************************************************************/
    /*                                  Enable EXTI & NIVC Section Start                                    */
    /********************************************************************************************************/
        SET_BIT(EXTI->IMR, pin_num);
        SET_BIT(NVIC_ISER0, (pin_num + 6));
    
    /********************************************************************************************************/
    /*                                  Enable EXTI & NIVC Section End                                      */
    /********************************************************************************************************/
}
void Exti_Disable( uint8 pin_num)
{
    /********************************************************************************************************/
    /*                                  Dsiable EXTI & NIVC Section Start                                    */
    /********************************************************************************************************/
        CLEAR_BIT(EXTI->IMR, pin_num);
        CLEAR_BIT(NVIC_ISER0, (pin_num + 6));
    
    /********************************************************************************************************/
    /*                                  Disable EXTI & NIVC Section End                                      */
    /********************************************************************************************************/
}


void EXTI0_IRQHandler(void){
    EXTI0_Callback();
	//clear pending flag
	SET_BIT(EXTI->PR, pin_number);
}
void EXTI1_IRQHandler(void){
    EXTI1_Callback();
	//clear pending flag
	SET_BIT(EXTI->PR, pin_number);
}
void EXTI2_IRQHandler(void){
    EXTI2_Callback();
	//clear pending flag
	SET_BIT(EXTI->PR, pin_number);
}
void EXTI3_IRQHandler(void){
    EXTI3_Callback();
	SET_BIT(EXTI->PR, pin_number);
}
void EXTI4_IRQHandler(void){
    EXTI4_Callback();
	SET_BIT(EXTI->PR, pin_number);
}
void EXTI9_5_IRQHandler(void){
    EXTI9_5_Callback();
	SET_BIT(EXTI->PR, pin_number);
}
void EXTI15_10_IRQHandler(void){
    EXTI15_10_Callback();
	SET_BIT(EXTI->PR, pin_number);
}
