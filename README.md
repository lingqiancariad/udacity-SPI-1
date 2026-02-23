### This exercise consists of 2 main parts.

Configuring the low-level SPI driver
Implementation of the application layer of both microcontrollers.
Configuring low-level SPI Driver:

Let's build SPI driver that consists of many files such as "spi.c" and "spi.h". However, we will focus on the functions exist in "spi.c" in order to be able to configure the SPI module.

As we learned through the lesson, configuring SPI registers is about setting some bits to one or clearing some bits to zero, so this is general formula on how to set or clear a bit in any register:

Setting a bit in any register:

To set a bit in any register in embedded systems programming (such as working with Atmega16), you can use the bitwise OR operator (|) along with the bit shift operator (<<).

Syntax:

```register |= (1 << bit_position);```

Explanation:

register: The name of the register where you want to set the bit.
1: A binary value with a single bit set to 1.
<< bit_position: This shifts the 1 by bit_position places to the left, creating a mask with the bit you want to set.
|=: The bitwise OR operation ensures that the specified bit is set to 1, while leaving the other bits unchanged.
Example:

Let's say you want to set bit 3 in the PORTB register

```PORTB |= (1 << 3);```

This operation only affects bit 3 of the PORTB register, and all other bits remain unchanged.

Clearing a bit in any register:

To clear a bit in any register, you can use the bitwise AND operator (&) along with the bitwise NOT operator (~) and the bit shift operator (<<). This will set a specific bit to 0 while leaving all other bits unchanged.

Syntax:

```register &= ~(1 << bit_position);```

Explanation:

register: The name of the register where you want to clear the bit.
1: A binary value with a single bit set to 1.
<< bit_position: This shifts the 1 by bit_position places to the left, creating a mask with the bit you want to clear.
~: The bitwise NOT operator inverts all bits in the mask (so the bit you want to clear becomes 0 and all others become 1).
&=: The bitwise AND operation clears the specified bit (sets it to 0) while leaving the other bits unchanged.
Example:

Let's say you want to clear bit 3 in the PORTB register:

```PORTB &= ~(1 << 3);```

This operation only affects bit 3 of the PORTB register, leaving all other bits unchanged.

Data Direction Registers (DDR)

In microcontrollers like the Atmega16, each I/O port has a Data Direction Register (DDR) that controls whether each pin in the port is configured as an input or output. There are several data direction registers for different ports, like DDRA, DDRB, DDRC, and DDRD.

DDR Register controls the direction of data flow:
Setting a bit in the DDR register to 1 configures the corresponding pin as an output.
Setting a bit to 0 configures the corresponding pin as an input.
For example:

DDRB controls the direction for the pins in Port B.

DDRC controls the direction for the pins in Port C.

How to Set a Pin as Output or Input:

Setting a Pin as Output:

To set a pin as an output, you set the corresponding bit in the DDR register to 1.

Syntax:

```DDRx |= (1 << pin_number); // Set pin as output```

Example:

To configure pin 2 of Port B (PB2) as an output:

```DDRB |= (1 << 2); // Set PB2 as output```

This sets bit 2 of DDRB to 1, making PB2 an output pin.

Setting a Pin as Input:

To set a pin as an input, you clear the corresponding bit in the DDR register to 0.

Syntax:

```DDRx &= ~(1 << pin_number); // Set pin as input```

Example:

To configure pin 3 of Port B (PB3) as an input:

```DDRB &= ~(1 << 3); // Set PB3 as input```

This clears bit 3 of DDRB, making PB3 an input pin.

Setting Multiple Pins as Input or Output:

You can configure multiple pins at once by combining the bitwise OR (|) and bitwise AND (&) operations for different pin numbers.

Example 1 (Multiple Outputs):

To set PB1 and PB2 as output pins:

```DDRB |= (1 << PB1) | (1 << PB2); // Set PB1 and PB2 as outputs```

Example 2 (Multiple Inputs):

To set PC0 and PC1 as input pins:

```DDRC &= ~(1 << PC0) & ~(1 << PC1); // Set PC0 and PC1 as inputs```

Pull-Up Resistors for Input Pins:

When configuring a pin as input, you might want to enable the internal pull-up resistor to avoid a floating input. This is done by writing a 1 to the corresponding PORT register.

Example:

To set PB3 as an input and enable the internal pull-up resistor:

```DDRB &= ~(1 << 3); // Set PB3 as input```

```PORTB |= (1 << 3); // Enable pull-up resistor on PB3```

Summary:

Use ```DDRx |= (1 << pin_number)``` to set a pin as output.

Use ```DDRx &= ~(1 << pin_number)``` to set a pin as input.

Enable pull-up resistors for input pins by setting the corresponding bit in the PORTx register.

### Task 1:
Implement the SPI_initMain function, satisfying the following requirements:

Configure SPI Main Pins which are MISO(PB6) as Input, while SCK(PB7), SS(PB4), and MOSI(PB5) as Output.
Enable MSTR bit to make it the main device.
Program SPR [1:0] bits to select SCLK frequency.
Set SPE bit to 1 to enable SPI.

### Task 2:
You will need to implement the SPI_initSecondary function, satisfying the following requirements:

Configure SPI Secondary Pins which are SS(PB4), SCK(PB7), and MOSI(PB5) as Inputs, while MISO(PB6) as Output.
Set SPE equal to 1 to activate SPI.

### Task 3:
You will implement the SPI_sendByte function satisfying these requirements:

take the data of type uint8 to be sent as an argument and save it to SPDR to be sent by SPI
wait until the SPI interrupt flag is set to 1 (data is sent correctly). You can use the macros in common_macros.h as needed.

### Task 4:
Implement the SPI_recieveByte function, satisfying the following requirements:

Take nothing as an argument and return data of type uint8.
Wait until the SPI interrupt flag is set to 1 (data is recieved correctly). You can use the macros in common_macros.h as needed.
Implementation of the Application layer
The project consists of 2 Microcontrollers, "MC1" being the Master/Main and "MC2" being the Slave/Secondary. As shown in the schematic below, MC1 is connected to a push button. When the push button is pressed, a byte of "1" or "0" will be sent through SPI to MC2 to turn ON/OFF the LED.

<img width="1606" height="804" alt="image" src="https://github.com/user-attachments/assets/186ac069-0a0a-472c-8bb3-cf5a7929e9e3" />

This image represents the connection between a push button and a microcontroller, 2 microcontrollers of type ATmega16 connecting to each other through SPI and a LED is connected to the second microcontroller
Schematic that shows the connections between push button, MC1, MC2, and LED respectively

Now, You have implemented all the functions needed for the low level driver and ready to start implementation of the application layer for both MC1 and MC2.

### Task 5:
The following requirements will be implemented in MC1.c.

You will find both microcontrollers are configured with internal 1Mhz Clock in ```"micro_config.h"```.
The switch should be connected to MC1 through PIN0 in PORTA, So you need to configure the data direction for this pin as input.
MC1 reads push button value then send it to MC2 by SPI.
You should use the following macros while sending and receiving bytes from MC1 to MC2 or vise versa ```#define SWITCH_PRESSED 1 #define SWITCH_NOT_PRESSED 0```
Task 6:
The following requirements will be implemented in MC2.c.

The LED should be connected to MC2 through PIN3 in PORTC, so you need to configure the data direction for this pin as the output.
MC2 will receive the push button status and according to it, MC2 will switch ON/OFF the LED.
You should use the following macros while sending and receiving bytes from MC1 to MC2 or vise versa ```#define SWITCH_PRESSED 1 #define SWITCH_NOT_PRESSED 0```
As a way of validating that there are no errors, you can check that the code compiles from the terminal using the following commands:

For MC1.c: ```avr-gcc -mmcu=atmega16 -DF_CPU=1000000UL MC1.c spi.c -o a1.out```
For MC2.c: ```avr-gcc -mmcu=atmega16 -DF_CPU=1000000UL MC2.c spi.c -o a2.out```
