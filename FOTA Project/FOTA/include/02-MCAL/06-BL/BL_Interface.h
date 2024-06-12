/******************************************************************/
/* Author	: Mahmoud Rajab										  */
/* Date		: 27 Nov 2021										  */
/* Version	: V01												  */
/******************************************************************/

#ifndef BL_INTERFACE_H
#define BL_INTERFACE_H





typedef void (*Function_t)(void);	/*	Pointer To Function	*/



void Parser_voidParseRecord(u8* Copy_u8BufData);

void ParseData(u8* Copy_u8BufData);

u8 AsciToHex(u8 Copy_u8Asci);

void Request_Page(u8 Page_Number);

void Copy_Line_to_Buffer( u8 U8LineNo );

void Array_ToBe_Zeroes(volatile u8* Ptr_U8Arr , u16 Copy_U16ArrSize);

u8 	 U8EndOfFileValidation(void);

u8 	 U8EndOfPageValidation(void);

u32  SumOfArr(u8* Arr , u16 Size);

u8   Record_CheckSum(void);

u8	 NewApptoBurn(void);

void General_VidServerMsg(u8* Copy_U8PtrMsg , u8 Copy_U8Length);

u8 HexToAsci(u8 Copy_U8Hex);/*	Used In Decryption Only	*/

u8 ASCIIToHex(u8 Copy_U8ASCII);/*	Used In Decryption Only	*/





#endif
