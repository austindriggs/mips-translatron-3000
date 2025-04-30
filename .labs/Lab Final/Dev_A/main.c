//*****************************************************************************
//
// THIS CODE SHOULD BE UPLOADED TO THE TEMPERATURE SENSING DEVICE A
//
//*****************************************************************************


// header files
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "inc/tm4c123gh6pm.h"
#include "driverlib/uart.h"
#include "driverlib/debug.h"
#include "driverlib/adc.h"


//*****************************************************************************
//
// DEFINE USEFUL VARIABLES
//
//*****************************************************************************

// temperature variables
uint32_t ui32ADC0Value[4];
volatile uint32_t ui32TempAvg;
volatile uint32_t ui32TempValueC;
volatile uint32_t ui32TempValueF;

// flag for main loop to know when to send data
volatile bool motionDetected = false;
 
// character array to store stringified 
// version of count to send over UART
char str[32] = {0};


//*****************************************************************************
//
// UART COMMUNICATION CODE
//
//*****************************************************************************

void PortFunctionInit(void) {
	// Enable Peripheral Clocks 
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

	// Enable pin PF4 and PF2 (LED) for GPIOInput
	GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);

	//First open the lock and select the bits we want to modify in the GPIO commit register.
	HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
	HWREG(GPIO_PORTF_BASE + GPIO_O_CR) = 0x1;

	// Enable pin PF0 for GPIOInput
	GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0);

	//Enable pull-up on PF4 and PF0
	GPIO_PORTF_PUR_R |= 0x11; 
}


void Interrupt_Init(void) {
  IntEnable(INT_GPIOF); // enable interrupt 30 in NVIC (GPIOF)
	IntPrioritySet(INT_GPIOF, 0x00); // configure GPIOF interrupt priority as 0

	// init GPIO F interrupts
	// SW1 and SW2 falling edge sentitive 
	GPIO_PORTF_IM_R |= 0x11;   		// arm interrupt on PF0 and PF4
	GPIO_PORTF_IS_R &= ~0x11;     // PF0 and PF4 are edge-sensitive
  GPIO_PORTF_IBE_R &= ~0x11;   	// PF0 and PF4 not both edges trigger 
  GPIO_PORTF_IEV_R &= ~0x11;  	// PF0 and PF4 falling edge event
}

void uart_Init(void) {
	// start peripheral clocks
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

	// configure external pins
	GPIOPinConfigure(GPIO_PB1_U1TX);
	
	// mux pins to UART peripheral
	GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_1);

	// configure UART system and packets
	UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(), 115200,
        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
}


//interrupt handler for SW1 is pressed
void GPIOPortF_Handler(void) {
	
	// switch 1
	if(GPIO_PORTF_RIS_R & 0x10) {
		// useful code
		GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_4); // acknowledge flag for PF4
		motionDetected = true; // motion detected
		
		// code for debugging
		//UARTCharPut(UART1_BASE, 'X');  // if UART works, you’ll see an 'X' when button is pressed
		//GPIO_PORTF_DATA_R ^= GPIO_PIN_2;
		//SysCtlDelay(SysCtlClockGet() / 3); // adjust as needed
		//GPIO_PORTF_DATA_R ^= GPIO_PIN_2;
	}
	
}

//*****************************************************************************
//
// ADC TEMPERATURE CODE
//
//*****************************************************************************


//ADC0 initialization
void ADC0_Init(void) {
	// enable port E
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE); // Enable clock for GPIO Port E
	SysCtlDelay(2); // Delay for clock stabilization
	GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_3); // Enable PE3 for ADC input

	
	SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);	//activate the clock of ADC0
	SysCtlDelay(2);	//insert a few cycles after enabling the peripheral to allow the clock to be fully activated.

	ADCSequenceDisable(ADC0_BASE, 1); //disable ADC0 before the configuration is complete
	ADCSequenceConfigure(ADC0_BASE, 1, ADC_TRIGGER_PROCESSOR, 0); // will use ADC0, SS1, processor-trigger, priority 0
	
	ADCSequenceStepConfigure(ADC0_BASE, 1, 0, ADC_CTL_CH0); // AIN0 = PE3
	ADCSequenceStepConfigure(ADC0_BASE, 1, 1, ADC_CTL_CH0);
	ADCSequenceStepConfigure(ADC0_BASE, 1, 2, ADC_CTL_CH0);
	ADCSequenceStepConfigure(ADC0_BASE, 1, 3, ADC_CTL_CH0 | ADC_CTL_IE | ADC_CTL_END);

	IntPrioritySet(INT_ADC0SS1, 0x00);  	 	// configure ADC0 SS1 interrupt priority as 0
	IntEnable(INT_ADC0SS1);    							// enable interrupt 31 in NVIC (ADC0 SS1)
	ADCIntEnableEx(ADC0_BASE, ADC_INT_SS1); // arm interrupt of ADC0 SS1

	ADCSequenceEnable(ADC0_BASE, 1); //enable ADC0
}
		
//interrupt handler
void ADC0_Handler(void) {
	// trigger and capture data
	ADCIntClear(ADC0_BASE, 1); //clear interrupt flag of ADC0 SS1
	ADCProcessorTrigger(ADC0_BASE, 1); //Software trigger the next ADC sampling
	ADCSequenceDataGet(ADC0_BASE, 1, ui32ADC0Value); //Load the captured data from FIFO
	
	
	// read temperature
	ui32TempAvg = (ui32ADC0Value[0] + ui32ADC0Value[1] + ui32ADC0Value[2] + ui32ADC0Value[3]) / 4.0;
	ui32TempValueC = (uint32_t)(ui32TempAvg + 0.5);
	ui32TempValueF = (uint32_t)((ui32TempAvg * 9.0 / 5.0) + 32.0);
	motionDetected = true;
}


//*****************************************************************************
//
// MAIN FUNCTION
//
//*****************************************************************************


 int main(void) {
	// set the clock once
	SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
	
	// initialize UART stuff
	PortFunctionInit(); //initialize the GPIO ports	
	uart_Init(); //initialize UART1
	Interrupt_Init(); //configure the GPIOF interrupt
	//IntMasterEnable(); // globally enable interrupt

	// initialize ADC stuff
	//ADC0_Init();
	//IntMasterEnable(); // globally enable interrupt
	//ADCProcessorTrigger(ADC0_BASE, 1);	
	ui32TempValueF = 87;

	// Loop forever.
	bool hello = true;
	while(1) {
		// debug
		if (hello == true) {
			UARTCharPut(UART1_BASE, 'H');
			UARTCharPut(UART1_BASE, 'i');
			UARTCharPut(UART1_BASE, '\n');
			UARTCharPut(UART1_BASE, '\r');
			hello = false;
		}
		
		// if button is pressed, send new value
		if (motionDetected) {			
			// convert count to ASCII characters
			int tempToSend = (int) (ui32TempValueF + 0.5);
			sprintf(str, "Temp: %d",tempToSend); // ui32TempValueF
			
			// send count value
			for(int i = 0; str[i] !=  '\0'; i++) {
				UARTCharPut(UART1_BASE, str[i]);
			}
			UARTCharPut(UART1_BASE, '\r');
			UARTCharPut(UART1_BASE, '\n');
			
			// debug: toggle LED
			GPIO_PORTF_DATA_R ^= GPIO_PIN_2;
			
			// clear flag to avoid resending same data
			motionDetected = false;
		}
		
		// debug: toggle LED
		//GPIO_PORTF_DATA_R ^= GPIO_PIN_2;
		//SysCtlDelay(SysCtlClockGet() / 1000); // adjust as needed
		//GPIO_PORTF_DATA_R ^= GPIO_PIN_2;

	}
}
