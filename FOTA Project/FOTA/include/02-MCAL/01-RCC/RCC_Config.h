/******************************************************************/
/* Author	: Mahmoud Rajab										  */
/* Date		: 27 Nov 2021										  */
/* Version	: V01												  */
/******************************************************************/

#ifndef 	RCC_CONFIG_H
#define 	RCC_CONFIG_H


/*	RCC Can Be:
 * 				1- RCC_HSE_CRYSTAL
 * 				2- RCC_HSE_RC
 * 				3- RCC_HSI
 * 				4- RCC_PLL	*/

#define RCC_CLOCK_TYPE		RCC_HSI

#if RCC_CLOCK_TYPE == RCC_PLL
/*	RCC PLL Can Be:
 * 					1-RCC_HSE
 * 					2-RCC_HSE_2
 * 					3-RCC_HSI_2
 * 					*/
#define 	RCC_PLL_SRC		RCC_HSE

#endif


#endif