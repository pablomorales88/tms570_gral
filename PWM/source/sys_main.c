/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Include Files */

#include "sys_common.h"

/* USER CODE BEGIN (1) */
#include <string.h>
#include "gio.h"
#include "het.h"
#include "sci.h"
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
#define UARTSCI sciREG
hetSIGNAL_t signal;
/* USER CODE END */

void main(void)
{
/* USER CODE BEGIN (3) */
	// Init GIO
    gioInit();
	// Initialize HET
	hetInit();
	//
	sciInit();
	sciSetBaudrate(UARTSCI,9600);
	int delay=0;
	uint32 j=0;
	signal.period = 20000; // long int, in us 20000
	// Run forever
	while (1){
	 for (j=0;j<100;j++){
	  // Configure PWM
	  // Set Servo position to neutral
	  signal.duty = j;
	  pwmSetSignal(hetRAM1, pwm0, signal); // J2, Pin 9
	  pwmSetSignal(hetRAM1, pwm1, signal); // J4, Pin 5
	  pwmSetSignal(hetRAM1, pwm2, signal); // J5, Pin 2
	  pwmSetSignal(hetRAM1, pwm3, signal); // J2, Pin 10
	  for(delay=0;delay<1000000;delay++);
	 }
	 for (j=100;j>0;j--){
	   // Configure PWM
	   // Set Servo position to neutral
	   signal.duty = j;
	   pwmSetSignal(hetRAM1, pwm0, signal);
	   pwmSetSignal(hetRAM1, pwm1, signal);
	   pwmSetSignal(hetRAM1, pwm2, signal);
	   pwmSetSignal(hetRAM1, pwm3, signal);
	   for(delay=0;delay<1000000;delay++);
	 }
	 //
	 gioToggleBit(gioPORTB,1);
	 gioToggleBit(gioPORTB,2);
	/* if (sciIsTxReady(UARTSCI)!=0){ // ==0 is Full
	   sciSendByte(UARTSCI,signal.duty);
	 }// end if*/
	 for(delay=0;delay<1000000;delay++);
	}

/* USER CODE END */
}

/* USER CODE BEGIN (4) */
/* USER CODE END */
