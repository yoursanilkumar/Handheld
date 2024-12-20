#include "main.h"

int Index = 1;
int count;
int check_release,relese_couter;	

uint8_t  One = 0x01, Two = 0x02, Three = 0x03, Four = 0x04, Five = 0x05, Six = 0x06, Seven = 0x07, Eight = 0x08, Nine = 0x09,GUI = 0x0A;

void Keypad_Init(void)
{
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB); //LED
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); //KEY
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	
 //  This is using for the PD7 Pin
	HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
	HWREG(GPIO_PORTD_BASE + GPIO_O_CR) |= 0x80;
	HWREG(GPIO_PORTD_BASE + GPIO_O_AFSEL) &= 0x80;
	HWREG(GPIO_PORTD_BASE + GPIO_O_DEN) |= 0x80;
	//HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = 0;

	
									/******* KEYPAD PB *********/
	ROM_GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PIN_0);
	ROM_GPIOPadConfigSet(GPIO_PORTB_BASE, GPIO_PIN_0, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);
		
									/******* KEYPAD PF********/
	ROM_GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_2 | GPIO_PIN_3 );
	ROM_GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);
	ROM_GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);
	
									/******* KEYPAD PD*********/
	ROM_GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, GPIO_PIN_6 | GPIO_PIN_7);
	ROM_GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_6, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);
	ROM_GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_7, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);
	ROM_GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, GPIO_PIN_5);
	//ROM_GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_5);
	ROM_GPIOPadConfigSet(GPIO_PORTD_BASE, GPIO_PIN_5, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_OD);
									/******* KEYPAD PE *********/
	ROM_GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_0 | GPIO_PIN_1);
	ROM_GPIOPadConfigSet(GPIO_PORTE_BASE, GPIO_PIN_3, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD); 
	ROM_GPIOPadConfigSet(GPIO_PORTE_BASE, GPIO_PIN_0, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);
	ROM_GPIOPadConfigSet(GPIO_PORTE_BASE, GPIO_PIN_1, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);
	ROM_GPIOPadConfigSet(GPIO_PORTE_BASE, GPIO_PIN_2, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);
}

void KeyPad_Cyclic(void)
{
	//ROM_GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0);
	//UARTprintf("Index : %d\r\n", Index);	
	/*
	switch(Index)
	{
		case 1 : 	
							ROM_GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, GPIO_PIN_2); //ROW1
							ROM_GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, 0); //ROW2
					
							check_release = ROM_GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_3);
							
		if(check_release)
		{
		}
		else
		{
			relese_couter++;
	//		UARTprintf("Count Value-->>%d\n\n",count);
			if(relese_couter > 1 || relese_couter < 11)
			{
//				UARTprintf("GUI Pin release-->>\n\n");
				count = 0;
			}
		}
			
							if(ROM_GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_2) > 0)
							{
								UART1_PutString("5\r\n");
								count = 0;
							}
							else if(ROM_GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_3) > 0)
							{
								UART1_PutString("1\r\n");
								count = 0;
							}
							else if(ROM_GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_6) > 0)
							{
								UART1_PutString("2\r\n");
								count = 0;
							}
							else if(ROM_GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_7) > 0)
							{
								UART1_PutString("3\r\n");
								count = 0;
							}
							else if(ROM_GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_3) > 0)
							{
								count++;
								
							if(count == 11)  //count = 11 means 5 seconds
								{
									UART1_PutString("0\r\n");
									//UART1_PutString("second\r\n");
									
									check_release = ROM_GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_3);
									if(check_release)
									{}
										else
										{
											count = 0;
										}
									
								}
								else
								{
									if(count == 1)
									{
											UART1_PutString("6\r\n");
											
										//UART1_PutString("first\r\n");									
									}

								}		
								
							}
							Index = 2;
							break;
							
		case 2 : 
							ROM_GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, 0); //ROW1 KEY6
							ROM_GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, GPIO_PIN_1); //ROW2	 KEY7
							if(ROM_GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_2) > 0)
							{
								UART1_PutString("8\r\n");
								count = 0;
							}
							else if(ROM_GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_3) > 0)
							{
								UART1_PutString("4\r\n"); //DPY
								count = 0;
							}
							else if(ROM_GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_6) > 0)
							{
								UART1_PutString("7\r\n");
								count = 0;
							}
							else if(ROM_GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_7) > 0)
							{
								UART1_PutString("9\r\n");
								count = 0;
							}
							else if(ROM_GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_3) > 0)
							{
								UART1_PutString("A\r\n");
								count = 0;
							}
							Index = 1;
							break;
		} */
		
						//	ROM_GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_2, GPIO_PIN_2); //ROW1
							//ROM_GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_1, 0); //ROW2
		
	  if(ROM_GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_3) > 0)
		{
			UART1_PutString("1\r\n");
			//UART1_WriteChar(One);
		}
		else if(ROM_GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_6) > 0)
		{
			UART1_PutString("2\r\n");
			//UART1_WriteChar(Two);
			
		}
		else if(ROM_GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_7) > 0)
		{
			UART1_PutString("3\r\n");
			//UART1_WriteChar(Three);
		}
		else if(ROM_GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_2) > 0)
		{
			UART1_PutString("4\r\n");
			//UART1_WriteChar(Four);
		}
		if(ROM_GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_2) > 0)
		{
			UART1_PutString("5\r\n");
			//UART1_WriteChar(Five);
			//ROM_GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_5, GPIO_PIN_5);
		}
		else if(ROM_GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_3) > 0)
		{
			UART1_PutString("A\r\n");
			//UART1_WriteChar(GUI);
		}
		else if (ROM_GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_0) > 0)
		{
			UART1_PutString("6\r\n");
			//UART1_WriteChar(Six);
		}
		else if(ROM_GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_1) > 0)
		{
			UART1_PutString("7\r\n");
			//UART1_WriteChar(Seven);
		}
		else if(ROM_GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_0) > 0)
		{
			UART1_PutString("9\r\n");
			//UART1_WriteChar(Nine);
		}
		else if(ROM_GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_5) > 0) // cant able to detect
		{
			UART1_PutString("8\r\n");
			//UART1_WriteChar(Eight);
		}
}