//*****************************************************************************
//
// THIS CODE SHOULD BE UPLOADED TO THE MONITORING DEVICE B
//
//*****************************************************************************


// header files
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include <stdlib.h>


//*****************************************************************************
//
// DEFINE USEFUL VARIABLES
//
//*****************************************************************************

// define variables to determine the state
char stateStr[5] = {0}; // to collect 5 digits + null terminator
int tempToSend;
uint8_t index = 0;


//*****************************************************************************
//
// UART CODE
//
//*****************************************************************************

void tempStateMachine(int receivedTemp) {
	// Turn off all LEDs (redundant but ensures clean start)
	GPIOPinWrite(GPIO_PORTF_BASE,
							 GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0x00);

	// LED on for 3 seconds based on temp range
	if (receivedTemp > 80) {
		// Blue LED
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
	}
	else if (receivedTemp > 32) {
		// Green LED
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
	}
	else {
		// Red LED
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
	}

	// Delay for ~3 seconds
	SysCtlDelay(SysCtlClockGet());

	// Turn off LEDs
	GPIOPinWrite(GPIO_PORTF_BASE,
							 GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0x00);

}



void UARTIntHandler(void) {
	// get then clear the interrupt
	uint32_t ui32Status;
	ui32Status = UARTIntStatus(UART1_BASE, true);
	UARTIntClear(UART1_BASE, ui32Status);

	// loop while there are characters
	while (UARTCharsAvail(UART1_BASE)) {
		char c = UARTCharGetNonBlocking(UART1_BASE);
		UARTCharPutNonBlocking(UART0_BASE, c);

		if (c != '\n' && c != '\r' && index < 3) {
			stateStr[index++] = c;
		}
		else if ((c == '\n' || c == '\r') && index == 3) {
			stateStr[4] = '\0';
			index = 0;
		
			int tempToSend = atoi(stateStr);
		}
		
	}
	
	tempStateMachine(tempToSend);
	
}

// void UARTIntHandler(void) {
//     // Get and clear the interrupt status
//     uint32_t ui32Status = UARTIntStatus(UART1_BASE, true);
//     UARTIntClear(UART1_BASE, ui32Status);
// 
//     // Echo received characters to PuTTY via UART0
//     while (UARTCharsAvail(UART1_BASE)) {
//         char c = UARTCharGet(UART1_BASE);
//         UARTCharPut(UART0_BASE, c);
//     }
// }





//*****************************************************************************
//
// MAIN CODE
//
//*****************************************************************************

int main(void) {
	// enable clock
	SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

	// enable LED
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); //enable GPIO port for LED
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3); // enable all LEDs

	
	// enable UART/GPIO periphs
  SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

	// configure GPIO pins for UART function
	GPIOPinConfigure(GPIO_PB0_U1RX);
	GPIOPinConfigure(GPIO_PA1_U0TX);
	GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_1);
	GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0);

	// config UART periphs
	UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
			(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

	UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(), 115200,
			(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

	IntMasterEnable(); //enable processor interrupts
	IntEnable(INT_UART1); //enable the UART interrupt
	UARTIntEnable(UART1_BASE, UART_INT_RX); //only enable RX interrupt
	
	UARTFIFOEnable(UART1_BASE);
	UARTFIFOEnable(UART0_BASE);

	
	// blink LED to show connection
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
	SysCtlDelay(SysCtlClockGet()); // 1 second = SysCtlClockGet()
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0x00);

	// print state header
	UARTCharPut(UART0_BASE, 'S');
	UARTCharPut(UART0_BASE, 't');
	UARTCharPut(UART0_BASE, 'a');
	UARTCharPut(UART0_BASE, 't');
	UARTCharPut(UART0_BASE, 'e');
	UARTCharPut(UART0_BASE, '\n');
	UARTCharPut(UART0_BASE, '\r'); 

	while (1); //let interrupt handler do the UART echo function

	return 0;
}
