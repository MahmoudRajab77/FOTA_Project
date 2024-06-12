/******************************************************************/
/* Author	: Mahmoud Rajab										  */
/* Date		: 27 Nov 2021										  */
/* Version	: V01												  */
/******************************************************************/

#ifndef BL_CONFIG_H
#define BL_CONFIG_H




#define		APP_VALIDATIONADD		(0x0800D2F0-0x02)/*	Last 4 Bytes In Flash	*/
#define		APP_STARTADDRESS		(0x08002800)
#define 	APP_RESETVECTORADD		((APP_STARTADDRESS)+0x04)
#define 	PAGE_SIZE				1500
#define 	RecBufferSize			50


#define 	WIFISSID				"A.C.F.F.4"
#define 	WIFIPASSWORD			"ana  ana"

#define 	CONNECTION_TYPE			"TCP"
#define 	SERVER_IP				"162.253.155.226"
#define 	PORT_IP					"80"

#define		SENDPAGENO_PATH			"GET http://fota-oto.freevar.com/PageRequest.php?PageNo="
#define		SENDPAGENO_PATH_LENGTH	57/*As Integer*/

#define 	PAGE_PATHE				"http://fota-oto.freevar.com/uploads/RequestedPage.txt"
#define 	PAGE_PATH_LENGTH		"59"/*As String*/

#define 	STATUFILE_PATH			"GET http://fota-oto.freevar.com/uploads/Status_File.txt"
#define 	STATUFILE_PATH_LENGTH	57/*As Integer*/

#define 	MESSAGE_PATH			"GET http://fota-oto.freevar.com/SendStatus.php?Status="
#define 	MESSAGE_PATH_LENGTH		56/*As Integer*/




#endif
