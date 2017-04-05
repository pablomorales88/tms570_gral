/* 
 A tener en cuenta:

 El Master es el ultimo que se debe poner en linea sobre el bus.
 Para ello, todos los slaves deben ya estar en linea.
 Caso contrario, todos reciben NACK y el bus queda bloqueado.
 Esta configurado a un Baudrate de 400Khz.
 Debe utilizarse una resistencia "Pull-up" de 10K conectada a
 3.3VDC sobre el SDA y SCL, entre el Master y todos los slaves.
 Ver Figura.
*/


/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Include Files */

#include "sys_common.h"

/* USER CODE BEGIN (1) */
#include <string.h>
#include "gio.h"
#include "i2c.h"
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
#define DATA_COUNT 20

#define Master_Address 0x26
#define Slave_Address  0x8

uint8_t TX_Data_Master[DATA_COUNT] = {0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,
		                              0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29};
uint8_t RX_Data_Master[DATA_COUNT] = {0};

/* USER CODE END */

void main(void)
{
/* USER CODE BEGIN (3) */

	int delay=0;

	// I2C Init as per GUI
	//  Mode = Master - Transmitter
	//  baud rate = 100KHz
	//  Bit Count = 8bit

	// Init GIO
	gioInit();
    //
	i2cInit();
    //
	// Configure address of Slave to talk to
	i2cSetSlaveAdd(i2cREG1, Slave_Address);
	//
	while(1){
	 ///////////////////////////////////////////////////////////////
	 //        Master Transfer Functionality                      //
	 ///////////////////////////////////////////////////////////////
	 //
	 memset(RX_Data_Master,0x00,DATA_COUNT);
	 // Set direction to Transmitter
	 // Note: Optional - It is done in Init
	 i2cSetDirection(i2cREG1, I2C_TRANSMITTER);
	 // Configure Data count
	 // Note: Optional - It is done in Init, unless user want to change
	 i2cSetCount(i2cREG1, DATA_COUNT);
	 // Set mode as Master
	 i2cSetMode(i2cREG1, I2C_MASTER);
	 // Set Stop after programmed Count
	 i2cSetStop(i2cREG1);
	 // Transmit Start Condition
	 i2cSetStart(i2cREG1);
	 // Tranmit DATA_COUNT number of data in Polling mode
	 i2cSend(i2cREG1, DATA_COUNT, TX_Data_Master);
     //
	 gioToggleBit(gioPORTB,1);
	 for(delay=0;delay<1000000;delay++);
	 // Wait until Bus Busy is cleared
	 while(i2cIsBusBusy(i2cREG1) == true);
	 // Wait until Stop is detected
	 while(i2cIsStopDetected(i2cREG1) == 0);
	 // Clear the Stop condition
	 i2cClearSCD(i2cREG1);
	 // Simple Dealya before starting Next Block
	 // Depends on how quick the Slave gets ready
	 for(delay=0;delay<1000000;delay++);
	 //////////////////////////////////////////////////////////////
	 //        Master Receive Functionality                      //
	 //////////////////////////////////////////////////////////////
	 // Set direction to receiver
	 i2cSetDirection(i2cREG1, I2C_RECEIVER);
	 // Configure Data count
	 // Note: Optional - It is done in Init, unless user want to change
	 i2cSetCount(i2cREG1, DATA_COUNT);
 	 // Set mode as Master
	 i2cSetMode(i2cREG1, I2C_MASTER);
 	 // Set Stop after programmed Count
	 i2cSetStop(i2cREG1);
	 // Transmit Start Condition
	 i2cSetStart(i2cREG1);
  	 // Tranmit DATA_COUNT number of data in Polling mode
	 i2cReceive(i2cREG1, DATA_COUNT, RX_Data_Master);
     //
	 gioToggleBit(gioPORTB,2);
	 for(delay=0;delay<1000000;delay++);
	 // Wait until Bus Busy is cleared
	 while(i2cIsBusBusy(i2cREG1) == true);
 	 // Wait until Stop is detected
	 while(i2cIsStopDetected(i2cREG1) == 0);
	 // Clear the Stop condition
	 i2cClearSCD(i2cREG1);
	 // Simple Dealya before starting Next Block
	 // Depends on how quick the Slave gets ready
	 for(delay=0;delay<1000000;delay++);
	}//end while
/* USER CODE END */
}

/* USER CODE BEGIN (4) */
/* USER CODE END */
