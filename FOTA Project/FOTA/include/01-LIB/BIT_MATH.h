/**************************************/
/******* Author : Mahmoud Rajab *******/
/******* Date   :  18/2/2020   *******/
/******* SWC    :    LIB        *******/
/******* Version:    1.0        *******/
/**************************************/

#ifndef _BIT_MATH_H
#define _BIT_MATH_H

#define SET_BIT(VAR,BITNO) (VAR) |=  (1 << (BITNO))
#define CLR_BIT(VAR,BITNO) (VAR) &= ~(1 << (BITNO))
#define TOGGLE_BIT(VAR,BITNO) (VAR) ^=  (1 << (BITNO))
#define GET_BIT(VAR,BITNO) (((VAR) >> (BITNO)) & 0x01)


#endif