
#include <msp430.h>
#include "bsp_cc1101.h"
#include "MP4725.h"
#include "MAX30100.h"
#include "IIC.h"
#include "msp430fr6989_lanchpad1.h"
#define NUM 4

void sampling()
{
    adc_init();// Enable ADC conv complete interrupt
    uart_init();
    while (!(ADC12IFGR0 & BIT0));
    P8DIR |= BIT4;
    P8OUT |= BIT4;
    __delay_cycles(400);//延时1ms
    P8OUT &= ~BIT4;//拉低P8.4
    MCP4725_WriteData_Digital(ADC12MEM0);
    my_itoa_ascii(ADC12MEM0, string);
    uart_send_once(string);
    SPI_Init();
    CC1101_Reset();
    CC1101_Init();
    Write_CMD(SFTX);
    CC1101_RFDataPack_Send(string, sizeof(string));

    ADC12CTL0 =0x00;


}

//
/*
 *1.定时器确定工作时间
 *2.将其存入铁电存储区
 *3.按照该时间确定采样次数
 *4.循环采样
 * */





int main(void)
{

    WDTCTL = WDTPW | WDTHOLD;  // Stop WDT
      // _MCU_LPM_Set_(_PMM1X_IO_Start);        // Low Power Set -- all port set to GND output(LEDL on)
      /* unsigned char n;
       //__delay_cycles(250000);
     //  for(n=0;n<NUM;n++)
       sampling();
       led_on();
       _PMM1X_IO_End();*/
    PM5CTL0 &= ~LOCKLPM5;
    IIC_Init();
    while(1){
      MCP4725_WriteData_Digital(2045);
       led_on();
       __delay_cycles(8000);
   }




}




void realWork()
{
    WDTCTL = WDTPW | WDTHOLD;  // Stop WDT
   _MCU_LPM_Set_(_PMM1X_IO_Start);        // Low Power Set -- all port set to GND output(LEDL on)
   PM5CTL0 &= ~LOCKLPM5;
   unsigned char n;
   //__delay_cycles(250000);
 //  for(n=0;n<NUM;n++)
   sampling();
   led_on();
   _PMM1X_IO_End();
}

