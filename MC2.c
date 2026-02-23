#include "spi.h"

#define SWITCH_PRESSED 1
#define SWITCH_NOT_PRESSED 0

int main(void)
{
	uint8 data_received;  // Variable to store the data received from the main
	SPI_initSecondary();  // Initialize the microcontroller as an SPI secondary
	SET_BIT(DDRC, PC3);  // Configure PC3 as an output pin for controlling an LED
	while(1)
	{
		data_received = SPI_receiveByte();  // Receive data from the main microcontroller via SPI
		if(data_received == SWITCH_PRESSED)  // If the received data indicates the switch is pressed
		{
			SET_BIT(PORTC, PC3);  // Turn the LED on
		}
		else if(data_received == SWITCH_NOT_PRESSED)  // If the received data indicates the switch is not pressed
		{
			CLEAR_BIT(PORTC, PC3);  // Turn the LED off
		}						
	}
}
