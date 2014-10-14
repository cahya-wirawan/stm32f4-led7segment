/*----------------------------------------------------------------------------
 * Name:    Led7Segment.c
 * Purpose: Led7Segment Driver
 * Author: Cahya Wirawan
 *----------------------------------------------------------------------------*/

#include <stdio.h>
#include "STM32F4xx.h"
#include "LED.h"
#include "Keyboard.h"

#include "Led7Segment.h"

volatile uint32_t msTicks;                      /* counts 1ms timeTicks       */

/*----------------------------------------------------------------------------
  SysTick_Handler
 *----------------------------------------------------------------------------*/
void SysTick_Handler(void) {
  msTicks++;
}

/*----------------------------------------------------------------------------
  delays number of tick Systicks (happens every 1 ms)
 *----------------------------------------------------------------------------*/
void Delay (uint32_t dlyTicks) {                                              
  uint32_t curTicks;

  curTicks = msTicks;
  while ((msTicks - curTicks) < dlyTicks);
}


/*----------------------------------------------------------------------------
  Main function
 *----------------------------------------------------------------------------*/
int main (void) {
  int32_t led_num = LED_Num();
  int num = 0; 
  //int32_t dir =  1;
 uint32_t btns = 0;

  SystemCoreClockUpdate();                      /* Get Core Clock Frequency   */
  if (SysTick_Config(SystemCoreClock / 1000)) { /* SysTick 1 msec interrupts  */
    while (1);                                  /* Capture error              */
  }

  Led7Segment_Initialize();
  Keyboard_Initialize();

  while(1) {                                    /* Loop forever               */
    btns = Keyboard_GetKeys();                  /* Read button states         */
		if (btns == (1UL << 0)) {
			num = (num+1)%1000;
		}
		//Led7Segment_PrintNumber(num);
		//Led7Segment_Write(0, (short)num);
		Delay(500);
		//LED_On(num);
		//Led7Segment_Write(0, (short)num);
		Led7Segment_PrintDecNumber(num);
		Delay(500);
		Led7Segment_Out(0);
		num = (num+1)%1000;
  }
}
