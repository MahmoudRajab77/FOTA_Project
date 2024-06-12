/******************************************************************/
/* Author	: Mahmoud Rajab										  */
/* Date		: 27 Nov 2021										  */
/* Version	: V01												  */
/******************************************************************/






#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "FPEC_Interface.h"





u16 Data[100] = {0};	/*	Array Of 2-Bytes(u16) Elements
 	 	 	 	 	 	 	These Elements Will Be Flashed On Flash Memory.
 	 	 	 	 	 	 	Note: FPEC Can Flash 16 bits In Once.
 	 	 	 	 	 	 	That Is The Reason Of u16 Elements
 	 	 	 	 	 	 	*/
u32 Address= 0x08002800;







u8 AsciToHex(u8 Copy_u8Asci)
{
	u8 Result;
	if ( (Copy_u8Asci >= 48) && (Copy_u8Asci <= 57) )
	{
		Result = Copy_u8Asci - 48;	/*	'0'=48, '1'=49, .....	*/
	}

	else
	{
		Result = Copy_u8Asci - 55;/*	Convert A=65, B=66, C D E F=70, Into From ASCII To HEX	*/
	}

	return Result;
}


void ParseData(u8* Copy_u8BufData)
{
	u8 DigitLow,DigitHigh,CC,i;
	u8 DataDigit0,DataDigit1,DataDigit2,DataDigit3;
	u8 DataCounter = 0;

	/* Get Character Count */
	DigitHigh = AsciToHex (Copy_u8BufData[1]);	/*	Index=0 Is The (:) So Starts With Index=1	*/
	DigitLow  = AsciToHex (Copy_u8BufData[2]);
	CC        = (DigitHigh<<4) | DigitLow ;

	/* Get Address From Record	*/
	DataDigit0 = AsciToHex (Copy_u8BufData[3]);
	DataDigit1 = AsciToHex (Copy_u8BufData[4]);
	DataDigit2 = AsciToHex (Copy_u8BufData[5]);
	DataDigit3 = AsciToHex (Copy_u8BufData[6]);

	/* Clear Low Part of Address */
	Address = Address & 0xFFFF0000;
	Address = Address | (DataDigit3) | (DataDigit2 << 4) | (DataDigit1 << 8) | (DataDigit0<<12);

	for (i=0;i<CC/2; i++)	/*	Loop To Loop On Record Data Elements & Store Them In Data Array  */
	{
		DataDigit0 = AsciToHex (Copy_u8BufData[4*i+9 ]);	/*	1- First Data Element In Record Always In Index=9
																2- This Is A 4 Bits Elements Received From Record*/
		DataDigit1 = AsciToHex (Copy_u8BufData[4*i+10]);
		DataDigit2 = AsciToHex (Copy_u8BufData[4*i+11]);
		DataDigit3 = AsciToHex (Copy_u8BufData[4*i+12]);
		/*	Now Convert The Array Element Of Index Of DataCounter Into u16 To Reach The
		 * 	Maximum Write Bits Per Word --> Depends On FPEC  */
		Data[DataCounter] = (DataDigit3 << 8) | (DataDigit2 << 12) | (DataDigit1) | (DataDigit0<<4);
		DataCounter++;
	}

	FPEC_voidFlashWrite(Address,Data,CC/2);	/*	Straight Forward Flashing	*/
}

void ParseUpperAddress(u8* Copy_u8BufData)
{
//	u8 DataDigit0,DataDigit1,DataDigit2,DataDigit3;
//
//	/* Get Address */
//	DataDigit0 = AsciToHex (Copy_u8BufData[3]);
//	DataDigit1 = AsciToHex (Copy_u8BufData[4]);
//	DataDigit2 = AsciToHex (Copy_u8BufData[5]);
//	DataDigit3 = AsciToHex (Copy_u8BufData[6]);
//
//	/* Clear Low Part of Address */
//	Address = Address & (u32)0x0000FFFF;
//	Address = Address | (u32)((u32)(DataDigit3 << 28) | (u32)(DataDigit2 << 24) | (u32)(DataDigit1 << 20) | (u32)(DataDigit0 << 16));
}

void Parser_voidParseRecord(u8* Copy_u8BufData)
{
	/*	Record Type 04 Or 00....
	 * 	04 --> High Part Address
	 * 	00 --> Write Data
	 * 	*/
	switch (Copy_u8BufData[8])
	{
	case '0': ParseData(Copy_u8BufData); break;
	case '4': ParseUpperAddress(Copy_u8BufData); break;
	}
}



