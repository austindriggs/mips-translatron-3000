#include <stdint.h>
#include "inc\tm4c123gh6pm.h"

#define RED_LED_MASK 0x02;  // Sets light mask to red
#define SWITCH 0x01;        // Declares switch for switch 2
 

void PortFunctionInit(void) {
	// dummy variable
	volatile uint32_t ui32Loop;
		
		// The steps below enable port F, just like in the toggle script
		SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF;
    ui32Loop = SYSCTL_RCGC2_R; 
    GPIO_PORTF_LOCK_R = 0x4C4F434B; 
    GPIO_PORTF_CR_R |= 0x01;        
    GPIO_PORTF_AMSEL_R = 0x00;
    GPIO_PORTF_PCTL_R = 0x00000000;

    // Set PF1 (LED) as output and PF0 (Switch) as input. We want the ~SWITCH so the light starts off as being off.
    GPIO_PORTF_DIR_R |= RED_LED_MASK;  // PF1 (output)
    GPIO_PORTF_DIR_R &= ~SWITCH; // PF0 (input)

    // This pulls the port to high so when the button is pressed, the light will turn on
    GPIO_PORTF_PUR_R |= SWITCH;

    // Digital functions for the LED light and Switch
    GPIO_PORTF_DEN_R |= RED_LED_MASK;
		GPIO_PORTF_DEN_R |= SWITCH;

}


int main(void) {
	
	//initialize the GPIO ports	
	PortFunctionInit();

		while(1){
			if ((GPIO_PORTF_DATA_R & 0x01) == 0){ // If the button is pressed, the light will turn on 
			GPIO_PORTF_DATA_R |= RED_LED_MASK;
			}
			else {        // else, button is not pressed and light is off
				GPIO_PORTF_DATA_R &= ~RED_LED_MASK;
		}
	}
}
