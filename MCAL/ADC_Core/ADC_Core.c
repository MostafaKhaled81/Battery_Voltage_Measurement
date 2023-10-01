/*
 * ADC_Core.c
 *
 * Created: 9/8/2023 4:37:21 PM
 *  Author: mk591
 */ 
/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  FileName.c
 *        \brief  
 *
 *      \details  
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "ADC_Core.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
 uint32 ADC_VAL=0;
/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


/******************************************************************************
* \Syntax          : void ADC_Init(void)       
* \Description     : Describe this service                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : parameterName   Parameter Describtion                     
* \Parameters (out): None                                                      
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK                                  
*******************************************************************************/
void ADC_Init(void)
{
	/*Vref*/
	#if (ADC_VOLTAGE_REFFERENCE==ADC_VREF_VCC)
	  CLR_BIT(ADMUX,7);
	  SET_BIT(ADMUX,6);
	#elif (ADC_VOLTAGE_REFFERENCE==ADC_VREF_AREF)
	  CLR_BIT(ADMUX,7);
	  CLR_BIT(ADMUX,6);
	#elif (ADC_VOLTAGE_REFFERENCE==ADC_VREF_INTERNAL)
	  SET_BIT(ADMUX,7);
	  SET_BIT(ADMUX,6);
    #endif
	
	
	/*READING TYPE*/
	#if (ADC_REG_ADJUST==ADC_RIGHT_ADJUCT)
      CLR_BIT(ADMUX,5);
	#elif (ADC_REG_ADJUST==ADC_LEFT_ADJUCT)
	   SET_BIT(ADMUX,5);
    #endif
	
	
	/*PRESCALER*/
	ADCSRA|=ADC_PRESCALER;


	/*CHANNEL*/
	ADMUX|=ADC_CHANNEL;
	

	/*CONVERSION TRIGGER*/
	#if (ADC_CONVERSION_TRIGGER==ADC_CONVERSION_SINGLE_CONVERSION)
      CLR_BIT(ADCSRA,5);
	#elif (ADC_CONVERSION_TRIGGER==ADC_CONVERSION_FREE_RUNNING)
	  SET_BIT(ADCSRA,5);
	  SFIOR|=(0X00<<5);
	#elif (ADC_CONVERSION_TRIGGER==ADC_CONVERSION_Analog_Comparator)
	  SET_BIT(ADCSRA,5);
	  SFIOR|=(0X01<<5);
	#elif (ADC_CONVERSION_TRIGGER==ADC_CONVERSION_External_Interrupt_Request_0)
	  SET_BIT(ADCSRA,5);
	  SFIOR|=(0X02<<5);
	#elif (ADC_CONVERSION_TRIGGER==ADC_CONVERSION_Timer_Counter0_Compare_Match)
	  SET_BIT(ADCSRA,5);
	  SFIOR|=(0X03<<5);
	#elif (ADC_CONVERSION_TRIGGER==ADC_CONVERSION_Timer_Counter0_Overflow)
	  SET_BIT(ADCSRA,5);
	  SFIOR|=(0X04<<5);
	#elif (ADC_CONVERSION_TRIGGER==ADC_CONVERSION_Timer_Counter_Compare_Match_B)
	  SET_BIT(ADCSRA,5);
	  SFIOR|=(0X05<<5);
	#elif (ADC_CONVERSION_TRIGGER==ADC_CONVERSION_Timer_Counter1_Overflow)
	  SET_BIT(ADCSRA,5);
	  SFIOR|=(0X06<<5);
	#elif (ADC_CONVERSION_TRIGGER==ADC_CONVERSION_Timer_Counter1_Capture_Event)
	  SET_BIT(ADCSRA,5);
	  SFIOR|=(0X07<<5);
    #endif
	
	
	/*INT ENABLE*/
	#if (ADC_INTERRUPT_STATUS==ADC_INTERRUPT_DISABLED)
	  CLR_BIT(ADCSRA,3);
	#elif (ADC_INTERRUPT_STATUS==ADC_INTERRUPT_ENABLED)
	  IRQH_SetGlobalINT(INT_ENABLE);
	  SET_BIT(ADCSRA,3);
    #endif
	
	
	/*ADC ENABLE*/
	SET_BIT(ADCSRA,7);
	
}
/******************************************************************************
* \Syntax          : void ADC_Read(void)
* \Description     : Describe this service
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/
void ADC_Read(void)
{
	uint32 Digital_Read=0;
	/*START CONVERSION*/
	SET_BIT(ADCSRA,6);
	#if (ADC_INTERRUPT_STATUS==ADC_INTERRUPT_DISABLED)
	  while(GET_BIT(ADCSRA,4)==0);
	  #if (ADC_REG_ADJUST==ADC_RIGHT_ADJUCT)
	    Digital_Read=ADC_RES;
      #elif (ADC_REG_ADJUST==ADC_LEFT_ADJUCT)
	    Digital_Read=(ADCH<<2)|(ADCL>>6);
	  #endif
    #endif
	ADC_VAL=(Digital_Read*5000)/1023;
}
/**********************************************************************************************************************
 *  END OF FILE: FileName.c
 *********************************************************************************************************************/