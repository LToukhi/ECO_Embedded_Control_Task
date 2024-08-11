#include <util/delay.h>

#include "../LIB/STD_Types.h"
#include "../LIB/STD_Macros.h"

#include "../MCAL/MDIO/MDIO.h"

#include "../MCAL/ADC/ADC_Init.h"
#include "../MCAL/ADC/ADC_Prv.h"
#include "../MCAL/ADC/ADC_Config.h"

#include "../MCAL/TIMERS/MTimerS_Init.h"
#include "../MCAL/TIMERS/MTIMERS_Priv.h"
#include "../MCAL/TIMERS/MTIMERS_Config.h"

#include "../MCAL/UART/UART.h"
#include "../MCAL/UART/UART_Private.h"
#include "../MCAL/UART/UART_Config.h"

f32 Sensed_Temp ;
f32 Sensed_Humidity ;
int main(){
	MDIO_voidSetPinDirection(MDIO_PORTA , PIN6 , INPUT)  ;
	MDIO_voidSetPinDirection(MDIO_PORTA , PIN1 , INPUT ) ;
//	MDIO_voidSetPinDirection(MDIO_PORTD , PIN0 , INPUT ) ;
//	MDIO_voidSetPinDirection(MDIO_PORTD , PIN1 , OUTPUT ) ;

	MUART_voidInit(9600) ;
	MADC_VoidADCInit() ;
	MTIMER1_voidInitFastPwm() ;

	while(1)
	{
		_delay_ms(100);
		// Temperature as a value from 0 to 1024
		Sensed_Temp = MADC_U16AnalogRead(PIN6);

		// Humidity as a value from 0 to 1024
		_delay_ms(100);
		Sensed_Humidity = MADC_U16AnalogRead(PIN1) ;

		if ((Sensed_Temp * 0.5) <= 25)
		{
			// Close the fan
			MTIMER1_voidSetPinACompareMatch(0) ;
			// Display fan speed in %
			MUART_voidSendString("Fan is Closed") ;
			MUART_voidSendString("\r\n") ;
			_delay_ms(25) ;
		}
		else
		{
			// Duty value of the generated PWM
			MTIMER1_voidSetPinACompareMatch((Sensed_Temp*65536)/1024.0) ;
			// Display fan speed in %
			MUART_voidSendString("Fan Speed Percentage = ") ;
			MUART_voidSendNumber((Sensed_Temp*0.5*100)/150) ;
			MUART_voidSendString(" %") ;
			MUART_voidSendString("\r\n") ;
			_delay_ms(25) ;
		}

		// Temperature in °C
		Sensed_Temp = Sensed_Temp * 0.5;
		// Humidity in %
		Sensed_Humidity = (((Sensed_Humidity/1024)*4000 - 800)/(3200-800))*100 ;

		// display temperature in °C
		MUART_voidSendString("Temperature = ") ;
		MUART_voidSendNumber(Sensed_Temp) ;
		MUART_voidSendString(" °C") ;
		MUART_voidSendString("\r\n") ;
		_delay_ms(25) ;

		// display humidity in %
		MUART_voidSendString("Humidity = ") ;
		MUART_voidSendNumber(Sensed_Humidity) ;
		MUART_voidSendString(" %") ;
		MUART_voidSendString("\r\n") ;
		MUART_voidSendString("\r\n") ;
		_delay_ms(25) ;
	}
	return 0 ;
}

