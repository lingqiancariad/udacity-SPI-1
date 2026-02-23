#include "spi.h"

void SPI_initMaster(void) 
{
	DDRB = DDRB | (1<<PB4);  		// Set PB4 (SS) as output. This is the Secondary Select pin used in SPI.
	DDRB = DDRB | (1<<PB5);  		// Set PB5 (MOSI) as output. This is the Main Out Secondary In pin.
	DDRB = DDRB & ~(1<<PB6); 		// Set PB6 (MISO) as input. This is the Main In Secondary Out pin.
	DDRB = DDRB | (1<<PB7);  		// Set PB7 (SCK) as output. This is the Serial Clock pin used to synchronize communication.
	SPCR = (1<<SPE) | (1<<MSTR);  	// Enable SPI by setting SPE bit and configure the device as SPI Main by setting MSTR bit.
}

void SPI_initSlave(void)
{ 
	DDRB = DDRB & (~(1<<PB4));  	// Set PB4 (SS) as input. The main will control this pin to select the secondary.
	DDRB = DDRB & (~(1<<PB5));  	// Set PB5 (MOSI) as input. The secondary receives data from the main on this pin.
	DDRB = DDRB | (1<<PB6);     	// Set PB6 (MISO) as output. The secondary sends data to the main on this pin.
	DDRB = DDRB & (~(1<<PB7));  	// Set PB7 (SCK) as input. The secondary receives the clock signal from the main.
	SPCR = (1<<SPE);  				// Enable SPI by setting SPE bit, and use the default clock (Fosc/4).
}

void SPI_sendByte(const uint8 data) 
{
	SPDR = data; 						// Send data via SPI by loading it into the SPI Data Register (SPDR)
	while(BIT_IS_CLEAR(SPSR, SPIF)){} 	// Wait until the SPI Interrupt Flag (SPIF) is set, indicating data has been sent
}

uint8 SPI_recieveByte(void)
{
	while(BIT_IS_CLEAR(SPSR, SPIF)){} 	// Wait until the SPI Interrupt Flag (SPIF) is set, indicating data has been received
    return SPDR; 						// Return the received byte from the SPI Data Register (SPDR)
}

