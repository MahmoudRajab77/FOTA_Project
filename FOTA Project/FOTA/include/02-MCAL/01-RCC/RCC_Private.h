/******************************************************************/
/* Author	: Mahmoud Rajab										  */
/* Date		: 27 Nov 2021										  */
/* Version	: V01												  */
/******************************************************************/



#ifndef RCC_PRIVATE_H
#define RCC_PRIVATE_H



#define RCC_BASE_ADD				(0x40021000)

//#define RCC_CR						*((u32 *)(RCC_BASE_ADD + 0x00))
//#define RCC_CFGR					*((u32 *)(RCC_BASE_ADD + 0x04))
//#define RCC_CIR						*((u32 *)(RCC_BASE_ADD + 0x08))
//#define RCC_APB2RSTR				*((u32 *)(RCC_BASE_ADD + 0x0C))
//#define RCC_APB1RSTR				*((u32 *)(RCC_BASE_ADD + 0x10))
//#define RCC_AHBENR					*((u32 *)(RCC_BASE_ADD + 0x14))
//#define RCC_APB2ENR					*((u32 *)(RCC_BASE_ADD + 0x18))
//#define RCC_APB1ENR					*((u32 *)(RCC_BASE_ADD + 0x1C))
//#define RCC_BDCR					*((u32 *)(RCC_BASE_ADD + 0x20))
//#define RCC_CSR						*((u32 *)(RCC_BASE_ADD + 0x24))


#define  RCC_HSE_CRYSTAL	0
#define  RCC_HSE_RC			1
#define  RCC_HSI			2
#define  RCC_PLL			3

typedef struct{
	u32 CR;
	u32 CFGR;
	u32 CIR;
	u32 APB2RSTR;
	u32 APB1RSTR;
	u32 AHBENR;
	u32 APB2ENR;
	u32 APB1ENR;
	u32 BDCR;
	u32 CSR;
}RCC_st;

//RCC_ST* RCC = 0x40021000;		//Base Address
#define RCC		((RCC_st*)0x40021000)


#endif
