#include <stdint.h>
#include <stdbool.h>
#include "inc\tm4c123gh6pm.h"
#include "driverlib\sysctl.h"


//////////////////////
// CREATE THE BIT MASK
//////////////////////

#define LED_MASK = 0x04;  // Set LED to PF2

void PortFunctionInit(void) {
	// dummy variable
	volatile uint32_t ui32Loop;   
	
	////////////////////////
	// ENABLE THE PORT CLOCK
	////////////////////////
	//
	// Do a dummy read to insert a few cycles after enabling the peripheral.
	//
	ui32Loop = SYSCTL_RCGC2_R;

	/////////////////////////////////////////////
	// ENABLE THE LED'S PIN FOR DIGITAL FUNCTIONS
	/////////////////////////////////////////////
		SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF;
		GPIO_PORTF_LOCK_R = 0x4C4F434B;   		// 2) unlock GPIO Port F
		GPIO_PORTF_CR_R |= 0x80;           			// allow changes to PF2
		// only PD7 needs to be unlocked, other bits can't be locked
		GPIO_PORTF_AMSEL_R |= 0x00;        		// 3) disable analog on PF2
		GPIO_PORTF_PCTL_R |= 0x00000000;   		// 4) PCTL GPIO on PF
		GPIO_PORTF_DIR_R |= 0x04;          
		GPIO_PORTF_AFSEL_R |= 0x00;        			// 6) disable alt funct on PF2
		GPIO_PORTF_PUR_R |= 0x04;          			// enable pull-up on PF
		GPIO_PORTF_DEN_R |= 0x04;          			// 7) enable digital I/O on PF2

}


int main(void) {
	
	//initialize the GPIO port
	PortFunctionInit();
	
	//////////////////////
	// YOUR CODE GOES HERE
	//////////////////////
	GPIO_PORTF_DATA_R  |= 0x04;
	while (1) {
        GPIO_PORTF_DATA_R ^= 0x04; // Toggle the LED, Blue Light should blinking
        SysCtlDelay(2000000);
	}
}
