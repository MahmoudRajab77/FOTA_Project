/******************************************************************/
/* Author	: Mahmoud Rajab										  */
/* Date		: 27 Nov 2021										  */
/* Version	: V01												  */
/******************************************************************/

#ifndef DIO_PRIVATE_H
#define DIO_PRIVATE_H



#define DIO_PORTA_BASE_ADD		(0x40010800)
#define DIO_PORTB_BASE_ADD		(0x40010C00)
#define DIO_PORTC_BASE_ADD		(0x40011000)


typedef struct{
	u32 CRL;
	u32 CRH;
	u32 IDR;
	u32 ODR;
	u32 BSRR;
	u32 BRR;
	u32 LCKR;

}DIO_st;

#define GPIO_PORTA		((DIO_st*)(DIO_PORTA_BASE_ADD))
#define GPIO_PORTB		((DIO_st*)(DIO_PORTB_BASE_ADD))
#define GPIO_PORTC		((DIO_st*)(DIO_PORTC_BASE_ADD))





#endif
