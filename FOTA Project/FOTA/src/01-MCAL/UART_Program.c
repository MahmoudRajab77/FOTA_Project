/******************************************************************/
/* Author	: Mahmoud Rajab										  */
/* Date		: 27 Nov 2021										  */
/* Version	: V01												  */
/******************************************************************/





#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "UART_Interface.h"
#include "UART_Private.h"
#include "UART_Config.h"

#include "STK_Interface.h"




void UART_VidInit(void){

	/*	Clear Status Register To Avoid Any Unexpected Interrupts After Enable UART*/
	UART_1 -> SR = 0x00;


	/* Select Baud Rate	--> BR = 115200
	 * 8000000/(9600*16)=4.340277777
	 * BRR = 4 in Mantissa and 5 in Fraction-->0.34027777*16=5.444=5
	 * SO BRR = 0x45*/
	UART_1 -> BRR = 0x45 ;
	/*
	 * 	1- Enable RX	Bit 2
	 * 	2- Enable TX	Bit 3
	 * 	3- Enable UART	Bit 13
	 * 	All This In Control Register CR1
	 * 	*/
	UART_1 -> CR1 |= (1<<2) | (1<<3) | (1<<13);
//	SET_BIT(UART_1 -> CR1 ,2);
//	SET_BIT(UART_1 -> CR1 ,3);
//	SET_BIT(UART_1 -> CR1 ,13);


}


void UART_VidTransmit(u8* arr){
	//u8 i = 0 ;
	//while( '\0' != arr[i] ){
	//	UART_1 -> DR = arr[i];
		/*	Wait Till Transmission Complete
		 * Check On Transmission Complete Flag In Status Register
		 * 	Bit No. 6 In Status Reg.
		 * 	Access It Using Get Bit --> while((GET_BIT(UART_1 -> SR , 6) == 0)
		 * 	Or Simply Using ...
		 * 	*/
		//while((UART_1 -> SR) & 0x40);
	//	while((GET_BIT((UART_1 -> SR), 6)) == 0);

	//	i++;
	//}
	/***/
//	u16 Local_u16Timeout=0;
//	u8 i = 0;
//	u8 Value=0;
//	while(arr[i] != '\0'){
//		Value = arr[i];
//		UART_1 -> DR = Value;
//		while((GET_BIT((UART_1 -> SR), 6)) == 0)
//		{
//			Local_u16Timeout++;
//			if (Local_u16Timeout == 10000)
//			{
//				break;
//			}
//		}
//		i++;
//	}

	u32 i=0;

	while(arr[i]!='\0')
	{
		if(arr[i] != '\\'){
			UART_1->DR = arr[i];
		}


		while(GET_BIT((UART_1->SR),6)==0);

		i++;
	}

}


void MUART_voidTransmitChar(u8 Copy_u8Char)
{
	UART_1->DR = Copy_u8Char;

	while(GET_BIT((UART_1->SR),6)==0);
}


u8 UART_U8Receive(void){
	/*	Wait Till Receive Complete
	 * 	Bit No. 5 In Status Register
	 * 	*/
//	u32 Local_U16TimeOut = 0 ;
//	u8 Data = 0;
//	/*	Instead OF Infinite Loop Use Time Out	*/
//	while((/*(UART_1 -> SR) & 0x10)*/GET_BIT((UART_1 -> SR), 5)) == 0){
//		/*	Use SysTick To Set Time After End Return To Function
//		 * 	MSTK_VidSetIntervalSignal(2000000);	*/
//		Local_U16TimeOut++;
//		if(Local_U16TimeOut == 1000000){
//			Data = 130;	/*=130 Value Not To Be Receive From  */
//			break ;
//		}
//	}
//	if ( Data == 0){
//		Data = ((u8)(UART_1 -> DR ) /*& 0xFF*/);	/*	This Is Bit Masking Or Register Masking To Make Sure Only 8 Bits Received
//	 	 	 	 	 	 	 	 	 	Or Simply Cast DR Into u8
//	 	 	 	 	 	 	 	 	 	*/
//	}
//	return 	Data;
/*************/
	u8 Local_u8Result = 0;

	if ( (GET_BIT((UART_1 -> SR), 5)) == 1 )/*	Check If There Is Data To Read*/
	{
		Local_u8Result = UART_1 -> DR;
	}

	/*	Return 1 If Data Is Received, 0 If Not	*/
	return (Local_u8Result);
}



