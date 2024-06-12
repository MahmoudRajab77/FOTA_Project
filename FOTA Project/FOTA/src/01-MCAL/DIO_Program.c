/******************************************************************/
/* Author	: Mahmoud Rajab										  */
/* Date		: 27 Nov 2021										  */
/* Version	: V01												  */
/******************************************************************/




#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_Interface.h"
#include "DIO_Private.h"
#include "DIO_Config.h"



void DIO_VidSetPinDirection(u8 Copy_U8PortID , u8 Copy_U8PinID , u8 Copy_U8PinDirection){

	/*	Range Check On Pin And Port	*/
	/*Copy_U8PortID >= DIO_PORTA && No Need --> U8 is Unsigned Char. Which Always Greater Than 0*/
	if(Copy_U8PortID < DIO_PORTC && Copy_U8PinID<16){

		/*Low Pins-->CRL Register*/
		if(Copy_U8PinID < 8){
			switch(Copy_U8PortID){
				case DIO_PORTA:	GPIO_PORTA->CRL &= (~(0xFF<<(Copy_U8PinID*4)));	//Four Bits Of Pin(Config. And Mode) == 0b0000
								GPIO_PORTA->CRL |= ((Copy_U8PinDirection)<<(Copy_U8PinID*4));
								break;
				case DIO_PORTB:	GPIO_PORTB->CRL &= (~(0xFF<<(Copy_U8PinID*4)));	//Four Bits Of Pin(Config. And Mode) == 0b0000
								GPIO_PORTB->CRL |= ((Copy_U8PinDirection)<<(Copy_U8PinID*4));
								break;
				case DIO_PORTC:	GPIO_PORTC->CRL &= (~(0xFF<<(Copy_U8PinID*4)));	//Four Bits Of Pin(Config. And Mode) == 0b0000
								GPIO_PORTC->CRL |= ((Copy_U8PinDirection)<<(Copy_U8PinID*4));
								break;
			}
		}
		/*HIGH Pins-->CRH Register*/
		else if(Copy_U8PinID >=8){
			Copy_U8PinID -=8 ;	//PinID - 8 To Deal With 32 Bits Register
			switch(Copy_U8PortID){

				case DIO_PORTA:	GPIO_PORTA->CRH &= (~(0xFF<<(Copy_U8PinID*4)));	//Four Bits Of Pin(Config. And Mode) == 0b0000
								GPIO_PORTA->CRH |= ((Copy_U8PinDirection)<<(Copy_U8PinID*4));	//Assign The Direction Of Pin Now
								break;
				case DIO_PORTB:	GPIO_PORTB->CRH &= (~(0xFF<<(Copy_U8PinID*4)));	//Four Bits Of Pin(Config. And Mode) == 0b0000
								GPIO_PORTB->CRH |= ((Copy_U8PinDirection)<<(Copy_U8PinID*4));
								break;
				case DIO_PORTC:	GPIO_PORTC->CRH &= (~(0xFF<<(Copy_U8PinID*4)));	//Four Bits Of Pin(Config. And Mode) == 0b0000
								GPIO_PORTC->CRH |= ((Copy_U8PinDirection)<<(Copy_U8PinID*4));
								break;
				}

		}
	}
	else{
		/*Return ERROR */
	}
}


void DIO_VidSetPinValue(u8 Copy_U8PortID , u8 Copy_U8PinID , u8 Copy_U8PinValue){

	/*	Range Check On Pin And Port	*/
	/*Copy_U8PortID >= DIO_PORTA && No Need --> U8 is Unsigned Char. Which Always Greater Than 0*/
	if(Copy_U8PortID <= DIO_PORTC && Copy_U8PinID<16){

		switch(Copy_U8PortID){
				/*Low Pins-->CRL Register*/
				case DIO_PORTA:	GPIO_PORTA->ODR &= (~(1<<(Copy_U8PinID)));
								GPIO_PORTA->ODR |= ((Copy_U8PinValue)<<(Copy_U8PinID));
								break;
				case DIO_PORTB:	GPIO_PORTB->ODR &= (~(1<<(Copy_U8PinID)));
								GPIO_PORTB->ODR |= ((Copy_U8PinValue)<<(Copy_U8PinID));
								break;
				case DIO_PORTC:	GPIO_PORTC->ODR &= (~(1<<(Copy_U8PinID)));
								GPIO_PORTC->ODR |= ((Copy_U8PinValue)<<(Copy_U8PinID));
								break;
		}
	}
	else{
		/*Return ERROR */
	}
}


u8 DIO_U8GetPinValue(u8 Copy_U8PortID , u8 Copy_U8PinID ){
	u8 Local_U8PinValue = 0;
	/*	Range Check On Pin And Port	*/
	/*Copy_U8PortID >= DIO_PORTA && No Need --> U8 is Unsigned Char. Which Always Greater Than 0*/
	if(Copy_U8PortID <= DIO_PORTC && Copy_U8PinID<16){
		switch(Copy_U8PortID){
				/*Low Pins-->CRL Register*/
				case DIO_PORTA:	Local_U8PinValue = GET_BIT(GPIO_PORTA->IDR , Copy_U8PinID);
								break;
				case DIO_PORTB:	Local_U8PinValue = GET_BIT(GPIO_PORTB->IDR , Copy_U8PinID);
								break;
				case DIO_PORTC:	Local_U8PinValue = GET_BIT(GPIO_PORTC->IDR , Copy_U8PinID);
								break;
		}
	}
	else{
		/*Return ERROR */
	}
	return Local_U8PinValue ;

}



void DIO_VidSetPortDirection(u8 Copy_U8PortID , u16 Copy_U8PortDirection){

	/*	Range Check On Pin And Port	*/
	/*Copy_U8PortID >= DIO_PORTA && No Need --> U8 is Unsigned Char. Which Always Greater Than 0*/
	if(Copy_U8PortID <= DIO_PORTC){

			switch(Copy_U8PortID){
				case DIO_PORTA:	GPIO_PORTA->CRL = 0x00000000 ;	//32 Bits Of Pin(Config. And Mode) == 0x00000000
								GPIO_PORTA->CRH = 0x00000000 ;
			    				for(u8 i=0 ; i<32 ; i+=4){
			    					GPIO_PORTA->CRL |= ((u32)Copy_U8PortDirection<<i);
			    					GPIO_PORTA->CRH |= ((u32)Copy_U8PortDirection<<i);
			    				}
								break;
				case DIO_PORTB:	GPIO_PORTB->CRL = 0x00000000 ;	//32 Bits Of Pin(Config. And Mode) == 0x00000000
								GPIO_PORTB->CRH = 0x00000000 ;
								for(u8 i=0 ; i<32 ; i+=4){
									GPIO_PORTB->CRL |= ((u32)Copy_U8PortDirection<<i);
									GPIO_PORTB->CRH |= ((u32)Copy_U8PortDirection<<i);
								}
								break;
				case DIO_PORTC:	GPIO_PORTC->CRL = 0x00000000 ;	//32 Bits Of Pin(Config. And Mode) == 0x00000000
								GPIO_PORTC->CRH = 0x00000000 ;
								for(u8 i=0 ; i<32 ; i+=4){
									GPIO_PORTC->CRL |= ((u32)Copy_U8PortDirection<<i);
									GPIO_PORTC->CRH |= ((u32)Copy_U8PortDirection<<i);
								}
								break;
			}

	}
	else{
		/*Return ERROR */
	}
}

void DIO_VidSetPortValue(u8 Copy_U8PortID , u16 Copy_U8PortValue){
	/*	Range Check On Pin And Port	*/
	/*Copy_U8PortID >= DIO_PORTA && No Need --> U8 is Unsigned Char. Which Always Greater Than 0*/
	if(Copy_U8PortID <= DIO_PORTC){
//		if(Copy_U8PinValue == DIO_LOW){
			switch(Copy_U8PortID){
				case DIO_PORTA:	GPIO_PORTA->ODR &= 0xFFFF0000 ;	//15 Bits Of Pin(Value) == LOW
								GPIO_PORTA->ODR |= Copy_U8PortValue ;
								break;
				case DIO_PORTB:	GPIO_PORTB->ODR &= 0xFFFF0000 ;	//15 Bits Of Pin(Value) == LOW
								GPIO_PORTB->ODR |= Copy_U8PortValue ;
								break;
				case DIO_PORTC:	GPIO_PORTC->ODR &= 0xFFFF0000 ;	//15 Bits Of Pin(Value) == LOW
								GPIO_PORTC->ODR |= Copy_U8PortValue ;
								break;
			}
		//}
		/*else if(Copy_U8PinValue == DIO_HIGH){
			switch(Copy_U8PortID){
				case DIO_PORTA:	GPIO_PORTA->ODR &= 0xFFFF0000 ;
								GPIO_PORTA->ODR |= 0x0000FFFF ;	//15 Bits Of Pin(Value) == HIGH
								break;
				case DIO_PORTB:	GPIO_PORTB->ODR &= 0xFFFF0000 ;
								GPIO_PORTB->ODR |= 0x0000FFFFF ; //15 Bits Of Pin(Value) == HIGH
								break;
				case DIO_PORTC:	GPIO_PORTC->ODR &= 0xFFFF0000 ;
								GPIO_PORTC->ODR |= 0x0000FFFF ;	//15 Bits Of Pin(Value) == HIGH
								break;
			}
		}*/

	}
	else{
		/*Return ERROR */
	}
}

