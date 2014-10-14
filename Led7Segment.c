/*----------------------------------------------------------------------------
 * Name:    Led7Segment.c
 * Purpose: Led7Segment Driver
 * Author: Cahya Wirawan
 *----------------------------------------------------------------------------*/
 
#include "GPIO_STM32F4xx.h"
#include "Led7Segment.h"


const GPIO_PIN_ID Pin_LED7SEGMENT[] = {
  { GPIOE, 0 },
  { GPIOE, 1 },
  { GPIOE, 2 },
  { GPIOE, 3 },
  { GPIOE, 4 },
  { GPIOE, 5 },
  { GPIOE, 6 },
  { GPIOE, 7 },
  { GPIOE, 12 },
  { GPIOE, 13 },
  { GPIOE, 14 },
  { GPIOE, 15 }
};

#define NUM_LED7SEGMENT (sizeof(Pin_LED7SEGMENT)/sizeof(GPIO_PIN_ID))


/*-----------------------------------------------------------------------------
 * Led7Segment_Initialize:  Initialize LEDs
 *
 * Parameters: (none)
 * Return:     (none)
 *----------------------------------------------------------------------------*/
void Led7Segment_Initialize (void) {
  uint32_t n;

  /* Configure pins: Push-pull Output Mode (50 MHz) with Pull-down resistors */
  for (n = 0; n < NUM_LED7SEGMENT; n++) {
    GPIO_PortClock   (Pin_LED7SEGMENT[n].port, true);
    GPIO_PinWrite    (Pin_LED7SEGMENT[n].port, Pin_LED7SEGMENT[n].num, 0);
    GPIO_PinConfigure(Pin_LED7SEGMENT[n].port, Pin_LED7SEGMENT[n].num,
                      GPIO_MODE_OUTPUT,
                      GPIO_OUTPUT_PUSH_PULL,
                      GPIO_OUTPUT_SPEED_50MHz,
                      GPIO_PULL_DOWN);
  }
}


/*-----------------------------------------------------------------------------
 * Led7Segment_Uninitialize:  Uninitialize LEDs
 *
 * Parameters: (none)
 * Return:     (none)
 *----------------------------------------------------------------------------*/
void Led7Segment_Uninitialize (void) {
  uint32_t n;

  /* Configure pins: Input mode, without Pull-up/down resistors */
  for (n = 0; n < NUM_LED7SEGMENT; n++) {
    GPIO_PinConfigure(Pin_LED7SEGMENT[n].port, Pin_LED7SEGMENT[n].num,
                      GPIO_MODE_INPUT,
                      GPIO_OUTPUT_PUSH_PULL,
                      GPIO_OUTPUT_SPEED_2MHz,
                      GPIO_NO_PULL_UP_DOWN);
  }
}


/*-----------------------------------------------------------------------------
 * Led7Segment_On: Turns on requested LED
 *
 * Parameters:  num - LED number
 * Return:     (none)
 *----------------------------------------------------------------------------*/
void Led7Segment_On (uint32_t num) {
  GPIO_PinWrite(Pin_LED7SEGMENT[num].port, Pin_LED7SEGMENT[num].num, 1);
}

/*-----------------------------------------------------------------------------
 * Led7Segment_Off: Turns off requested LED
 *
 * Parameters:  num - LED number
 * Return:     (none)
 *----------------------------------------------------------------------------*/
void Led7Segment_Off (uint32_t num) {
  GPIO_PinWrite(Pin_LED7SEGMENT[num].port, Pin_LED7SEGMENT[num].num, 0);
}

/*-----------------------------------------------------------------------------
 * Led7Segment_Out: Write value to LEDs
 *
 * Parameters:  val - value to be displayed on LEDs
 * Return:     (none)
 *----------------------------------------------------------------------------*/
void Led7Segment_Out (uint32_t val) {
  uint32_t n;

  for (n = 0; n < NUM_LED7SEGMENT; n++) {
    if (val & (1<<n)) {
      Led7Segment_On (n);
    } else {
      Led7Segment_Off(n);
    }
  }
}

/*-----------------------------------------------------------------------------
 * Led7Segment_Num: Get number of available LEDs
 *
 * Parameters: (none)
 * Return:      number of available LEDs
 *----------------------------------------------------------------------------*/
uint32_t Led7Segment_Num (void) {
  return (NUM_LED7SEGMENT);
}


/*-----------------------------------------------------------------------------
 * Led7Segment_Write: Print a number using available LEDs as binary number
 *
 * Parameters: (short)
 * Return:      none
 *----------------------------------------------------------------------------*/
void Led7Segment_Write (short segment, short num) {
	short i;
	
	for(i=0; i<4; i++)  {
		if((1<<i) & num) {
			Led7Segment_On(segment*4 + i);
		} else {
			Led7Segment_Off(segment*4 + i);
		}
	}
}

/*-----------------------------------------------------------------------------
 * Led7Segment_PrintNumber: Print number to 3 Led7Segment
 *
 * Parameters: (short)
 * Return:      none
 *----------------------------------------------------------------------------*/
void Led7Segment_PrintNumber (int num, short base) {
	short i;
	if(num>=1000)
		return;
	i = num % base;
	Led7Segment_Write(0, i);
	num = (short)(num/base);
	i = num % base;
	Led7Segment_Write(1, i);
	num = (short)(num/base);
	i = num % base;
	Led7Segment_Write(2, i);
}

/*-----------------------------------------------------------------------------
 * Led7Segment_PrintDecNumber: Print Decimal number to 3 Led7Segment
 *
 * Parameters: (short)
 * Return:      none
 *----------------------------------------------------------------------------*/
void Led7Segment_PrintDecNumber (int num) {
	Led7Segment_PrintNumber(num, 10);
}

/*-----------------------------------------------------------------------------
 * Led7Segment_PrintHexNumber: Print Hexadecimal number to 3 Led7Segment
 *
 * Parameters: (short)
 * Return:      none
 *----------------------------------------------------------------------------*/
void Led7Segment_PrintHexNumber (int num) {
	Led7Segment_PrintNumber(num, 16);
}
