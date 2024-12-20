#ifndef __MAIN_H
#define __MAIN_H

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "inc/hw_hibernate.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/hibernate.h"
#include "inc/hw_ints.h"
#include "driverlib/debug.h"
#include "driverlib/uart.h"
#include "driverlib/interrupt.h"
#include "driverlib/rom.h"
#include "utils/eeprom_pb.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "utils/locator.h"
#include "driverlib/ssi.h"
#include "inc/hw_ints.h"
//#include "utils/lwiplib.h"
//#include "lwip/sys.h"
#include "utils/ustdlib.h"
//#include "config.h"
//#include "httpserver_raw/httpd.h"
#include "utils/ringbuf.h"
#include "inc/hw_uart.h"
//#include "telnet.h"
#include "serial.h"
//#include "cmdline.h"
#include "utils/swupdate.h"
#include "driverlib/timer.h"
//#include "lwip_task.h"
//#include "priorities.h"
//#include "serial_task.h"

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
//#include "uartstdio.h"
#include "inc/hw_uart.h"


#include "inc/hw_ints.h"
#include "inc/hw_gpio.h"

#include "driverlib/hibernate.h"
#include "inc/hw_hibernate.h"
#include "driverlib/usb.h"
#include "inc/hw_memmap.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "driverlib/rom_map.h"
#include "driverlib/adc.h"
//#include "eeprom_app.h"

typedef union
{
	float fval;
	unsigned int ival;
}data_ftoi;

typedef struct
{
	data_ftoi val_ONE;
	uint8_t data_check_ONE;
	uint8_t data_check_TWO;
	data_ftoi val_TWO;
	uint8_t data_check_THREE;
	uint8_t data_check_FOUR;
	data_ftoi val_THREE;
	uint8_t data_check_FIVE;
	uint8_t data_check_SIX;
	data_ftoi val_SEVEN;
	//uint8_t data_check_SEVEN;
	uint8_t data_check_EIGH;
char sign;
	char sign1;
}Serial_pack_struc;

extern void NHD15128128G_SPI_Init(void);
extern void UART1_Init(void);
extern void NHD15128128G_Reset(void);
extern void OLED_Init_128128RGB(void); 
extern void Keypad_Init(void);
extern void OLED_FillScreen_128128RGB(unsigned long color); 
extern void OLED_Text2x_128128RGB(unsigned char x_pos, unsigned char y_pos, unsigned char letter, unsigned long textColor, unsigned long backgroundColor);			
extern void OLED_Text_128128RGB(unsigned char x_pos, unsigned char y_pos, unsigned char letter, unsigned long textColor, unsigned long backgroundColor);
extern void KeyPad_Cyclic(void);
extern int UART1_ReadCharAvailable(void);
extern int UART1_ReadChar(void);
extern void UART1_PutString(char *buf);
void NHD15128128G_TickHandler(void);

#endif
