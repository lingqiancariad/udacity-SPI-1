#include "spi.h"

#define SWITCH_PRESSED 1
#define SWITCH_NOT_PRESSED 0

int main(void)
{
	SPI_initMaster();  // Initialize the microcontroller as the SPI master
	CLEAR_BIT(DDRA, PA0);  // Configure PA0 as an input pin for reading the state of the switch
	while(1)
	{
		if(BIT_IS_SET(PINA, PA0))  // If the switch connected to PA0 is pressed
		{
			SPI_sendByte(SWITCH_PRESSED);  // Send the value indicating the switch is pressed over SPI
		}
		else  // If the switch is not pressed
		{
			SPI_sendByte(SWITCH_NOT_PRESSED);  // Send the value indicating the switch is not pressed over SPI
		}						
	}
}
