/******************************************************************/
/* Author	: Mahmoud Rajab										  */
/* Date		: 27 Nov 2021										  */
/* Version	: V01												  */
/******************************************************************/


#ifndef 	RCC_INTERFACE_H
#define 	RCC_INTERFACE_H



#define 	RCC_AHB		0
#define 	RCC_APB1	1
#define 	RCC_APB2	2

#define 	RCC_HSE		0
#define 	RCC_HSE_2	1
#define 	RCC_HSI_2	2



void RCC_VidInit(void);
void RCC_VidEnableClock(u8 Copy_U8BusID , u8 Copy_U8PeripheralID);
void RCC_VidDisableClock(u8 Copy_U8BusID , u8 Copy_U8PeripheralID);


#endif
