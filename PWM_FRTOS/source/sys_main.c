/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Include Files */

#include "sys_common.h"

/* USER CODE BEGIN (1) */
#include "FreeRTOS.h"
#include "os_task.h"
#include "gio.h"
#include "het.h"

/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
// Define Task Handles
xTaskHandle xTask1Handle1;
xTaskHandle xTask1Handle2;
xTaskHandle xTask1Handle3;
xTaskHandle xTask1Handle4;
//
void vTask1(void *pvParameters);
void vTask2(void *pvParameters);
void vTask3(void *pvParameters);
void vTask4(void *pvParameters);
/* USER CODE END */

void main(void)
{
	// Init GIO
	gioInit();
	// Initialize HET
	hetInit();


/* USER CODE BEGIN (3) */
	// Create Task 1
	    if (xTaskCreate(vTask1,"Task1", configMINIMAL_STACK_SIZE, NULL, 1, &xTask1Handle1) != pdTRUE){
	      // Task could not be created
	       while(1);
	    }
	    // Create Task 2
	    if (xTaskCreate(vTask2,"Task2", configMINIMAL_STACK_SIZE, NULL, 1, &xTask1Handle2) != pdTRUE){
	      // Task could not be created
	      while(1);
	    }
	    // Create Task 3
	    if (xTaskCreate(vTask3,"Task3", configMINIMAL_STACK_SIZE, NULL, 1, &xTask1Handle3) != pdTRUE){
	       // Task could not be created
	       while(1);
	    }
	    // Create Task 4
	    if (xTaskCreate(vTask4,"Task4", configMINIMAL_STACK_SIZE, NULL, 1, &xTask1Handle4) != pdTRUE){
	     // Task could not be created
	      while(1);
	    }
	    // Start Scheduler
	    vTaskStartScheduler();
	    // Run forever
	    while(1);
/* USER CODE END */
}

/* USER CODE BEGIN (4) */
// Task1
void vTask1(void *pvParameters){
  //
  hetSIGNAL_t signal;
  signal.period = 20000; // long int, in us 20000
  uint32 j=0;
  for(;;){
   //
   for (j=0;j<100;j++){
	// Configure PWM
	// Set Servo position to neutral
	signal.duty = j;
	pwmSetSignal(hetRAM1, pwm0, signal); // J2, Pin 9
	vTaskDelay(10);
   }
   for (j=100;j>0;j--){
	// Configure PWM
	// Set Servo position to neutral
	signal.duty = j;
	pwmSetSignal(hetRAM1, pwm0, signal); // J2, Pin 9
	vTaskDelay(10);
   }
   //
   //gioToggleBit(gioPORTB,1);
   vTaskDelay(100);
  }
}

// Task2
void vTask2(void *pvParameters){
  //
  hetSIGNAL_t signal;
  signal.period = 20000; // long int, in us 20000
  uint32 j=0;
  for(;;){
   //
   for (j=0;j<100;j++){
	// Configure PWM
	// Set Servo position to neutral
	signal.duty = j;
	pwmSetSignal(hetRAM1, pwm1, signal); // J4, Pin 5
	vTaskDelay(20);
   }
   for (j=100;j>0;j--){
	// Configure PWM
	// Set Servo position to neutral
	signal.duty = j;
	pwmSetSignal(hetRAM1, pwm1, signal); // J4, Pin 5
	vTaskDelay(20);
   }
   //
   vTaskDelay(200);
  }
}

// Task3
void vTask3(void *pvParameters){
  //
  hetSIGNAL_t signal;
  signal.period = 20000; // long int, in us 20000
  uint32 j=0;
  for(;;){
   //
   for (j=0;j<100;j++){
	// Configure PWM
	// Set Servo position to neutral
	signal.duty = j;
	pwmSetSignal(hetRAM1, pwm2, signal); // J5, Pin 2
	vTaskDelay(30);
   }
   for (j=100;j>0;j--){
	// Configure PWM
	// Set Servo position to neutral
	signal.duty = j;
	pwmSetSignal(hetRAM1, pwm2, signal); // J5, Pin 2
	vTaskDelay(30);
   }
   //
   vTaskDelay(300);
  }
}

// Task4
void vTask4(void *pvParameters){
  //
  hetSIGNAL_t signal;
  signal.period = 20000; // long int, in us 20000
  uint32 j=0;
  for(;;){
   //
   for (j=0;j<100;j++){
	// Configure PWM
	// Set Servo position to neutral
	signal.duty = j;
	pwmSetSignal(hetRAM1, pwm3, signal); // J2, Pin 10
	vTaskDelay(40);
   }
   for (j=100;j>0;j--){
	// Configure PWM
	// Set Servo position to neutral
	signal.duty = j;
	pwmSetSignal(hetRAM1, pwm3, signal); // J2, Pin 10
	vTaskDelay(40);
   }
   //
   vTaskDelay(400);
  }
}
/* USER CODE END */
