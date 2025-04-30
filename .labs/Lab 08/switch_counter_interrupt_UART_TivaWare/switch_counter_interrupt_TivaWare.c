#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "switch_counter_interrupt_TivaWare.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "inc/tm4c123gh6pm.h"
#include "driverlib/uart.h"


//*****************************************************************************
//
//!
//! Design a counter. The counter is incremented by 1 when SW1 (PF4) or SW2 (PF0) 
//! is pressed. Counter is then sent over UART to be displayed in a serial terminal
//
//*****************************************************************************

// value to increment
volatile uint8_t count = 0;

// flag for main loop to know when count has changed
volatile bool buttonPressed = false;

// character array to store stringified 
// version of count to send over UART
char str[4] = {0, 0, 0, 0};

void PortFunctionInit(void) {
	//
	// Enable Peripheral Clocks 
	//
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

	//
	// Enable pin PF4 for GPIOInput
	//
	GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);

	//
	//First open the lock and select the bits we want to modify in the GPIO commit register.
	//
	HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
	HWREG(GPIO_PORTF_BASE + GPIO_O_CR) = 0x1;

	//
	// Enable pin PF0 for GPIOInput
	//
	GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0);

	//Enable pull-up on PF4 and PF0
	GPIO_PORTF_PUR_R |= 0x11; 
}


void Interrupt_Init(void) {
  IntEnable(INT_GPIOF);  							// enable interrupt 30 in NVIC (GPIOF)
	IntPrioritySet(INT_GPIOF, 0x00); 		// configure GPIOF interrupt priority as 0
	GPIO_PORTF_IM_R |= 0x11;   		// arm interrupt on PF0 and PF4
	GPIO_PORTF_IS_R &= ~0x11;     // PF0 and PF4 are edge-sensitive
  GPIO_PORTF_IBE_R &= ~0x11;   	// PF0 and PF4 not both edges trigger 
  GPIO_PORTF_IEV_R &= ~0x11;  	// PF0 and PF4 falling edge event
}

void uart_Init(void) {
	// configure main clock	
	SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

	// start peripheral clocks
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

	// configure external pins
	GPIOPinConfigure(GPIO_PA0_U0RX);
	GPIOPinConfigure(GPIO_PA1_U0TX);
	
	// mux pins to UART peripheral
	GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

	// configure UART system and packets
	UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
}


//interrupt handler
void GPIOPortF_Handler(void) {
	//SW1 is pressed
	if(GPIO_PORTF_RIS_R&0x10) {
		// acknowledge flag for PF4
		GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_4); 
		
		//counter incremented by 1
		count++;
		
		// set flag for main
		buttonPressed = true;
	}
	
	//SW2 is pressed
  if(GPIO_PORTF_RIS_R&0x01) {
		// acknowledge flag for PF0
		GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_0);
		
		//counter incremented by 1
		count++;
		
		// set flag for main
		buttonPressed = true;
	}
}

int main(void) {
	//initialize the GPIO ports	
	PortFunctionInit();

	//initialize UART0
	uart_Init();
	
	//configure the GPIOF interrupt
	Interrupt_Init();

	// globally enable interrupt
	IntMasterEnable();       		

	//
	// Loop forever.
	//
	while(1) {
		// if button is pressed, send new count value
		if (buttonPressed) {
			// send the characters over UART
			UARTCharPut(UART0_BASE, 'C');
			UARTCharPut(UART0_BASE, 'o');
			UARTCharPut(UART0_BASE, 'u');
			UARTCharPut(UART0_BASE, 'n');
			UARTCharPut(UART0_BASE, 't');
			UARTCharPut(UART0_BASE, '=');
			
			// convert count to ASCII characters
			sprintf(str, "%03u", count);
			
			UARTCharPut(UART0_BASE, str[0]); 
			UARTCharPut(UART0_BASE, str[1]); 
			UARTCharPut(UART0_BASE, str[2]);
			UARTCharPut(UART0_BASE, '\n'); 
			UARTCharPut(UART0_BASE, '\r');
			
			// clear flag to avoid resending same data
			buttonPressed = false;
		}
	}
}
