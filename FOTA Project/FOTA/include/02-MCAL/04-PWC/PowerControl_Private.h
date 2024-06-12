/******************************************************************/
/* Author	: Mahmoud Rajab										  */
/* Date		: 27 Nov 2021										  */
/* Version	: V01												  */
/******************************************************************/


#ifndef POWERCONTROL_PRIVATE_H
#define POWERCONTROL_PRIVATE_H





/*	In PWC	*/
#define 	LPDS			0

#define 	PDDS			1

typedef struct{
	volatile u32 CR;
	volatile u32 CSR;
}PWC_t;

#define 	PWC_BASEADDRESS		0x40007000

#define		PWC					((PWC_t*)PWC_BASEADDRESS)






/*	In SCB	*/
#define 	SLEEPDEEP		2


typedef struct{

	volatile u32 CPUID;
	volatile u32 ICSR;
	volatile u32 VTOR;
	volatile u32 AIRCR;
	volatile u32 SCR;	/*	Use Only This Register	*/
	volatile u32 CCR;
	volatile u32 SHPR1;
	volatile u32 SHPR2;
	volatile u32 SHPR3;
	volatile u32 SHCSR;
	volatile u32 CFSR;
	volatile u32 HFSR;
	volatile u32 RESERVED;
	volatile u32 MMFAR;
	volatile u32 BFAR;

}SCB_t;

#define 	SCB_BASEADDRESS		0xE000ED00

#define		SCB					((SCB_t*)SCB_BASEADDRESS)


#endif
