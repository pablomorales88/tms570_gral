/** @file sys_main.c 
*   @brief Application main file
*   @date 02-Mar-2016
*   @version 04.05.02
*
*   This file contains an empty main function,
*   which can be used for the application.
*/

/* 
* Copyright (C) 2009-2016 Texas Instruments Incorporated - www.ti.com 
* 
* 
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
*
*    Redistributions of source code must retain the above copyright 
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the 
*    documentation and/or other materials provided with the   
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


/* USER CODE BEGIN (0) */
/*   This file contains an example of SPI1 and SPI3 Master / Slave configurations.
 * at 8MHz
*
*   PIN Connections must be as Below
*     ---------------         ---------------
*     SPI1 ( Master ) TMS570         SPI1 ( SLave)
*     ---------------         ---------------
*     SIM0             --->    SIMO
*     S0MI             <---    SOMI
*     CLK              --->    CLK
*     CS1              --->    CS1
*
*   PIN Connections must be as Below
*     ---------------         ---------------
*     SPI3 ( Master ) TMS570         SPI3 ( SLave)
*     ---------------         ---------------
*     SIM0             --->    SIMO
*     S0MI             <---    SOMI
*     CLK              --->    CLK
*     CS5              --->    CS5
*
*     SPI1 Pintout lauchpad:
*     ** SIM0:J9, 6
*     ** S0MI:J9, 7
*     ** CS1:J9, 8
*     ** CLK:J6, 7
*     ** ENA:J8, 4 --> disable
*
*     SPI3 Pintout lauchpad:
*     ** SIM0:J5, 6
*     ** S0MI:J5, 7
*     ** CS5:J6, 8
*     ** CLK:J2, 7
*     ** ENA:J6, 8 --> disable
*/
/* USER CODE END */

/* Include Files */

#include "sys_common.h"
#include "system.h"

/* USER CODE BEGIN (1) */
#include <string.h>
#include "gio.h"
#include "spi.h"
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
#define DELAY_VALUE 10000 // 1 milis
#define UARTLIN scilinREG
#define UARTSCI sciREG
#define L 198
//
uint16 TX_Data_Master[L];/* = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A,
		                      0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10,
							  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A,
							  0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10};*/
uint16 RX_Data_Master[L] = { 0 };

uint16 TX_Data_Master1[L];/* = {0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x20,
		                      0x21, 0x22, 0x23, 0x24, 0x25, 0x26,
							  0x27, 0x28, 0x29, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36,
							  0x37, 0x38, 0x39, 0x40, 0x41, 0x42};*/
uint16 RX_Data_Master1[L] = { 0 };
//uint16 FirstData[1] = { 0xFF };
/* USER CODE END */

void main(void)
{
/* USER CODE BEGIN (3) */
	    int i;
	    //
	    spiDAT1_t spi_config = (spiDAT1_t) { (boolean) 0, (boolean) 0, SPI_FMT_0, (uint8_t) SPI_CS_1 };
	    spiDAT1_t spi_config1 = (spiDAT1_t) { (boolean) 0, (boolean) 0, SPI_FMT_0, (uint8_t) SPI_CS_5 };
		 // Init GIO
		 gioInit();
		 // initialize sci/sci-lin
		 // even parity , 2 stop bits
		 sciInit();
		 sciSetBaudrate(UARTSCI,115200);
		 sciSetBaudrate(scilinREG,115200);
        //
		spiInit();
        //
		for(i=0;i<L;i++){
		 TX_Data_Master[i]=(uint8)i;
		 TX_Data_Master1[i]=(uint8)(L-i);
	    }//end for

		while(1){
		 memset(RX_Data_Master,0x00,L);
		 memset(RX_Data_Master1,0x00,L);
		//
		//spiTransmitData(spiREG1, &spi_config, 1, FirstData);
		spiTransmitData(spiREG1, &spi_config, L, TX_Data_Master);
		spiTransmitData(spiREG3, &spi_config1, L, TX_Data_Master1);
		//
		spiReceiveData(spiREG1, &spi_config, L, RX_Data_Master);
		spiReceiveData(spiREG3, &spi_config1, L, RX_Data_Master1);
        //
		if ((sciIsTxReady(UARTSCI)!=0)&&(sciIsTxReady(scilinREG)!=0)){ // ==0 is Full
		  for(i=0;i<L;i++){
		   sciSendByte(UARTSCI,(uint8)RX_Data_Master[i]);
		   sciSendByte(scilinREG,(uint8)RX_Data_Master1[i]);
		  }//end for
		}
		 gioToggleBit(gioPORTB,1);
		 gioToggleBit(gioPORTB,2);
		 //for (i=0;i<DELAY_VALUE;i++){};
		}

/* USER CODE END */
}

/* USER CODE BEGIN (4) */
/* USER CODE END */
