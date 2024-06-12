/******************************************************************/
/* Author	: Mahmoud Rajab										  */
/* Date		: 27 Nov 2021										  */
/* Version	: V01												  */
/******************************************************************/




#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "STK_Interface.h"


#include "PowerControl_Interface.h"
#include "PowerControl_Private.h"
#include "PowerControl_Config.h"


void PWC_StopModeEnter(void){
	/*	Configure As Deep Sleep Mode	*/
	SET_BIT(SCB -> SCR , SLEEPDEEP);

	/*	Clear PDDS(Power Down Deep Sleep) Bit */
	SET_BIT(PWC -> CR , PDDS );

	/*	Set LPDS(Low Power Deep Sleep) --> Voltage regulator in low-power mode during Stop mode*/
//	SET_BIT( PWC -> CR , LPDS);

	CLR_BIT(PWC -> CSR ,0);	/*	Clear Wake Up Flag	*/

	/*	Suspend Systick Or Its Interrupt Will Wake Up The System	*/
	MSTK_voidStopInterval();

}
