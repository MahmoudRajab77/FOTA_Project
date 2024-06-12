/******************************************************************/
/* Author	: Mahmoud Rajab										  */
/* Date		: 27 Nov 2021										  */
/* Version	: V01												  */
/******************************************************************/





#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "ESP2866_Interface.h"
#include "ESP2866_Private.h"

#include "UART_Interface.h"
#include "STK_Interface.h"


#include <string.h>


#define RecResArrSize	100
#define PAGE_SIZE	1500

#define 	CONNECTION_TYPE			"TCP"
#define 	SERVER_IP				"162.253.155.226"
#define 	PORT_IP					"80"





extern volatile u8 Global_U8ArrRecResponse_Buffer[PAGE_SIZE] ;
void Array_ToBe_Zeroes(volatile u8* Ptr_U8Arr , u16 Copy_U16ArrSize);

u8 GlobalU8ArrRecResponse[RecResArrSize] ;
u8 ArrToSaveStr[70]			  ;






void ESP_VidInit(void){
    /*
        1- ATE0			--> Disable Echo
        2- AT+CWMODE=1  --> Operation Mode = Station
    */

	Array_ToBe_Zeroes(GlobalU8ArrRecResponse , RecResArrSize);
	u8 Local_U8Counter=0;

	Local_U8Counter=1;
	UART_VidTransmit((u8*)"AT\r\n");
	while(GlobalU8ArrRecResponse[Local_U8Counter-1] != 'K'){
		do
		{
			GlobalU8ArrRecResponse[Local_U8Counter]=(u8)UART_U8Receive();
		}while(GlobalU8ArrRecResponse[Local_U8Counter] ==0);
		if(Local_U8Counter == RecResArrSize){
			break;
		}
		else{
			if(GlobalU8ArrRecResponse[Local_U8Counter-1] == 'R' && GlobalU8ArrRecResponse[Local_U8Counter] == 'R'){
				/*Connection Error --> Re send The Command*/
				UART_VidTransmit((u8*)"AT\r\n");
				Local_U8Counter = 1;
				continue;
			}
			Local_U8Counter++;
		}
	}

	Array_ToBe_Zeroes(GlobalU8ArrRecResponse , RecResArrSize);

	Local_U8Counter=1;
//	General_VidDummyDelay(10);///------------------------+++++

	UART_VidTransmit((u8*)"ATE0\r\n");


	while(GlobalU8ArrRecResponse[Local_U8Counter-1] != 'K'){
		do
		{
			GlobalU8ArrRecResponse[Local_U8Counter]=(u8)UART_U8Receive();
		}while(GlobalU8ArrRecResponse[Local_U8Counter] ==0);
		if(Local_U8Counter == RecResArrSize){
			break;
		}
		else{
			if(GlobalU8ArrRecResponse[Local_U8Counter-1] == 'R' && GlobalU8ArrRecResponse[Local_U8Counter] == 'R'){
				/*Connection Error --> Re send The Command*/
				UART_VidTransmit((u8*)"ATE0\r\n");
				Local_U8Counter = 1;
				continue;
			}
			Local_U8Counter++;
		}
	}



	Array_ToBe_Zeroes(GlobalU8ArrRecResponse , RecResArrSize);

	Local_U8Counter=1;
	UART_VidTransmit((u8*)"AT+CWMODE=1\r\n");


	while(GlobalU8ArrRecResponse[Local_U8Counter-1] != 'K'){
		do
		{
			GlobalU8ArrRecResponse[Local_U8Counter]=(u8)UART_U8Receive();
		}while(GlobalU8ArrRecResponse[Local_U8Counter] ==0);
		if(Local_U8Counter == RecResArrSize){
			break;
		}
		else{
			if(GlobalU8ArrRecResponse[Local_U8Counter-1] == 'R' && GlobalU8ArrRecResponse[Local_U8Counter] == 'R'){
				/*Connection Error --> Re send The Command*/
				UART_VidTransmit((u8*)"AT+CWMODE=1\r\n");
				Local_U8Counter = 1;
				continue;
			}
			Local_U8Counter++;
		}
	}

	/*********************Multi Connection With ID == 1************************************/
	/*Array_ToBe_Zeroes(GlobalU8ArrRecResponse , RecResArrSize);

		Local_U8Counter=1;
		UART_VidTransmit("AT+CIPMUX=1\r\n");


		while(GlobalU8ArrRecResponse[Local_U8Counter-1] != 'K' && GlobalU8ArrRecResponse[Local_U8Counter-1] != 'R'){
			do
			{
				GlobalU8ArrRecResponse[Local_U8Counter]=(u8)UART_U8Receive();
			}while(GlobalU8ArrRecResponse[Local_U8Counter] ==0);
			if(Local_U8Counter == RecResArrSize){
				break;
			}
			else{
				Local_U8Counter++;
			}
		}
		General_VidDummyDelay(100);*/
	/*********************************************************/


}

void ESP_VidConnectNetwork(u8* Copy_U8WIFISSD , u8* Copy_U8WIFIPassword){
    /*
        1- AT+CWJAP_CUR="Copy_U8WIFISSD","Copy_U8WIFIPassword"
    */
	Array_ToBe_Zeroes(GlobalU8ArrRecResponse , RecResArrSize);
	Array_ToBe_Zeroes(ArrToSaveStr , 70);
	u8 Local_U8Counter = 1;

	strcat(ArrToSaveStr,(char*)"AT+CWJAP_CUR=\"");
	strcat(ArrToSaveStr,Copy_U8WIFISSD);
	strcat(ArrToSaveStr,"\",\"");
	strcat(ArrToSaveStr,Copy_U8WIFIPassword);
	strcat(ArrToSaveStr,"\"\r\n");

	UART_VidTransmit(ArrToSaveStr);
	while(GlobalU8ArrRecResponse[Local_U8Counter-1] != 'K'){/*WIFI CONNECTED*/
		do
		{
			GlobalU8ArrRecResponse[Local_U8Counter]=(u8)UART_U8Receive();
		}while(GlobalU8ArrRecResponse[Local_U8Counter] == 0);
		if(Local_U8Counter == RecResArrSize){
			break;
		}
		else{
			if(GlobalU8ArrRecResponse[Local_U8Counter-1] == 'R' && GlobalU8ArrRecResponse[Local_U8Counter] == 'R'){
				/*Connection Error --> Re send The Command*/
				UART_VidTransmit(ArrToSaveStr);
				Local_U8Counter = 1;
				continue;
			}
			Local_U8Counter++;
		}
	}

}

void ESP_VidConnectToServer(u8* Copy_U8Mode , u8* Copy_U8IP , u8* Copy_U8Port){
    /*
        AT+CIPSTART="Copy_U8Mode","Copy_U8IP",Copy_U8Port
    */


	Array_ToBe_Zeroes(GlobalU8ArrRecResponse , RecResArrSize);
	Array_ToBe_Zeroes(ArrToSaveStr , 70);
	u8 Local_U8Counter = 1;


	strcat(ArrToSaveStr,"AT+CIPSTART=\"");
	strcat(ArrToSaveStr,Copy_U8Mode);
	strcat(ArrToSaveStr,"\",\"");
	strcat(ArrToSaveStr,Copy_U8IP);
	strcat(ArrToSaveStr,"\",");
	strcat(ArrToSaveStr,Copy_U8Port);
	strcat(ArrToSaveStr,"\r\n");
	MSTK_voidSetBusyWait(400000);/*400ms*/

	UART_VidTransmit(ArrToSaveStr);
/*	3 Responses--> {"CONNECT\r\nOK\r\n" , "ALREADY CONNECT\r\nERROR\r\n" , "ERROR\r\n"}*/
	while(GlobalU8ArrRecResponse[Local_U8Counter-1] != 'K'){/*CONNECTED \r\n OK*/
		do
		{
			GlobalU8ArrRecResponse[Local_U8Counter]=(u8)UART_U8Receive();
		}while(GlobalU8ArrRecResponse[Local_U8Counter] ==0);
		if(Local_U8Counter == RecResArrSize){
			Local_U8Counter=0;
		}
		else{
			if(GlobalU8ArrRecResponse[Local_U8Counter-1] == 'R' && GlobalU8ArrRecResponse[Local_U8Counter] == 'E'){
				break;/*ALREADY CONNECT*/
			}
			else if(GlobalU8ArrRecResponse[Local_U8Counter-1] == 'R' && GlobalU8ArrRecResponse[Local_U8Counter] == 'R'){
				/*Connection Error --> Re send The Command*/
				UART_VidTransmit(ArrToSaveStr);
				Local_U8Counter = 1;
				continue;
			}
			else if(GlobalU8ArrRecResponse[Local_U8Counter-1] == 'N' && GlobalU8ArrRecResponse[Local_U8Counter] == 'N'){
				MSTK_voidSetBusyWait(100);
				break;/*	Already Connected	*/
			}
			/*	In All Other Cases No Problems So Continue Receiving */
			Local_U8Counter++;
		}

}


}

void ESP_VidGetFile(u8* Copy_U8NOofCharacters , u8* Copy_U8WebsiteFilePath){
    /*
        AT+CIPSEND=Copy_U8NOofCharacters+2
        GET Copy_U8WebsiteFilePath
    */
//	GetFile_Start:

	Array_ToBe_Zeroes(GlobalU8ArrRecResponse , RecResArrSize);
	Array_ToBe_Zeroes(ArrToSaveStr , 70);
	u16 Local_U16Counter = 1;

	strcat(ArrToSaveStr,"AT+CIPSEND=");
	strcat(ArrToSaveStr,Copy_U8NOofCharacters);
	strcat(ArrToSaveStr,"\r\n");


	Local_U16Counter=1;


	UART_VidTransmit(ArrToSaveStr);
/*2 Respnses {"ERROR" , "SEND OK"}*/
	while(GlobalU8ArrRecResponse[Local_U16Counter-1] != 'K'){
		do
		{
			GlobalU8ArrRecResponse[Local_U16Counter]=(u8)UART_U8Receive();
		}while(GlobalU8ArrRecResponse[Local_U16Counter] ==0);
		if(Local_U16Counter == RecResArrSize){
			break;
		}
		else{
			if(GlobalU8ArrRecResponse[Local_U16Counter-1] == 'R' && GlobalU8ArrRecResponse[Local_U16Counter] == 'R'){
				/*Connection Error --> ReConnect To Server Then ReSend The Command*/
				ESP_VidConnectToServer((u8*)CONNECTION_TYPE,(u8*)SERVER_IP,(u8*)PORT_IP);
				UART_VidTransmit(ArrToSaveStr);
				Local_U16Counter = 1;
				continue;
			}
			else if(GlobalU8ArrRecResponse[Local_U16Counter-1] == 'N' && GlobalU8ArrRecResponse[Local_U16Counter] == 'N'){
				MSTK_voidSetBusyWait(100);
				break;/*	ALREADY CONNECTED*/
			}

			Local_U16Counter++;
		}
	}//

//	ESP_VidSendNoOfCharacters(66);

	u8 Local_U8StartRecord=0;
	Array_ToBe_Zeroes(ArrToSaveStr , 70);

	strcat(ArrToSaveStr,"GET ");
	strcat(ArrToSaveStr,Copy_U8WebsiteFilePath);
	strcat(ArrToSaveStr,"\r\n");



	UART_VidTransmit(ArrToSaveStr);
	/*LOOP On L In Closed*/
	Local_U16Counter=0;/*DO NOT CHANGE IT TO ONE EVVVERRR*/

	while(Global_U8ArrRecResponse_Buffer[Local_U16Counter-1] != 'S'){
		do
		{
			Global_U8ArrRecResponse_Buffer[Local_U16Counter]=(u8)UART_U8Receive();
		}while(Global_U8ArrRecResponse_Buffer[Local_U16Counter] == 0 || Global_U8ArrRecResponse_Buffer[Local_U16Counter] == '\n');

		if(Local_U16Counter == PAGE_SIZE){
			break;
		}
		else{
			/*ERROR Handling*/
			if(GlobalU8ArrRecResponse[Local_U16Counter-1] == 'R' && GlobalU8ArrRecResponse[Local_U16Counter] == 'R'){
				/*Connection Error --> ReSend The Command*/
				UART_VidTransmit(ArrToSaveStr);
				Local_U16Counter = 1;
				continue;
			}

			/*	Check If Server Still Connected Or Not	!!!!!!!!!*/
			/*SEND FAIL*/
//			if(GlobalU8ArrRecResponse[Local_U16Counter-1] == 'N'){
//				goto GetFile_Start;/*Very BAD!!!!!*/
//			}

			/*	Deal With First Line --> +IPD,No::	*/
			if(Global_U8ArrRecResponse_Buffer[Local_U16Counter]=='+'){
				while(1){
					Global_U8ArrRecResponse_Buffer[Local_U16Counter]=(u8)UART_U8Receive();
					if(Global_U8ArrRecResponse_Buffer[Local_U16Counter]==':'){
						break;
					}
				}
			}
//+IPD,N::0

			if(Global_U8ArrRecResponse_Buffer[0]==':' && Global_U8ArrRecResponse_Buffer[1]==':' ){/*First Line Only*/
				Local_U8StartRecord =1;
//				Local_U16Counter=0;/*Will be Incremented At The End Of the Loop To Start New Iteration With Value=1*/
				continue;
				/*If First : Comes In Index 1 --> Handle This Case  */
			}
			else if( 0 == Local_U8StartRecord ){
//				Local_U16Counter = Local_U16Counter ^ 1;/*Toggle Value-->0 and1 */
				if( 1 == Local_U16Counter ){
					Local_U16Counter = 0;
				}
				else if ( 0 == Local_U16Counter ){
					Local_U16Counter = 1;
				}
			}

			if( 1 == Local_U8StartRecord ){
				Local_U16Counter++;
			}

		}
	}
}



void ESP_VidSendNoOfCharacters(u8 Copy_U8PageNumber){

	Array_ToBe_Zeroes(GlobalU8ArrRecResponse , RecResArrSize);
	Array_ToBe_Zeroes(ArrToSaveStr , 70);


	u8 Local_U8ArrAsciiCharNo[5]={0};
	u8 Local_U8Counter=0;

	/*	Send Page Request	*/
	/*	Deal With No. Of Characters */
    Local_U8Counter = 64;/*Init With 64 Char.*/
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


	strcat(ArrToSaveStr,"AT+CIPSEND=");
	strcat(ArrToSaveStr,Local_U8ArrAsciiCharNo);
	strcat(ArrToSaveStr,"\r\n");


	Local_U8Counter=1;

	UART_VidTransmit(ArrToSaveStr);
/*2 Respnses {"ERROR" , "SEND OK"}*/
	while(GlobalU8ArrRecResponse[Local_U8Counter-1] != 'K'){
		do
		{
			GlobalU8ArrRecResponse[Local_U8Counter]=(u8)UART_U8Receive();
		}while(GlobalU8ArrRecResponse[Local_U8Counter] ==0);
		if(Local_U8Counter == RecResArrSize){
			break;
		}
		else{
			if(GlobalU8ArrRecResponse[Local_U8Counter-1] == 'R' && GlobalU8ArrRecResponse[Local_U8Counter] == 'R'){
				/*Connection Error --> ReConnect To Server Then ReSend The Command*/
				ESP_VidConnectToServer((u8*)CONNECTION_TYPE,(u8*)SERVER_IP,(u8*)PORT_IP);
				UART_VidTransmit(ArrToSaveStr);
				Local_U8Counter = 1;
				continue;
			}
			else if(GlobalU8ArrRecResponse[Local_U8Counter-1] == 'N' && GlobalU8ArrRecResponse[Local_U8Counter] == 'N'){
				MSTK_voidSetBusyWait(200);
				break;/*	ALREADY CONNECTED*/
			}

			Local_U8Counter++;
		}
	}
}


void ESP_VidGet(u8* Copy_U8WebsiteFilePath , u8 Copy_U8PageNumber){

	u8 Local_U8Counter=0;
	u8 Local_U8ArrAsciiPageNo[5]={0};
	Array_ToBe_Zeroes(ArrToSaveStr , 70);
	itoa(Copy_U8PageNumber,Local_U8ArrAsciiPageNo,10);/*	10 --> Base of No.(Decimal)-->PHP-URL*/


	strcat(ArrToSaveStr,"GET ");
	strcat(ArrToSaveStr,Copy_U8WebsiteFilePath);
	strcat(ArrToSaveStr,Local_U8ArrAsciiPageNo);
	strcat(ArrToSaveStr,"\r\n");

	UART_VidTransmit(ArrToSaveStr);
	/*LOOP On L In Closed*/
	Local_U8Counter=1;

	while(GlobalU8ArrRecResponse[Local_U8Counter-1] != 'K'){
		do
		{
			GlobalU8ArrRecResponse[Local_U8Counter]=(u8)UART_U8Receive();
		}while(GlobalU8ArrRecResponse[Local_U8Counter] == 0 && GlobalU8ArrRecResponse[Local_U8Counter] != '\r' && GlobalU8ArrRecResponse[Local_U8Counter] != '\n' );

		if(Local_U8Counter == RecResArrSize){
			break;
		}
		else{
			/*ERROR Handling*/
			if(GlobalU8ArrRecResponse[Local_U8Counter-1] == 'R' && GlobalU8ArrRecResponse[Local_U8Counter] == 'R'){
				/*Connection Error --> ReSend The Command*/
				UART_VidTransmit(ArrToSaveStr);
				Local_U8Counter = 1;
				continue;
			}
			Local_U8Counter++;
		}
	}
}





u8 ESP_U8IsConnect(void){
	u8 U8ReturnedData=0;
	u8 Local_U8Counter=1;
	Array_ToBe_Zeroes(GlobalU8ArrRecResponse , RecResArrSize);

	UART_VidTransmit((u8*)"AT+CIPSTATUS\r\n");

	while(GlobalU8ArrRecResponse[Local_U8Counter-1] != 'K'){/*STATUS:2 or 5*/
		do
		{
			GlobalU8ArrRecResponse[Local_U8Counter]=(u8)UART_U8Receive();
		}while(GlobalU8ArrRecResponse[Local_U8Counter] ==0);
		if(Local_U8Counter == RecResArrSize){
			break;
		}
		else{
			if(GlobalU8ArrRecResponse[Local_U8Counter-1] == ':'){
				if('2' == GlobalU8ArrRecResponse[Local_U8Counter] || '4' == GlobalU8ArrRecResponse[Local_U8Counter]){
					U8ReturnedData = 1;
				}
				else if ('5' == GlobalU8ArrRecResponse[Local_U8Counter]){
					U8ReturnedData = 0;
				}
				break;
			}
			else if(GlobalU8ArrRecResponse[Local_U8Counter-1] == 'R' && GlobalU8ArrRecResponse[Local_U8Counter] == 'R'){
				/*Connection Error --> Re send The Command*/
				UART_VidTransmit((u8*)"AT+CIPSTATUS\r\n");
				Local_U8Counter = 1;
				continue;
			}
			Local_U8Counter++;
		}
	}

	return U8ReturnedData;

}





