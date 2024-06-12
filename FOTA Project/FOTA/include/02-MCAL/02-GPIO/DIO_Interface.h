/******************************************************************/
/* Author	: Mahmoud Rajab										  */
/* Date		: 27 Nov 2021										  */
/* Version	: V01												  */
/******************************************************************/


#ifndef 	DIO_INTERFACE_H
#define 	DIO_INTERFACE_H





#define 	DIO_HIGH	1
#define 	DIO_LOW		0


#define 	DIO_PORTA									0
#define 	DIO_PORTB									1
#define 	DIO_PORTC									2

#define	 	DIO_PIN_0									0
#define 	DIO_PIN_1									1
#define 	DIO_PIN_2									2
#define 	DIO_PIN_3									3
#define 	DIO_PIN_4									4
#define 	DIO_PIN_5									5
#define 	DIO_PIN_6									6
#define 	DIO_PIN_7									7
#define 	DIO_PIN_8									8
#define 	DIO_PIN_9									9
#define 	DIO_PIN_10									10
#define 	DIO_PIN_11									11
#define 	DIO_PIN_12									12
#define 	DIO_PIN_13									13
#define 	DIO_PIN_14									14
#define 	DIO_PIN_15									15
#define 	DIO_PIN_16									16



#define 	DIO_INPUT_ANALOG							0b0000
#define 	DIO_INPUT_FLOATING							0b0100
#define 	DIO_INPUT_PULL_UP_DOWN						0b1000


#define 	DIO_OUTPUT_SPEED_10MHZ_PP					0b0001
#define 	DIO_OUTPUT_SPEED_10MHZ_OD					0b0101
#define 	DIO_OUTPUT_SPEED_10MHZ_AF_PP				0b1001
#define 	DIO_OUTPUT_SPEED_10MHZ_AF_OD				0b1101

#define 	DIO_OUTPUT_SPEED_2MHZ_PP					0b0010
#define 	DIO_OUTPUT_SPEED_2MHZ_OD					0b0110
#define 	DIO_OUTPUT_SPEED_2MHZ_AF_PP					0b1010
#define 	DIO_OUTPUT_SPEED_2MHZ_AF_OD					0b1110

#define 	DIO_OUTPUT_SPEED_50MHZ_PP					0b0011
#define 	DIO_OUTPUT_SPEED_50MHZ_OD					0b0111
#define 	DIO_OUTPUT_SPEED_50MHZ_AF_PP				0b1011
#define 	DIO_OUTPUT_SPEED_50MHZ_AF_OD				0b1111




void DIO_VidSetPinDirection(u8 Copy_U8PortID , u8 Copy_U8PinID , u8 Copy_U8PinDirection);

void DIO_VidSetPinValue(u8 Copy_U8PortID , u8 Copy_U8PinID , u8 Copy_U8PinValue);

u8 DIO_U8GetPinValue(u8 Copy_U8PortID , u8 Copy_U8PinID );

void DIO_VidSetPortDirection(u8 Copy_U8PortID , u16 Copy_U8PortDirection);

void DIO_VidSetPortValue(u8 Copy_U8PortID , u16 Copy_U8PortValue);




#endif
