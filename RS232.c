//*****************************************************************************
//
// uart_echo.c - Example for reading data from and writing data to the UART in
//               an interrupt driven fashion.
//
// Copyright (c) 2012-2013 Texas Instruments Incorporated.  All rights reserved.
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
// This is part of revision 2.0.1.11577 of the EK-TM4C123GXL Firmware Package.
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"

#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif

/* Receive buffer */
#define GSMRXBUFSIZE    (2048 * 2)                          /**< Buffer size for RX */
static volatile int     rxReadIndex  = 0;       /**< Index in buffer to be read */
static volatile int     rxWriteIndex = 0;       /**< Index in buffer to be written to */
static volatile int     rxCount      = 0;       /**< Keeps track of how much data which are stored in the buffer */
static volatile uint8_t rxBuffer[GSMRXBUFSIZE];    /**< Buffer to store data */

//*****************************************************************************
//
// The UART interrupt handler.
//
//*****************************************************************************
void
RS232IntHandler(void)
{
    uint32_t ui32Status;
		
		//UARTprintf("HERE\r\n");
    //
    // Get the interrrupt status.
    //
    ui32Status = ROM_UARTIntStatus(UART1_BASE, true);

    //
    // Clear the asserted interrupts.
    //
    ROM_UARTIntClear(UART1_BASE, ui32Status);

    //
    // Loop while there are characters in the receive FIFO.
    //
    while(ROM_UARTCharsAvail(UART1_BASE))
    {

			/* Store Data */
			rxBuffer[rxWriteIndex] = ROM_UARTCharGetNonBlocking(UART1_BASE);
			rxWriteIndex++;
			rxCount++;
			UARTprintf("%c", rxBuffer);
			if (rxWriteIndex >= GSMRXBUFSIZE)
			{
				rxWriteIndex = 0;
			}
			
			/* Check for overflow - flush buffer */
//			if (rxCount > RXBUFSIZE)
//			{
//				rxWriteIndex = 0;
//				rxCount      = 0;
//				rxReadIndex  = 0;
//			}

    }
}

int UART1_ReadChar(void)
{
  int c = -1;

	//INT_Disable();
  if (rxCount > 0)
  {
    c = rxBuffer[rxReadIndex];
    rxReadIndex++;
    if (rxReadIndex >= GSMRXBUFSIZE)
    {
      rxReadIndex = 0;
    }
    rxCount--;
  }
  //INT_Enable();

  return c;
}

int UART1_ReadCharAvailable(void)
{
		//UARTprintf("rxCount %d\r\n",rxCount);
		return rxCount;
}


int UART1_WriteChar(char ch)
{

	ROM_UARTCharPutNonBlocking(UART1_BASE, ch);
				while(((*((volatile unsigned long *)0x4000D018))& 0x00000008) == 0x08)
				{
					//UARTprintf("\nUARTFR = 0x%x", (*((volatile unsigned long *)0x4000D018)));
				}	
	
  return ch;
}


void UART1_Flush(void)
{
	rxReadIndex  = 0;
	rxWriteIndex = 0;
	rxCount      = 0;
	memset(rxBuffer, 0, sizeof(rxBuffer));
}

uint8_t *UART1_GetBufferPointer(void)
{
		return rxBuffer;
}

void UART1_PutString(char *buf)
{
	while(*buf != '\0')
	{
		ROM_UARTCharPutNonBlocking(UART1_BASE, *buf++);
				while(((*((volatile unsigned long *)0x4000D018))& 0x00000008) == 0x08)
				{
					//UARTprintf("\nUARTFR = 0x%x", (*((volatile unsigned long *)0x4000D018)));
				}
	}
	
}

void UART1_PutStringlen(const uint8_t *pui8Buffer, uint32_t ui32Count)
{
    //
    // Loop while there are more characters to send.
    //
    while(ui32Count--)
    {
        //
        // Write the next character to the UART.
        //
        ROM_UARTCharPutNonBlocking(UART1_BASE, *pui8Buffer++);
				while(((*((volatile unsigned long *)0x4000D018))& 0x00000008) == 0x08)
				{
					//UARTprintf("\nUARTFR = 0x%x", (*((volatile unsigned long *)0x4000D018)));
				}			
    }
}

int UART1_Init(void)
{
    //
    // Enable the peripherals used by this example.
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
		
    //
    // Enable processor interrupts.
    //
    ROM_IntMasterEnable();

    //
    // Set GPIO C4 and C5 as UART pins.
    //
    GPIOPinConfigure(GPIO_PC4_U1RX);
    GPIOPinConfigure(GPIO_PC5_U1TX);
    ROM_GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5);

    //
    // Configure the UART for 115,200, 8-N-1 operation.
    //
    ROM_UARTConfigSetExpClk(UART1_BASE, 16000000, 115200,
                            (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                             UART_CONFIG_PAR_NONE));
														 
    //
    // Enable the UART interrupt.
    //
    ROM_IntEnable(INT_UART1);
    ROM_UARTIntEnable(UART1_BASE, UART_INT_RX | UART_INT_RT);	
		UARTprintf("UART1 Is Enable\r\n");
		
		return 0;
}


