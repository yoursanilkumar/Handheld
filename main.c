//*****************************************************************************
//
// hello.c - Simple hello world example.
//
// Copyright (c) 2011-2017 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 2.1.4.178 of the DK-TM4C123G Firmware Package.
//
//*****************************************************************************

#include "main.h"

#define    RED  0x0000FF
#define  GREEN  0x00FF00
#define   BLUE  0xFF0000
#define  WHITE  0xFFFFFF
#define  BLACK  0x000000
//*****************************************************************************
//
//! \addtogroup example_list
//! <h1>Hello World (hello)</h1>
//!
//! A very simple ``hello world'' example.  It simply displays ``Hello World!''
//! on the display and is a starting point for more complicated applications.
//! This example uses calls to the TivaWare Graphics Library graphics
//! primitives functions to update the display.  For a similar example using
//! widgets, please see ``hello_widget''.
//
//*****************************************************************************

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif


static unsigned char data_check = 0;
unsigned char Serial_Date[50] = {0};
uint8_t commands[256] = {0};
int indx = 0;
bool sign_check = false;
bool sign_check1 = false;
//*****************************************************************************
//
// Configure the UART and its pins.  This must be called before UARTprintf().
//
//*****************************************************************************
void
ConfigureUART(void)
{
    //
    // Enable the GPIO Peripheral used by the UART.
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Enable UART0
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    //
    // Configure GPIO Pins for UART mode.
    //
    ROM_GPIOPinConfigure(GPIO_PA0_U0RX);
    ROM_GPIOPinConfigure(GPIO_PA1_U0TX);
    ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Use the internal 16MHz oscillator as the UART clock source.
    //
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(0, 115200, 16000000);

}

void App_Systick(void)
{
	NHD15128128G_TickHandler();
}
Serial_pack_struc Serial_Packet;

unsigned char values[20] = {0};
void convert_float(void)
{
	float first_val = 0, Second_val = 0, Thrid_val = 0, Seven_val = 0;
	first_val = Serial_Packet.val_ONE.fval;
	Second_val = Serial_Packet.val_TWO.fval;
	Thrid_val = Serial_Packet.val_THREE.fval;
	Seven_val = Serial_Packet.val_SEVEN.fval;
	
	values[0] = first_val / 100.00;
	//UARTprintf("values[0] %d\r\n", values[0]);
	first_val = (first_val - (values[0] * 100.00));
	values[1] = first_val / 10.00;
	//UARTprintf("values[1] %d\r\n", values[1]);
	first_val = (first_val - (values[1] * 10.00));
	values[2] = first_val / 1.00;
	//UARTprintf("values[2] %d\r\n", values[2]);
	first_val = (first_val - (values[2] * 1.00));
	values[3] = first_val / 0.10;
	//UARTprintf("values[3] %d\r\n", values[3]);
	first_val = (first_val - (values[3] * 0.10));
	values[4] = (first_val / 0.01) + 0.5;
	if(values[4] > 5)
	{
	}
	else
	{
		values[4] = values[4] + 0.5;		
	}
		
	
	values[5] = Second_val / 10.00;
	//UARTprintf("values[5] %d\r\n", values[5]);
	Second_val = (Second_val - (values[5] * 10.00));
	values[6] = Second_val / 1.00;
	//UARTprintf("values[6] %d\r\n", values[6]);
	Second_val = (Second_val - (values[6] * 1.00));
	values[7] = (Second_val / 0.10);
	//UARTprintf("values[7] %d\r\n", values[7]);
	Second_val = (Second_val - (values[7] * 0.10));
	values[8] = (Second_val / 0.01); // + 0.5;
	//UARTprintf("values[8] %d\r\n", values[8]);

	
	values[9] = Thrid_val / 10.00;
	//UARTprintf("values[9] %d\r\n", values[9]);
	Thrid_val = (Thrid_val - (values[9] * 10.00));
	values[10] = Thrid_val / 1.00;
	//UARTprintf("values[6] %d\r\n", values[10]);
	Thrid_val = (Thrid_val - (values[10] * 1.00));
	values[11] = (Thrid_val / 0.10);
	//UARTprintf("values[11] %d\r\n", values[11]);
	Thrid_val = (Thrid_val - (values[11] * 0.10));
	values[12] = (Thrid_val / 0.01);// + 0.5;
	//UARTprintf("values[12] %d\r\n", values[12]);
	
	values[13] = Seven_val / 10.00;
	//UARTprintf("values[9] %d\r\n", values[9]);
	Seven_val = (Seven_val - (values[13] * 10.00));
	values[14] = Seven_val / 1.00;
	//UARTprintf("values[6] %d\r\n", values[10]);
	Seven_val = (Seven_val - (values[14] * 1.00));
	values[15] = (Seven_val / 0.10);
	//UARTprintf("values[11] %d\r\n", values[11]);
	Seven_val = (Seven_val - (values[15] * 0.10));
	values[16] = (Seven_val / 0.01);// + 0.5;
	//UARTprintf("values[12] %d\r\n", values[12]);	
}

void Command_Parser(const char *buff, int size)
{
	unsigned char data[150] = {0};
//	UARTprintf("Command_Parser %s\r\n", buff);

	//sscanf(buff, "$A:|%f|%d|%d|%f|%d|%d|%f|%d|%d|%d|%d|", &Serial_Packet.val_ONE.ival, &Serial_Packet.data_check_ONE, &Serial_Packet.data_check_TWO, &Serial_Packet.val_TWO.ival, &Serial_Packet.data_check_THREE, &Serial_Packet.data_check_FOUR, &Serial_Packet.val_THREE.ival, &Serial_Packet.data_check_FIVE, &Serial_Packet.data_check_SIX, &Serial_Packet.data_check_SEVEN, &Serial_Packet.data_check_EIGH);
//	char *token   =   strtok(buff, ",");	
//	char *token_1 = strtok(NULL, ",");					
//	char *token_2 = strtok(NULL, ",");
//	char *token_3 = strtok(NULL, ",");
//	char *token_4 = strtok(NULL, ",");
//	char *token_5 = strtok(NULL, ",");

//	UARTprintf("\n Token - %s\n",token);
//	UARTprintf("\n Token_1 - %s\n",token_1);
//	int value = atoi(token_1);
//	UARTprintf("\n Token_1 After Conversion- %d\n",value);

//	UARTprintf("\n Token_2 - %s\n",token_2);
//	UARTprintf("\n Token_3 - %s\n",token_3);
//	UARTprintf("\n Token_4 - %s\n",token_4);
//	UARTprintf("\n Token_5 - %s\n",token_5);

	sscanf(buff, "$A:%f,%d,%d;E:%c,%f,%d,%d;P:%c,%f,%d,%d;B:%f,%d#",&Serial_Packet.val_ONE.ival, &Serial_Packet.data_check_ONE, 
																														 &Serial_Packet.data_check_TWO, &Serial_Packet.sign, &Serial_Packet.val_TWO.ival, 
																														 &Serial_Packet.data_check_THREE, 
																														 &Serial_Packet.data_check_FOUR, &Serial_Packet.sign1,
																														 &Serial_Packet.val_THREE.ival, &Serial_Packet.data_check_FIVE, 
																														 &Serial_Packet.data_check_SIX, 
																														 &Serial_Packet.val_SEVEN.ival, 
																														 &Serial_Packet.data_check_EIGH);
		UARTprintf("buff[16]---------->>>>>%x\n\n\n\n",buff[16]);
		if(buff[16] == 0x2D)
			sign_check = true;
		
		else
			sign_check = false;
		
		UARTprintf("buff[30]---------->>>>>%x\n\n\n\n",buff[30]);
		if(buff[30] == 0x2D)
			sign_check1 = true;
		
		else
			sign_check1 = false;		
		
	sprintf(data, "%0.2f, %0.2f, %0.2f, %0.2f\r\n", Serial_Packet.val_ONE.fval,Serial_Packet.val_TWO.fval,Serial_Packet.val_THREE.fval,Serial_Packet.val_SEVEN.fval);
//	UARTprintf("After Scanf %s\r\n", buff);

	//	UARTprintf(data);
//	UARTprintf("val  %d, %d\r\n",  Serial_Packet.data_check_ONE, Serial_Packet.data_check_TWO);
//	UARTprintf("val  %d, %d\r\n",  Serial_Packet.data_check_THREE, Serial_Packet.data_check_FOUR);
//	UARTprintf("val  %d, %d\r\n",  Serial_Packet.data_check_FIVE, Serial_Packet.data_check_SIX);
//	UARTprintf("last %d : %d\r\n", Serial_Packet.data_check_SEVEN, Serial_Packet.data_check_EIGH);
	convert_float(); 
}
//*****************************************************************************
//Command_Parser
// Print "Hello World!" to the display.
//
//*****************************************************************************
char ch;
uint32_t g_ui32SysClock;
int
main(void)
{
    //
    // Set the clocking to run directly from the crystal.
    //
		
//			ROM_SysCtlClockSet(SYSCTL_SYSDIV_8 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |
//                       SYSCTL_XTAL_25MHZ);
	
	    g_ui32SysClock = MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                                             SYSCTL_OSC_MAIN | SYSCTL_USE_PLL |
                                             SYSCTL_CFG_VCO_480),
                                            120000000);
	
	
	  ROM_SysTickPeriodSet( ROM_SysCtlClockGet() / 1000);
    ROM_SysTickEnable();
    ROM_SysTickIntEnable();
    //
    // Initialize the UART.
    //
    ConfigureUART();
		
    UARTprintf("**** BEL... HAND HELD Board ****\r\n");
		
		UARTprintf("ROM_SysCtlClockGet %d HZ\r\n", ROM_SysCtlClockGet());
		
		NHD15128128G_SPI_Init();
				
		UART1_Init();
		
		NHD15128128G_Reset();

		OLED_Init_128128RGB(); 
		
		OLED_FillScreen_128128RGB(BLACK);
		
		Keypad_Init();
		
    while(1)
    {
			//OLED_Data_128128RGB(0xAA);
			OLED_Text2x_128128RGB(44, 110, 34, BLUE, BLACK);   
			OLED_Text2x_128128RGB(56, 110, 37, BLUE, BLACK);   
			OLED_Text2x_128128RGB(68, 110, 44, BLUE, BLACK); 
		
			OLED_Text_128128RGB(1, 95, 40, RED, BLACK);    //HAND HELD Control unit 
			OLED_Text_128128RGB(7, 95, 33, RED, BLACK);   
			OLED_Text_128128RGB(13, 95, 46, RED, BLACK); 
			OLED_Text_128128RGB(19, 95, 36, RED, BLACK);
			OLED_Text_128128RGB(25, 95, 00, RED, BLACK);
			OLED_Text_128128RGB(29, 95, 40, RED, BLACK); 
			OLED_Text_128128RGB(35, 95, 37, RED, BLACK);   
			OLED_Text_128128RGB(41, 95, 44, RED, BLACK);   
			OLED_Text_128128RGB(47, 95, 36, RED, BLACK);
			OLED_Text_128128RGB(53, 95, 00, RED, BLACK);		
			OLED_Text_128128RGB(57, 95, 35, RED, BLACK);
			OLED_Text_128128RGB(63, 95, 79, RED, BLACK);
			OLED_Text_128128RGB(69, 95, 78, RED, BLACK);
			OLED_Text_128128RGB(75, 95, 84, RED, BLACK);
			OLED_Text_128128RGB(81, 95, 82, RED, BLACK);
			OLED_Text_128128RGB(87, 95, 79, RED, BLACK);
			OLED_Text_128128RGB(93, 95, 76, RED, BLACK);
			OLED_Text_128128RGB(99, 95, 00, RED, BLACK);
			OLED_Text_128128RGB(103, 95, 85, RED, BLACK);
			OLED_Text_128128RGB(109, 95, 78, RED, BLACK);
			OLED_Text_128128RGB(115, 95, 73, RED, BLACK);
			OLED_Text_128128RGB(121, 95, 84, RED, BLACK);
			
			OLED_Text2x_128128RGB(0, 70, 33, GREEN, BLACK); 
			OLED_Text2x_128128RGB(10, 70, 26, GREEN, BLACK);
			OLED_Text2x_128128RGB(20, 70, values[0]+16, GREEN, BLACK);
			OLED_Text2x_128128RGB(30, 70, values[1]+16, GREEN, BLACK);
			OLED_Text2x_128128RGB(40, 70, values[2]+16, GREEN, BLACK);
			OLED_Text2x_128128RGB(50, 70, 14, GREEN, BLACK);
			OLED_Text2x_128128RGB(60, 70, values[3]+16, GREEN, BLACK);
			OLED_Text2x_128128RGB(70, 70, values[4]+16, GREEN, BLACK);
			OLED_Text2x_128128RGB(80, 70, 12, GREEN, BLACK);
			OLED_Text2x_128128RGB(90, 70, Serial_Packet.data_check_ONE+16, GREEN, BLACK);
			OLED_Text2x_128128RGB(100, 70, 12, GREEN, BLACK);
			OLED_Text2x_128128RGB(110, 70, Serial_Packet.data_check_TWO+16, GREEN, BLACK);
					
			
			OLED_Text2x_128128RGB(0, 50, 37, GREEN, BLACK); 
			OLED_Text2x_128128RGB(10, 50, 26, GREEN, BLACK);
			
			if(sign_check == true)
			OLED_Text2x_128128RGB(20, 50, 13, GREEN, BLACK); //values[0]+16
			
			else
			OLED_Text2x_128128RGB(20, 50, 11, GREEN, BLACK);	
			
			OLED_Text2x_128128RGB(30, 50, values[5]+16, GREEN, BLACK);
			OLED_Text2x_128128RGB(40, 50, values[6]+16, GREEN, BLACK);
			OLED_Text2x_128128RGB(50, 50, 14, GREEN, BLACK);
			OLED_Text2x_128128RGB(60, 50, values[7]+16, GREEN, BLACK);
			OLED_Text2x_128128RGB(70, 50, values[8]+16, GREEN, BLACK);
			OLED_Text2x_128128RGB(80, 50, 12, GREEN, BLACK);
			OLED_Text2x_128128RGB(90, 50, Serial_Packet.data_check_THREE+16, GREEN, BLACK);
			OLED_Text2x_128128RGB(100, 50, 12, GREEN, BLACK);
			OLED_Text2x_128128RGB(110, 50, Serial_Packet.data_check_FOUR+16, GREEN, BLACK);
			
//			OLED_Text2x_128128RGB(20, 50, values[5]+16, GREEN, BLACK);
//			OLED_Text2x_128128RGB(30, 50, values[6]+16, GREEN, BLACK);
//			OLED_Text2x_128128RGB(40, 50, 14, GREEN, BLACK);
//			OLED_Text2x_128128RGB(50, 50, values[7]+16, GREEN, BLACK);
//			OLED_Text2x_128128RGB(60, 50, values[8]+16, GREEN, BLACK);
//			OLED_Text2x_128128RGB(70, 50, 12, GREEN, BLACK);
//			OLED_Text2x_128128RGB(80, 50, Serial_Packet.data_check_THREE+16, GREEN, BLACK);	
//			OLED_Text2x_128128RGB(90, 50, 12, GREEN, BLACK);
//			OLED_Text2x_128128RGB(100, 50, Serial_Packet.data_check_FOUR+16, GREEN, BLACK);
			
			//P values here---->>>>>>>>>>>>

			OLED_Text2x_128128RGB(0, 30, 48, GREEN, BLACK); 
			OLED_Text2x_128128RGB(10, 30, 26, GREEN, BLACK);
			
			if(sign_check1 == true)
			OLED_Text2x_128128RGB(20, 30, 13, GREEN, BLACK); //values[0]+16
			
			else
			OLED_Text2x_128128RGB(20, 30, 11, GREEN, BLACK);	
			
			OLED_Text2x_128128RGB(30, 30, values[9]+16, GREEN, BLACK);
			OLED_Text2x_128128RGB(40, 30, values[10]+16, GREEN, BLACK);
			OLED_Text2x_128128RGB(50, 30, 14, GREEN, BLACK);
			OLED_Text2x_128128RGB(60, 30, values[11]+16, GREEN, BLACK);
			OLED_Text2x_128128RGB(70, 30, values[12]+16, GREEN, BLACK);
			OLED_Text2x_128128RGB(80, 30, 12, GREEN, BLACK);
			OLED_Text2x_128128RGB(90, 30, Serial_Packet.data_check_FIVE+16, GREEN, BLACK);
			OLED_Text2x_128128RGB(100, 30, 12, GREEN, BLACK);
			OLED_Text2x_128128RGB(110, 30, Serial_Packet.data_check_SIX+16, GREEN, BLACK);

//			OLED_Text2x_128128RGB(0, 30, 48, GREEN, BLACK); 
//			OLED_Text2x_128128RGB(10, 30, 26, GREEN, BLACK);
//			OLED_Text2x_128128RGB(20, 30, values[9]+16, GREEN, BLACK);
//			OLED_Text2x_128128RGB(30, 30, values[10]+16, GREEN, BLACK);
//			OLED_Text2x_128128RGB(40, 30, 14, GREEN, BLACK);
//			OLED_Text2x_128128RGB(50, 30, values[11]+16, GREEN, BLACK);
//			OLED_Text2x_128128RGB(60, 30, values[12]+16, GREEN, BLACK);
//			OLED_Text2x_128128RGB(70, 30, 12, GREEN, BLACK);
//			OLED_Text2x_128128RGB(80, 30, Serial_Packet.data_check_FIVE+16, GREEN, BLACK);
//			OLED_Text2x_128128RGB(90, 30, 12, GREEN, BLACK);
//			OLED_Text2x_128128RGB(100, 30, Serial_Packet.data_check_SIX+16, GREEN, BLACK);


			//B values here---->>>>>>>>>>>>

			OLED_Text2x_128128RGB(0, 10, 34, GREEN, BLACK); 
			OLED_Text2x_128128RGB(10, 10, 26, GREEN, BLACK);
			OLED_Text2x_128128RGB(20, 10, values[13]+16, GREEN, BLACK);
			OLED_Text2x_128128RGB(30, 10, values[14]+16, GREEN, BLACK);
			OLED_Text2x_128128RGB(40, 10, 14, GREEN, BLACK);
			OLED_Text2x_128128RGB(50, 10, values[15]+16, GREEN, BLACK);
			OLED_Text2x_128128RGB(60, 10, values[16]+16, GREEN, BLACK);
			OLED_Text2x_128128RGB(70, 10, 12, GREEN, BLACK);
			OLED_Text2x_128128RGB(80, 10, Serial_Packet.data_check_EIGH+16, GREEN, BLACK);
//			OLED_Text2x_128128RGB(90, 10, 12, GREEN, BLACK);
//			OLED_Text2x_128128RGB(100, 10, Serial_Packet.data_check_EIGH+16, GREEN, BLACK);

		//	OLED_Text2x_128128RGB(0, 10, 34, GREEN, BLACK); 
		//	OLED_Text2x_128128RGB(10, 10, 26, GREEN, BLACK);
		//	OLED_Text2x_128128RGB(20, 10, Serial_Packet.data_check_SEVEN, GREEN, BLACK);
		//	OLED_Text2x_128128RGB(20, 10, Serial_Packet.data_check_SEVEN+16, GREEN, BLACK);
		//	OLED_Text2x_128128RGB(30, 10, 12, GREEN, BLACK);
		//	OLED_Text2x_128128RGB(40, 10, Serial_Packet.data_check_EIGH+16, GREEN, BLACK);
			
			KeyPad_Cyclic();
			//UARTprintf("App_Tick\r\n");
			
			while(UART1_ReadCharAvailable())
			{	
				ch = UART1_ReadChar();
				UARTprintf("%c", ch);
				if(ch == '$')
				{	
					data_check = 1;
				}
				if(data_check)
				{
					commands[indx++] = ch; 
				}	
				if(ch == 0x0A)
				{
					if(!strncmp("$A:",(const char *)commands, 3))
					{	
						Command_Parser((const char *)commands, indx);
						indx = 0;
						data_check = 0;
					}						
				}
			}
		}
}
