/*  Abram Gad   -   Amr Mohamed   -  Mahmude Hamdy  -  Naira Youssef */
/*  TEAM  8  */
#include "Std_Types.h"
#include "Bit_Operations.h"
#include "Rcc.h"
#include "Gpio.h"
#include "EXTI.h"
#include "GPT.h"

typedef enum
{
	LOCKED,
	UNLOCKED
} Lock_Type;

typedef enum{
	DOOR_CLOSING,
	DOOR_OPENING,
	HANDEL_CLOSING,
	HANDEL_OPENING,
	ANTI_THIFT,
	NO_ACTION
}Actions_Type;


/*****************************************************************************************************/
/*                                   Function  & Global var Declaration                              */
/*****************************************************************************************************/
	void Handel_btn_handeler(void);
	void DoorLock_btn_handeler(void);
	uint8 Door_State ,Handel_State;
	uint8 next_action ;
	uint8 Change_Flag =0;

/*****************************************************************************************************/

int main()
{
	Rcc_Init();
	Rcc_Enable(RCC_GPIOA);
	Rcc_Enable(RCC_GPIOB);
	Rcc_Enable(RCC_GPIOD);
	Exti_Init(GPIO_A, 0, EXTI_DETECT_FALLING, Handel_btn_handeler);
	Exti_Init(GPIO_B, 1, EXTI_DETECT_FALLING, DoorLock_btn_handeler);
	GPT_Init();
	/**********************************************************************************************************************/
	/*                                        Input Output Configrations                                                  */
	/**********************************************************************************************************************/
		Gpio_ConfigPin(GPIO_D, 0, GPIO_OUTPUT, GPIO_PUSH_PULL);
		Gpio_ConfigPin(GPIO_D, 1, GPIO_OUTPUT, GPIO_PUSH_PULL);
		Gpio_ConfigPin(GPIO_D, 2, GPIO_OUTPUT, GPIO_PUSH_PULL);
		Exti_Enable(0);
		Exti_Enable(1);
	/**********************************************************************************************************************/
	/*                                        End Of Input Output Configrations                                           */
	/**********************************************************************************************************************/

	/**********************************************************************************************************************/
	/*                                            Default State                                                           */
	/**********************************************************************************************************************/
		Handel_State = LOCKED;
		Door_State = LOCKED;
		next_action =NO_ACTION ;
		Gpio_WritePin(GPIO_D, 0, LOW);
		Gpio_WritePin(GPIO_D, 1, LOW);
		Gpio_WritePin(GPIO_D, 2, LOW);
	/**********************************************************************************************************************/
	/*                                        End Of  Default State                                                       */
	/**********************************************************************************************************************/
	while (1)
	{
		switch(next_action)
		{
			case HANDEL_OPENING:
				if(Change_Flag==0)
				{
					GPT_StartTimer(10100);
					Handel_State= UNLOCKED;  /*Change State Of Handel*/
					Gpio_WritePin(GPIO_D, 0, HIGH);  /*Vehicle lock LED is on*/
					Gpio_WritePin(GPIO_D, 1, HIGH);
					Gpio_WritePin(GPIO_D, 2, HIGH);
					Change_Flag=1;
				}
				else
				{

					/**************************************************************************/
					/*   Hazard LED is blinking one time 0.5 second high and 0.5 second low   */
					/**************************************************************************/
						if (GPT_GetElapsedTime() > 500)
						{
							Gpio_WritePin(GPIO_D, 1, LOW);
						}
					/**************************************************************************/
					


					/**************************************************************************/
					/*             Ambient light LED is on for 2 seconds then off             */
					/**************************************************************************/
						if (GPT_GetElapsedTime() > 2000)
						{
							Gpio_WritePin(GPIO_D, 2, LOW);
						}
					/**************************************************************************/

					/**************************************************************************/
					/*                    No buttons pressed for 10 seconds                   */
					/**************************************************************************/
						if(GPT_GetElapsedTime() > 10000)
						{
							next_action=ANTI_THIFT;
							Handel_State= LOCKED;
							Change_Flag=0;
						}
					/**************************************************************************/

				}
				break;
			case HANDEL_CLOSING:
				if(Door_State==LOCKED)/* Can Not Lock The Handel If Door Is Opened */
				{
					if (Change_Flag == 0)
					{
						GPT_StartTimer(2000);
						Handel_State=LOCKED; /*Change State Of Handel*/
						Gpio_WritePin(GPIO_D, 0, LOW);
						Gpio_WritePin(GPIO_D, 2, LOW);
						Gpio_WritePin(GPIO_D, 1, HIGH);
						Change_Flag = 1;
					}
					else
					{
						static uint8 i=0;
						/**************************************************************************/
						/*   Hazard LED is blinking two time 0.5 second high and 0.5 second low   */
						/**************************************************************************/
							if((GPT_GetElapsedTime() > 500)&&i==0)
							{
								Gpio_WritePin(GPIO_D, 1, LOW);
								i++;
							}
							else if ((GPT_GetElapsedTime() > 1000)&&i==1)
							{
								Gpio_WritePin(GPIO_D, 1, HIGH);
								i++;
							}
							else if((GPT_GetElapsedTime() > 1500)&&i==2)
							{
								Gpio_WritePin(GPIO_D, 1, LOW);
								i++;
							}
							if(i==3)
							{
								i=0;
								next_action=NO_ACTION;
							}
						/**************************************************************************/
					}
				}
				break;
			case DOOR_OPENING:
				if (Handel_State==UNLOCKED)/* Can Not Open The Door If Handel Is Locked */
				{
					Door_State = UNLOCKED;
					Gpio_WritePin(GPIO_D, 2, HIGH);
					next_action= NO_ACTION;
				}
				break;
			case DOOR_CLOSING:
				if (Change_Flag == 0)
				{
					GPT_StartTimer(2000);
					Door_State = LOCKED; /*Change State Of door*/
					Gpio_WritePin(GPIO_D, 0, LOW);
					Gpio_WritePin(GPIO_D, 1, LOW);
					Change_Flag = 1;
				}
				else
				{
					if (GPT_GetElapsedTime() > 1000)
					{
						Gpio_WritePin(GPIO_D, 2, LOW);
						next_action=NO_ACTION;
					}
				}
				break;
			case ANTI_THIFT:
				if (Change_Flag == 0) {
					GPT_StartTimer(2000);
					Handel_State = LOCKED; /*Change State Of Handel*/
					Gpio_WritePin(GPIO_D, 0, LOW);
					Gpio_WritePin(GPIO_D, 2, LOW);
					Gpio_WritePin(GPIO_D, 1, HIGH);
					Change_Flag = 1;
				}
				else
				{
					static uint8 i = 0;
					if ((GPT_GetElapsedTime() > 500) && i == 0) {
						Gpio_WritePin(GPIO_D, 1, LOW);
						i++;
					} else if ((GPT_GetElapsedTime() > 1000) && i == 1) {
						Gpio_WritePin(GPIO_D, 1, HIGH);
						i++;
					} else if ((GPT_GetElapsedTime() > 1500) && i == 2) {
						Gpio_WritePin(GPIO_D, 1, LOW);
						i++;
					}
					if (i == 3) {
						i = 0;
						next_action = NO_ACTION;
					}
				}
				break;

		}


	}
	return 0;
}

/**********************************************************************************************************************/
/*                                         Interrupt handelers                                                        */
/**********************************************************************************************************************/
	void Handel_btn_handeler(void) {
		if(Handel_State==UNLOCKED)
		{
			next_action =HANDEL_CLOSING;
		}
		else
		{
			next_action =HANDEL_OPENING;
		}
		Change_Flag=0;
	}
	void DoorLock_btn_handeler(void) {
		if(Door_State==UNLOCKED)
		{
			next_action =DOOR_CLOSING;
		}
		else
		{
			next_action =DOOR_OPENING;
		}
		Change_Flag=0;
	}
/**********************************************************************************************************************/
/*                                        End Interrupt handelers                                                     */
/**********************************************************************************************************************/
