/******************************************************************/
/* Author	: Mahmoud Rajab										  */
/* Date		: 27 Nov 2021										  */
/* Version	: V01												  */
/******************************************************************/





#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_Interface.h"
#include "DIO_interface.h"
#include "STK_Interface.h"
#include "UART_Interface.h"
#include "FPEC_Interface.h"
#include "ESP2866_Interface.h"
#include "BL_Config.h"
#include "BL_Interface.h"
#include "PowerControl_Interface.h"
#include <string.h>





volatile 	u8 		Global_U8ArrRecResponse_Buffer[PAGE_SIZE] ;/*Size Testing*/

volatile 	u8  	u8RecBuffer[RecBufferSize]     ;

volatile 	u8  	u8RecCounter     = 0;

volatile 	u8 		U8PageNo   =  0;	/*Page No. To Send --> PHP*/

volatile 	u8 		U8LineNo=0;

volatile	u16		APP_VALIDATIONWORD = 0xF0F1;








void main(void)
{

	Array_ToBe_Zeroes(Global_U8ArrRecResponse_Buffer , PAGE_SIZE);/*Array = 0*/
	Array_ToBe_Zeroes(u8RecBuffer , RecBufferSize);/*Array = 0*/


	/*	RCC Run On 8MHz	*/
	RCC_VidInit();
	/*	Enable RCC Of UART
	 * 	Bit No. 14 */
	RCC_VidEnableClock(RCC_APB2 , 14);
	/*	Enable RCC Of GPIO
	 * 	Bit No. 2 In APB2 peripheral clock enable register (RCC_APB2ENR)
	 * 	From Data sheet Section 7.3.7*/
	RCC_VidEnableClock(RCC_APB2 , 2);

	RCC_VidEnableClock(RCC_AHB,4);   /* FPEC   */


	/*	Configure TX Pin As Output PP On 50 MHz
	 * 	A9 = TX
	 * 	*/
	DIO_VidSetPinDirection(DIO_PORTA , DIO_PIN_9 , DIO_OUTPUT_SPEED_50MHZ_AF_PP);
	/*	Configure RX Pin As Input Floating
	 * 	A10 = RX
	 * 	*/
	DIO_VidSetPinDirection(DIO_PORTA , DIO_PIN_10 , DIO_INPUT_FLOATING);



	/*	Initiate UART_1	*/
	UART_VidInit();



	/*ESP INIT*/
	ESP_VidInit();



	/*Check Internet Connection Status And Connect If Not Connected*/

	if( !ESP_U8IsConnect() ){
		/*	Connect To Network --> Happens Just Once In Whole Program	*/
		ESP_VidConnectNetwork((u8*)WIFISSID,(u8*)WIFIPASSWORD);
	}

	General_VidServerMsg((u8*)"Init%20Done",11);


	MSTK_voidInit();		/*	STK --> To Be Reviewed*/


	/*STK Start!!*/


	/* Check Status File For Erasing Or Jumping To Current App
	 * NewApptoBurn() Return 1 If There Is A New Application To Burn, 0 If /not*/

	if( '1' == NewApptoBurn() ){/*New App. Exist*/
		FPEC_voidEraseAppArea();
		General_VidServerMsg((u8*)"Flash%20Erased%20Done",21);
		/*While App Flash Space Erased Including APP_VALIDATIONADD*/
	}
	else{
//		FPEC_voidEraseAppArea();
		if( /*(*(u32*)(APP_RESETVECTORADD)) != 0xFFFFFFFF*/ *(u16*)APP_VALIDATIONADD == APP_VALIDATIONWORD){
			General_VidServerMsg((u8*)"App%20Found",11);
//			General_VidServerMsg((u8*)"Jump%20To%20App",21);/*MSG*/
			func();	/*Jump To Current App.*//*Check If There is App Or NOT
		 	 	 	 	 	 	 	 	   --> Check On Stack Pointer Value	*/
		}
		else{
			/*	Turn OFF & Send Message To Website	*///++
			/*GET-->pkjnb*///++         /*WDT-->*/
			General_VidServerMsg((u8*)"App%20Not%20Found",17);
			General_VidServerMsg((u8*)"Enter%20Sleep%20Mode",20);
			PWC_StopModeEnter();	/*Stop Mode*/
			while(1);
		}
	}

	Array_ToBe_Zeroes(Global_U8ArrRecResponse_Buffer , PAGE_SIZE);/*Array = 0*/
	Request_Page(U8PageNo);
	General_VidServerMsg((u8*)"Page%20Processing",17);
	U8PageNo++;

	while( 1 )
	{

		Array_ToBe_Zeroes(u8RecBuffer , RecBufferSize);
		Copy_Line_to_Buffer(U8LineNo);
		if( !U8EndOfPageValidation() ){/**EOP, */
			/*	Return 1 If EOF Reached	*/
			if( U8EndOfFileValidation() ){
				General_VidServerMsg((u8*)"App%20Burning%20Done!!",22);
				break;
			}
			/*EDIT IT WITH ERROR HANDLING OR MESSAGE*/
			if( (SumOfArr(u8RecBuffer , RecBufferSize)) && Record_CheckSum() ){/*	If CS ERROR Detected Record_CheckSum() Return 1	*/
				General_VidServerMsg((u8*)"Data%20ERROR%20Detected!!",25);
				PWC_StopModeEnter();	/*Stop Mode*/
				while(1);
				break;
			}

			ParseData(u8RecBuffer);
			U8LineNo++;
		}
		else{

			Array_ToBe_Zeroes(Global_U8ArrRecResponse_Buffer , PAGE_SIZE);
			Array_ToBe_Zeroes(u8RecBuffer , RecBufferSize);

			Request_Page(U8PageNo);
			U8PageNo++;
			U8LineNo=0;
		}
	}
	General_VidServerMsg((u8*)"Running%20Your%20App",20);
	FPEC_voidFlashWrite( (u32*)APP_VALIDATIONADD , &APP_VALIDATIONWORD , 1 );	/*	Indicates There Is A Valid Burned Application	*/

	func();	/*	Jump To Application	*/
}



/*************************************************************************************************************************/

Function_t addr_to_call = NULL;

void func(void)	/*	Jump to Application	If No Data Received On UART After 15 Sec	*/
{
#define SCB_VTOR   *((volatile u32*)0xE000ED08)

	SCB_VTOR = APP_STARTADDRESS;

	addr_to_call = *(Function_t*)(APP_RESETVECTORADD);	/*First Address In Flash --> First 4Byte Is Reset Address Which Initialize Stack Pointer By Startup Code	*/
	addr_to_call();
}


/****************************************************************************************************************************/


/*	Integrated With Decryption	*/
void Copy_Line_to_Buffer( u8 U8LineNo ){//10
	u8 Local_U8Counter=0 ;
	u16 Local_U16Iterator=0;/*Loop On All Array Characters */

	/*	Go To The Desired Line	*/
	while(  Local_U8Counter < U8LineNo ){
		Local_U16Iterator++;
		while( '\r' != Global_U8ArrRecResponse_Buffer[Local_U16Iterator] ){
			Local_U16Iterator++;
		}

		Local_U8Counter++;/*Increment After Each Line*/
	}
	if( 0 != Local_U16Iterator ){/**/
		Local_U16Iterator+=1;
	}


	/**/
	Local_U8Counter=0;/*For The Buffer*/
//	u8RecBuffer[Local_U8Counter] =  Global_U8ArrRecResponse_Buffer[Local_U16Iterator] ;/*Decryption*/
//	Local_U8Counter=1;
//	Local_U16Iterator++;
	/*	Now Copy The Desired Line	*/
	while( '\r' != Global_U8ArrRecResponse_Buffer[Local_U16Iterator] ){/*Last Line In Page*/
		/*Copy Line From 15000char Array Into Buffer*/

		if(Global_U8ArrRecResponse_Buffer[Local_U16Iterator] == 'P' ){
			u8RecBuffer[Local_U8Counter] = Global_U8ArrRecResponse_Buffer[Local_U16Iterator];
			break;
		}/*DLETE IT*/
		else if(Global_U8ArrRecResponse_Buffer[Local_U16Iterator] == 'e'){/*end of file*/
			u8RecBuffer[Local_U8Counter] = Global_U8ArrRecResponse_Buffer[Local_U16Iterator];
			MSTK_voidSetIntervalSingle(30,func);
			break;
		}/*DLETE IT*/
		else{
			if(Global_U8ArrRecResponse_Buffer[Local_U16Iterator] == ':' || Global_U8ArrRecResponse_Buffer[Local_U16Iterator] == '\r' ){
				u8RecBuffer[Local_U8Counter] = Global_U8ArrRecResponse_Buffer[Local_U16Iterator];
			}
			else{
				u8RecBuffer[Local_U8Counter] = HexToAsci( ASCIIToHex( Global_U8ArrRecResponse_Buffer[Local_U16Iterator] ) ^ 9 );/*Decryption*/
			}
			Local_U8Counter++;
			Local_U16Iterator++;
		}

	}
	u8RecBuffer[Local_U8Counter] = Global_U8ArrRecResponse_Buffer[Local_U16Iterator];/* To Save the '\r' The End Of the Line	*/

}


/*	Validation Test Approved	*/
void Request_Page(u8 Copy_U8PageNumber){
	/*******************************************************************************/

	u8 Local_U8ArrAsciiPageNo[5]={0};
	u8 Local_U8ArrAsciiCharNo[5]={0};
	u8 Local_U8ResponceValidationArr[50]={0};
	u8 Local_U8Counter=0;

	itoa(Copy_U8PageNumber,Local_U8ArrAsciiPageNo,10);/*	10 --> Base of No.(Decimal)-->PHP-URL*/
	ESP_VidConnectToServer((u8*)CONNECTION_TYPE,(u8*)SERVER_IP,(u8*)PORT_IP);

	/*	Send Page Request	*/
	/*	Deal With No. Of Characters */
    Local_U8Counter = SENDPAGENO_PATH_LENGTH;/*Init With 64 Char.*/
    if(Copy_U8PageNumber == 0){
    	Local_U8Counter++;
    }
    else{
    	while (Copy_U8PageNumber!=0)
        {
            Local_U8Counter++;
            Copy_U8PageNumber/=10;
        }
    }

	itoa(Local_U8Counter,Local_U8ArrAsciiCharNo,10);
	UART_VidTransmit((u8*)"AT+CIPSEND=");
	UART_VidTransmit(Local_U8ArrAsciiCharNo);/*	Send Char. No.	*/
	UART_VidTransmit((u8*)"\r\n");
//	General_VidDummyDelay(1);
//	MSTK_voidSetBusyWait(2000);
	Local_U8Counter=1;
	while(Local_U8ResponceValidationArr[Local_U8Counter-1] != 'K'){
		do
		{
			Local_U8ResponceValidationArr[Local_U8Counter]=(u8)UART_U8Receive();
		}while(Local_U8ResponceValidationArr[Local_U8Counter] ==0);
		if(Local_U8Counter == 50){
			break;
		}
		else{
			Local_U8Counter++;
		}
	}

	UART_VidTransmit((u8*)SENDPAGENO_PATH);
	UART_VidTransmit(Local_U8ArrAsciiPageNo);/*	Send Page No.	*/
	UART_VidTransmit((u8*)"\r\n");
//	General_VidDummyDelay(100);
//	MSTK_voidSetBusyWait(2000);
	Local_U8Counter=1;
	while(Local_U8ResponceValidationArr[Local_U8Counter-1] != 'L'){
		do
		{
			Local_U8ResponceValidationArr[Local_U8Counter]=(u8)UART_U8Receive();
		}while(Local_U8ResponceValidationArr[Local_U8Counter] ==0);
		if(Local_U8Counter == 50){
			break;
		}
		else{
			Local_U8Counter++;
		}
	}



	/*	Receive Page Data	*/
	ESP_VidConnectToServer((u8*)CONNECTION_TYPE,(u8*)SERVER_IP,(u8*)PORT_IP);
	ESP_VidGetFile((u8*)PAGE_PATH_LENGTH , (u8*)PAGE_PATHE);//RequestedPage.txt
	/*********************************************************************************/
}


/*	Validation Test Approved	*/
void Array_ToBe_Zeroes(volatile u8* Ptr_U8Arr , u16 Copy_U16ArrSize){
	while( Copy_U16ArrSize > 0 ){
		Ptr_U8Arr[Copy_U16ArrSize] = 0;
		Copy_U16ArrSize--;
	}
	Ptr_U8Arr[0] = 0;
}
/*	Return 1 If EOF Reached, 0 If Not	*//*EDIT IT !!!!!*/
u8 U8EndOfFileValidation(void){
	u8 i=0;
	if( u8RecBuffer[0] == 'E' && u8RecBuffer[1] == 'F' ){
		i=1;
	}
	return i;
}
/*	Return 1 If EOP Reached, 0 If Not	*/
u8 U8EndOfPageValidation(void){
	u8 i=0;
	if( u8RecBuffer[0] == 'E' && u8RecBuffer[1] == 'P' ){
		i=1;
	}
	return i;
}


/*	Return 1 In Case Of ERROR OR 0 In Case Of Correct Record	*/
u8 Record_CheckSum(void){

	/**/
	volatile u16 u16Checksum   = 0x00;
	volatile u16 u16RecChecksum= 0x00;
	volatile u8  u8i		   =    1;
	volatile u8  u8FirstChar   = 0x00;
	volatile u8  u8SecondChar  = 0x00;
	/*	Checksum Safety On Every Record If Correct Send Record To Parser	*/
	if( u8RecBuffer[0] != 'E' && u8RecBuffer[1] != 'O' && u8RecBuffer[2] != 'P' ){
		while('\r' != u8RecBuffer[u8i+2]){/*	i+2 To Avoid Summing Of Last 2 Character In Record--> Received CS	*/
			u8FirstChar = AsciToHex(u8RecBuffer[u8i]);
			u8SecondChar= AsciToHex(u8RecBuffer[u8i+1]);
			u16Checksum += ( (u8FirstChar<<4) | (u8SecondChar) );
			u8i+=2;
		}
		u16Checksum = (u8)(0x01 + ((~u16Checksum)&0xFF));

		u8FirstChar = AsciToHex(u8RecBuffer[u8i]);
		u8SecondChar= AsciToHex(u8RecBuffer[u8i+1]);
		u16RecChecksum = (( (u8FirstChar << 4) | (u8SecondChar) ) & 0xFF);

		u8i = 0;	/*	Use It In ERROR Checking	*/


		if( u16Checksum != u16RecChecksum){/*	In Case Of ERROR Jump To Current Application	*/
	/*		func();	/*	Jump To Previous If Exist Application.
			 	 	 	Note: Add Feature To Check If Any Application
			 	 	 		  Existent Already Before Jumping.	*/
			/*ADD Function In Case Of ERROR --> Blink LED For Example
			 * Or Write An ERROR Message to Server */
			u8i=1;
		}
	}
//	u8i = 0;/*??!!*/

	return u8i;
}


u32 SumOfArr(u8* Arr , u16 Size){
	u32 Sum=0;
	while(Size>0){
		Sum += Arr[Size];
		Size--;
	}
	Sum += Arr[0];
	return Sum ;
}


/*	Check If There Is New App To Burn-->Return 1 If There, 0 If Not
 * 	--> Implementation Depends On PHP Code	*/
u8 NewApptoBurn(void){

	u8 Returned_Data=0;
	u8 Local_U8ArrAsciiCharNo[5]={0};
	u8 Local_RecResponse[500]={0};
	u8 Local_U8ResponceValidationArr[50]={0};
	u8 Local_U8Counter=0;

	ESP_VidConnectToServer((u8*)CONNECTION_TYPE,(u8*)SERVER_IP,(u8*)PORT_IP);
	/*	Send Page Request	*/
	/*	Deal With No. Of Characters */
    Local_U8Counter = STATUFILE_PATH_LENGTH;/*Init With 64 Char.*/

	itoa(Local_U8Counter,Local_U8ArrAsciiCharNo,10);


	UART_VidTransmit((u8*)"AT+CIPSEND=");
	UART_VidTransmit(Local_U8ArrAsciiCharNo);/*	Send Char. No.	*/
	UART_VidTransmit((u8*)"\r\n");

//	MSTK_voidSetBusyWait(1000);
	Local_U8Counter=1;
	while(Local_U8ResponceValidationArr[Local_U8Counter-1] != 'K'){
		do
		{
			Local_U8ResponceValidationArr[Local_U8Counter]=(u8)UART_U8Receive();
		}while(Local_U8ResponceValidationArr[Local_U8Counter] ==0);
		if(Local_U8Counter == 50){
			break;
		}
		else{
			Local_U8Counter++;
		}
	}

	UART_VidTransmit((u8*)STATUFILE_PATH);
	UART_VidTransmit((u8*)"\r\n");
	MSTK_voidSetBusyWait(1000);


	Local_U8Counter=1;

	while(Local_RecResponse[Local_U8Counter-1] != 'L'){
		do
		{
			Local_RecResponse[Local_U8Counter]=(u8)UART_U8Receive();
		}while(Local_RecResponse[Local_U8Counter] == 0);

		/*	Data Validation */
		if( ':' == Local_RecResponse[Local_U8Counter-1]){
			Returned_Data = Local_RecResponse[(Local_U8Counter)];
			break;
		}

		if(Local_U8Counter == 500){
			break;
		}
		else{

			Local_U8Counter++;
		}
	}

	/*	Data Validation */
	return Returned_Data;
}


void General_VidServerMsg(u8* Copy_U8PtrMsg , u8 Copy_U8Length){
	Copy_U8Length += MESSAGE_PATH_LENGTH;

	u8 Local_U8ArrAsciiLengthNo[5]={0};
	itoa(Copy_U8Length,Local_U8ArrAsciiLengthNo,10);

	u8 Local_U8ResponceValidationArr[50]={0};
	u8 Local_U8Counter=0;

	ESP_VidConnectToServer((u8*)CONNECTION_TYPE,(u8*)SERVER_IP,(u8*)PORT_IP);

	UART_VidTransmit((u8*)"AT+CIPSEND=");
	UART_VidTransmit(Local_U8ArrAsciiLengthNo);/*	Send Char. No.	*/
	UART_VidTransmit((u8*)"\r\n");
	Local_U8Counter=1;
	while(Local_U8ResponceValidationArr[Local_U8Counter-1] != 'K'){
		do
		{
			Local_U8ResponceValidationArr[Local_U8Counter]=(u8)UART_U8Receive();
		}while(Local_U8ResponceValidationArr[Local_U8Counter] ==0);
		if(Local_U8Counter == 50){
			break;
		}
		else{
			Local_U8Counter++;
		}
	}

	UART_VidTransmit((u8*)MESSAGE_PATH);
	UART_VidTransmit(Copy_U8PtrMsg);/*	Send the Actual Message		*/
	UART_VidTransmit((u8*)"\r\n");

	Local_U8Counter=1;
	while(Local_U8ResponceValidationArr[Local_U8Counter-1] != 'L'){
		do
		{
			Local_U8ResponceValidationArr[Local_U8Counter]=(u8)UART_U8Receive();
		}while(Local_U8ResponceValidationArr[Local_U8Counter] ==0);
		if(Local_U8Counter == 50){
			break;
		}
		else{
			Local_U8Counter++;
		}
	}
}


u8 HexToAsci(u8 Copy_U8Hex){
	u8 Result;
	if ( (Copy_U8Hex >= 0) && (Copy_U8Hex <= 9) )
	{
		Result = Copy_U8Hex + 48;	/*	'0'=48, '1'=49, .....	*/
	}

	else if( (Copy_U8Hex >= 10) && (Copy_U8Hex <= 15) )
	{
		Result = Copy_U8Hex + 55;/*	Convert A=65, B=66, C D E F=70, Into From ASCII To HEX	*/
	}
	else{
		Result = Copy_U8Hex;
	}

	return Result;
}


u8 ASCIIToHex(u8 Copy_U8ASCII){
	u8 Result;
	if ( (Copy_U8ASCII >= 48) && (Copy_U8ASCII <= 57) )
	{
		Result = Copy_U8ASCII - 48;	/*	'0'=48, '1'=49, .....	*/
	}

	else if( (Copy_U8ASCII >= 65) && (Copy_U8ASCII <= 70) )
	{
		Result = Copy_U8ASCII - 55;/*	Convert A=65, B=66, C D E F=70, Into From ASCII To HEX	*/
	}
	else{
		Result = Copy_U8ASCII;
	}

	return Result;
}

