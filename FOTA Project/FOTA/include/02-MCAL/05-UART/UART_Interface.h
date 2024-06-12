/******************************************************************/
/* Author	: Mahmoud Rajab										  */
/* Date		: 27 Nov 2021										  */
/* Version	: V01												  */
/******************************************************************/


#ifndef _UART_interface_H
#define _UART_interface_H



void UART_VidInit(void);

void UART_VidTransmit(u8* arr);

u8 UART_U8Receive(void);

void MUART_voidTransmitChar(u8 Copy_u8Char);




#endif //_UART_interface_H
