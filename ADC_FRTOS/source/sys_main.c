 /* USER CODE BEGIN (0) */
/* USER CODE END */

/* Include Files */

#include "sys_common.h"
#include "system.h"

/* USER CODE BEGIN (1) */
// Include FreeRTOS scheduler files
#include "FreeRTOS.h"
#include "os_task.h"
#include "esm.h"
#include "adc.h"
#include "sci.h"
#include "gio.h"

//
adcData_t adc_data[4];
uint16 value1,value2,value3,value4;

void sciDisplayText(sciBASE_t *sci, uint8 *text, uint32 length);
void sciDisplayData(sciBASE_t *sci, uint8 *text,uint32 length);
void wait(uint32 time);
void AdcInit();
void capturaNormal();

// Define Task Handles
xTaskHandle xTask1Handle1;
xTaskHandle xTask1Handle2;
xTaskHandle xTask1Handle3;
xTaskHandle xTask1Handle4;
xTaskHandle xTask1Handle5;
//
void vTask1(void *pvParameters);
void vTask2(void *pvParameters);
void vTask3(void *pvParameters);
void vTask4(void *pvParameters);
void vTask5(void *pvParameters);

/* USER CODE END */


/** @fn void main(void)
*   @brief Application main function
*
*/

/* USER CODE BEGIN (2) */
/* USER CODE END */

void main(void){
/* USER CODE BEGIN (3) */

    // initialize gio
    gioInit();

    // initialize sci/sci-lin  : even parity , 2 stop bits
    sciInit();

    // initialize ADC
    AdcInit();

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
    // Create Task 5
    if (xTaskCreate(vTask5,"Task5", configMINIMAL_STACK_SIZE, NULL, 1, &xTask1Handle5) != pdTRUE){
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
//
void AdcInit(){
 adcInit();
 adcREG1->G1DMACR=0x1U;
 adcStartConversion(adcREG1,1U);
 return;
}

//
void capturaNormal(){
 uint32 count=0;
 count=count;
 //
 while(!adcIsConversionComplete(adcREG1,1U));
 count=adcGetData(adcREG1, adcGROUP1, adc_data);
 value1=(uint16)(adc_data[0].value & 0xFFFU);// pin 2 --> J5
 value2=(uint16)(adc_data[1].value & 0xFFFU);// pin 3 --> J5
 value3=(uint16)(adc_data[2].value & 0xFFFU);// pin 19 --> J3
 value4=(uint16)(adc_data[3].value & 0xFFFU);// pin 20 --> J3
 return;
}

// Task1
void vTask1(void *pvParameters){

  for(;;){
     //
     capturaNormal();
  }
}

// Task2
void vTask2(void *pvParameters){

  for(;;){
     //
     gioToggleBit(gioPORTB,1);
     //sciDisplayData(scilinREG,(uint8*)&value1,2);
     vTaskDelay(value3/10);
	 //vTaskDelay(100);
  }
}

// Task3
void vTask3(void *pvParameters){

  for(;;){
     //
     gioToggleBit(gioPORTB,2);
     //sciDisplayData(scilinREG,(uint8*)&value2,2);
     vTaskDelay(value4/10);
     //vTaskDelay(100);
  }
}

// Task4
void vTask4(void *pvParameters){

  for(;;){
	//
	//gioToggleBit(gioPORTB,1);
	//sciDisplayData(scilinREG,(uint8*)&value1,2);
	//vTaskDelay(value1/10);
	vTaskDelay(100);
  }
}

// Task5
void vTask5(void *pvParameters){

  for(;;){
	//
	//gioToggleBit(gioPORTB,2);
	//sciDisplayData(scilinREG,(uint8*)&value2,2);
	//vTaskDelay(value2/10);
	vTaskDelay(100);
  }
}
//
void sciDisplayData(sciBASE_t *sci, uint8 *text,uint32 length){
    uint8 txt = 0;
    uint8 txt1 = 0;

#if ((__little_endian__ == 1) || (__LITTLE_ENDIAN__ == 1))
text = text + (length -1);
#endif

    while(length--){
#if ((__little_endian__ == 1) || (__LITTLE_ENDIAN__ == 1))
        txt = *text--;
#else
        txt = *text++;
#endif

        txt1 = txt;
        txt  &= ~(0xF0);
        txt1 &= ~(0x0F);
        txt1  =txt1>>4;

        if(txt<=0x9){
         txt +=0x30;
        }
        else if(txt > 0x9 && txt < 0xF){
         txt +=0x37;
        }
        else{
         txt = 0x30;
        }

        if(txt1 <= 0x9){
         txt1 +=0x30;
        }
        else if((txt1 > 0x9) && (txt1 <= 0xF)){
         txt1 +=0x37;
        }
        else{
         txt1 = 0x30;
        }

        while ((scilinREG->FLR & 0x4) == 4); // wait until busy
        sciSendByte(scilinREG,txt1);      // send out text
        while ((scilinREG->FLR & 0x4) == 4); // wait until busy
        sciSendByte(scilinREG,txt);      // send out text
    }
}
//
void sciDisplayText(sciBASE_t *sci, uint8 *text,uint32 length){
    while(length--){
     while ((scilinREG->FLR & 0x4) == 4); // wait until busy
     sciSendByte(scilinREG,*text++);      // send out text
    }
}
//
void wait(uint32 time){
    while(time){time--;}
}

/* USER CODE END */
