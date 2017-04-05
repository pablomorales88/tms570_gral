 /* USER CODE BEGIN (0) */
/* USER CODE END */

/* Include Files */

#include "sys_common.h"
#include "system.h"

/* USER CODE BEGIN (1) */
#include "esm.h"
#include "adc.h"
#include "sci.h"
#include "gio.h"

//#define  TSIZE1 12
//uint8  TEXT1[TSIZE1]= {'\r','\n','|','\t','C','H','.','I','D','=','0','x'};
//#define  TSIZE2 9
//uint8  TEXT2[TSIZE2]= {'\t','V','A','L','U','E','=','0','x'};

adcData_t adc_data[2];
uint16 value[2];

void sciDisplayText(sciBASE_t *sci, uint8 *text, uint32 length);
void sciDisplayData(sciBASE_t *sci, uint8 *text,uint32 length);
void wait(uint32 time);
void AdcInit();
void capturaNormal();
/* USER CODE END */


/** @fn void main(void)
*   @brief Application main function
*
*/

/* USER CODE BEGIN (2) */
/* USER CODE END */

void main(void){
/* USER CODE BEGIN (3) */
   // uint32 ch_count=0;
   // uint32 id    =0;
   // uint32 value =0;

    // initialize gio
    gioInit();

    // initialize sci/sci-lin  : even parity , 2 stop bits
    sciInit();

    // initialize ADC
    AdcInit();

    while(1){

    	capturaNormal();

    	/*
        while((adcIsConversionComplete(adcREG1,adcGROUP1))==0);
        ch_count = adcGetData(adcREG1, adcGROUP1,adc_data);

        //id    = adc_data[0].id;
        value = adc_data[0].value;

        //gioSetBit(gioPORTB, 0, 0);

       //sciDisplayText(scilinREG,&TEXT1[0],TSIZE1);
       //sciDisplayData(scilinREG,(uint8*)&id,4);
        sciDisplayText(scilinREG,&TEXT2[0],TSIZE2);
        sciDisplayData(scilinREG,(uint8*)&value,4);

        //id    = adc_data[1].id;
        //value = adc_data[1].value;

        //sciDisplayText(scilinREG,&TEXT1[0],TSIZE1);
        //sciDisplayData(scilinREG,(uint8*)&id,4);
        //sciDisplayText(scilinREG,&TEXT2[0],TSIZE2);
        //sciDisplayData(scilinREG,(uint8*)&value,4);*/
        //
        gioToggleBit(gioPORTB,2);
        wait(1000*value[0]);
        gioToggleBit(gioPORTB,1);
        wait(1000*value[1]);
        //wait((uint32)i);
    }
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
 uint32 count;
 int i;
 //
 //AdcInit();
 //
 while(!adcIsConversionComplete(adcREG1,1U));
 count=adcGetData(adcREG1, adcGROUP1, adc_data);
 for (i = 0U; i < count; i++){
  value[i]=(uint16)(adc_data[i].value & 0xFFFU);
  sciDisplayText(scilinREG,"CCS:",4);
  sciDisplayData(scilinREG,(uint8*)&value,2);
 }
 sciDisplayText(scilinREG,"\n\r",2);
 return;
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

void sciDisplayText(sciBASE_t *sci, uint8 *text,uint32 length){
    while(length--){
     while ((scilinREG->FLR & 0x4) == 4); // wait until busy
     sciSendByte(scilinREG,*text++);      // send out text
    }
}

void wait(uint32 time){
    while(time){time--;}
}

/* USER CODE END */
