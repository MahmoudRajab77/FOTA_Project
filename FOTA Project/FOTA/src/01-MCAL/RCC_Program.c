/******************************************************************/
/* Author	: Mahmoud Rajab										  */
/* Date		: 27 Nov 2021										  */
/* Version	: V01												  */
/******************************************************************/




#include "STD_TYPES.h"
#include "BIT_MATH.h"


#include "RCC_Interface.h"
#include "RCC_Private.h"
#include "RCC_Config.h"




void RCC_VidInit(void){
	/*	Select System Clock	*/
	u16 TimeOut_Counter 	= 0 ;
	#if 	RCC_CLOCK_TYPE == RCC_HSE_CRYSTAL
		RCC->CR 		= 0x00010000 ;//0x00010080	//Configuration From DataSheet
		RCC->CFGR		= 0x00000001 ;
		/*Polling With Time Out*/
		u8 m = !(RCC->CR & (1<<17));
		while( m && TimeOut_Counter <20000){	// While HSE Is Not Ready
			TimeOut_Counter++ ;
			m = !(RCC->CR & (1<<17));
		}

	#elif 	RCC_CLOCK_TYPE == RCC_HSE_RC
		/*???????????!!!!!!!!!!!*/
	#elif 	RCC_CLOCK_TYPE == RCC_HSI
		RCC->CR		= 0x00000081;	//Configuration From D.S Enable HSI From Bit_0
		RCC->CFGR	= 0x00000000 ;
		/*	Polling With Time Out Counter	*/
		while( !(RCC->CR & (1<<1)) && TimeOut_Counter <10000){	// While HSI Is Not Ready
			TimeOut_Counter++ ;
		}
	#elif 	RCC_CLOCK_TYPE == RCC_PLL
		#if		RCC_PLL_SRC == RCC_HSE			//Must Configured While PLL Disabled
			RCC->CFGR	= 0x00030002 ;			//
			RCC->CR 	= 0x01010080 ;			//Configuration From D.S Enable HSE From Bit_16 And PLL From Bit_24
		#elif		RCC_PLL_SRC == RCC_HSE_2	//Must Configured While PLL Disabled
			RCC->CFGR	= 0x00010002 ;
			RCC->CR 	= 0x01010080 ;			//Configuration From D.S Enable HSE From Bit_16 And PLL From Bit_24
		#elif		RCC_PLL_SRC == RCC_HSI_2	//Must Configured While PLL Disabled
			RCC->CFGR	= 0x00000002 ;
			RCC->CR		= 0x00000081;	//Configuration From D.S Enable HSI From Bit_0 And PLL From Bit_24
		#else	#error "Wrong Choice Of RCC_PLL Source Clock Type"
		#endif
		while( !(RCC->CR & (1<<25)) && TimeOut_Counter <10000){	// While PLL Is Not Ready--> Bit_25 For All PLL_Sources
			TimeOut_Counter++ ;
		}

	#else	#error "Wrong Choice Of RCC Clock Type"
	#endif

}
void RCC_VidEnableClock(u8 Copy_U8BusID , u8 Copy_U8PeripheralID){
	/*	Enable RCC For Peripheral = Enable Peripheral Clock	*/
	/*	Range Check						*/
	if( (32 > Copy_U8BusID) && (32 > Copy_U8PeripheralID) ){
		switch(Copy_U8BusID){
			case RCC_AHB :
				SET_BIT(RCC->AHBENR , Copy_U8PeripheralID);
				break;
			case RCC_APB1 :
				SET_BIT(RCC->APB1ENR , Copy_U8PeripheralID);
				break;
			case RCC_APB2 :
				SET_BIT(RCC->APB2ENR , Copy_U8PeripheralID);
				break;
		}
	}
	else{
		/* Return ERROR Status */
	}
}
void RCC_VidDisableClock(u8 Copy_U8BusID , u8 Copy_U8PeripheralID){
	/*	Disable RCC For Peripheral = Disable Peripheral Clock	*/
	/*	Range Check						*/
	if( (32 > Copy_U8BusID) && (32 > Copy_U8PeripheralID) ){
		switch(Copy_U8BusID){
			case RCC_AHB :
				CLR_BIT(RCC->AHBENR , Copy_U8PeripheralID);
				break;
			case RCC_APB1 :
				CLR_BIT(RCC->APB1ENR , Copy_U8PeripheralID);
				break;
			case RCC_APB2 :
				CLR_BIT(RCC->APB2ENR , Copy_U8PeripheralID);
				break;
		}
	}
	else{
		/* Return ERROR Status */
	}

}
