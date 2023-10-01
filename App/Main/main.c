#include "LCD_Core.h"
#include "PORT_CORE.h"
#include "BVM_Core.h"
#include "IRQH_Core.h"

#define F_CPU 16000000U
#include <util/delay.h>

int main(void)
{
	PORT_INIT();
	LCD_Init();
	BVM_INIT();
	IRQH_SetGlobalINT(INT_ENABLE);
	IRQH_SetCallBack(ADC_Conversion_Complete_VECTOR_INDEX,BVM_Read);
	ADC_Read();
	while (1)
	{
		LCD_WriteInteger(BVM);
		LCD_WriteChar('m');
		LCD_WriteChar('v');
		_delay_ms(100);
		LCD_GOTO(0,0);
	}
}