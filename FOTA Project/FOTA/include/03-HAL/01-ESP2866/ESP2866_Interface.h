/******************************************************************/
/* Author	: Mahmoud Rajab										  */
/* Date		: 27 Nov 2021										  */
/* Version	: V01												  */
/******************************************************************/

#ifndef ESP2866_INTERFACE_H
#define ESP2866_INTERFACE_H



void ESP_VidInit(void);

void ESP_VidConnectNetwork(u8* Copy_U8WIFISSD , u8* Copy_U8WIFIPassword);

void ESP_VidConnectToServer(u8* Copy_U8Mode , u8* Copy_U8IP , u8* Copy_U8Port);

void ESP_VidGetFile(u8* Copy_U8NOofCharacters , u8* Copy_U8WebsiteFilePath);


void ESP_VidGet(u8* Copy_U8WebsiteFilePath , u8 Copy_U8PageNumber);//

void ESP_VidSendNoOfCharacters(u8 Copy_U8PageNumber);

u8 ESP_U8IsConnect(void);




#endif


