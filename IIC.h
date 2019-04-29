
#include"msp430.h"


#define u8 unsigned char

//IO·½ÏòÉèÖÃ
#define SDA_IN()  (P1DIR &= ~ BIT6)
#define SDA_OUT() (P1DIR |= BIT6)

//IO²Ù×÷º¯Êý
//#define IIC_SCL    PBout(8)       //SCL
//#define IIC_SDA    PBout(9)       //SDA
//#define READ_SDA   PBin(9)        //ÊäÈëSDA

#define IIC_SCL_SET (P1OUT |= BIT7)      // P1.7为SCL
#define IIC_SCL_CLR (P1OUT &= ~BIT7)
#define IIC_SDA_SET (P1OUT |= BIT6)     //p1.6为SDA
#define IIC_SDA_CLR (P1OUT &= ~BIT6)
#define READ_SDA   (P1IN & BIT6) >> 6

//#define IIC_SCL_SET GPIO_SetBits(GPIOB,GPIO_Pin_10)
//#define IIC_SCL_CLR GPIO_ResetBits(GPIOB,GPIO_Pin_10)
//#define IIC_SDA_SET GPIO_SetBits(GPIOB,GPIO_Pin_11)
//#define IIC_SDA_CLR GPIO_ResetBits(GPIOB,GPIO_Pin_11)

//IICËùÓÐ²Ù×÷º¯Êý
void IIC_Init(void);                //³õÊ¼»¯IICµÄIO¿Ú
void IIC_Start(void);               //·¢ËÍIIC¿ªÊ¼ÐÅºÅ
void IIC_Stop(void);                //·¢ËÍIICÍ£Ö¹ÐÅºÅ
void IIC_Send_Byte(u8 txd);         //IIC·¢ËÍÒ»¸ö×Ö½Ú
u8 IIC_Read_Byte(unsigned char ack);//IIC¶ÁÈ¡Ò»¸ö×Ö½Ú
u8 IIC_Wait_Ack(void);              //IICµÈ´ýACKÐÅºÅ
void IIC_Ack(void);                 //IIC·¢ËÍACKÐÅºÅ
void IIC_NAck(void);                //IIC²»·¢ËÍACKÐÅºÅ

