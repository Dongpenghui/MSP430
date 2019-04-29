/*-------------------------------------------------------------------------------
ÎÄ¼þÃû³Æ£ºmyiic.c
ÎÄ¼þÃèÊö£ºÄ£ÄâIICÊ±Ðò¿ØÖÆ£¬
Ó²¼þÆ½Ì¨£ºÄáÄªM3S¿ª·¢°å
±àÐ´ÕûÀí£ºshifang
¹Ì¼þ¿â  £ºV3.5
¼¼ÊõÂÛÌ³£ºwww.doflye.net
±¸    ×¢£ºÍ¨¹ý¼òµ¥ÐÞ¸Ä¿ÉÒÔÒÆÖ²µ½ÆäËû¿ª·¢°å£¬²¿·Ö×ÊÁÏÀ´Ô´ÓÚÍøÂç¡£
---------------------------------------------------------------------------------*/
#include "IIC.h"




void IIC_Init(void)
{
    P1DIR |= BIT7|BIT6;                          // Clear P1.0 output latch for a defined power-on state
    P1OUT |= BIT7|BIT6;
}
//²úÉúIICÆðÊ¼ÐÅºÅ
void IIC_Start(void)
{
    SDA_OUT();     //sdaÏßÊä³ö
    IIC_SDA_SET;
    IIC_SCL_SET;
    __delay_cycles(4);
    IIC_SDA_CLR;//START:when CLK is high,DATA change form high to low
    __delay_cycles(4);
    IIC_SCL_CLR;//Ç¯×¡I2C×ÜÏß£¬×¼±¸·¢ËÍ»ò½ÓÊÕÊý¾Ý
}
//²úÉúIICÍ£Ö¹ÐÅºÅ
void IIC_Stop(void)
{
    SDA_OUT();//sdaÏßÊä³ö
    IIC_SCL_CLR;
    IIC_SDA_CLR;//STOP:when CLK is high DATA change form low to high
    __delay_cycles(4);
    IIC_SCL_SET;
    IIC_SDA_SET;//·¢ËÍI2C×ÜÏß½áÊøÐÅºÅ
    __delay_cycles(4);
}
//µÈ´ýÓ¦´ðÐÅºÅµ½À´
//·µ»ØÖµ£º1£¬½ÓÊÕÓ¦´ðÊ§°Ü
//        0£¬½ÓÊÕÓ¦´ð³É¹¦
u8 IIC_Wait_Ack(void)
{
    u8 ucErrTime=0;
    SDA_IN();      //SDAÉèÖÃÎªÊäÈë
    IIC_SDA_SET;__delay_cycles(1);
    IIC_SCL_SET;__delay_cycles(1);
    while(READ_SDA)
    {
        ucErrTime++;
        if(ucErrTime>250)
        {
            IIC_Stop();
            return 1;
        }
    }
    IIC_SCL_CLR;//Ê±ÖÓÊä³ö0
    return 0;
}
//²úÉúACKÓ¦´ð
void IIC_Ack(void)
{
    IIC_SCL_CLR;
    SDA_OUT();
    IIC_SDA_CLR;
    __delay_cycles(2);
    IIC_SCL_SET;
    __delay_cycles(2);
    IIC_SCL_CLR;
}
//²»²úÉúACKÓ¦´ð
void IIC_NAck(void)
{
    IIC_SCL_CLR;
    SDA_OUT();
    IIC_SDA_SET;
    __delay_cycles(2);
    IIC_SCL_SET;
    __delay_cycles(2);
    IIC_SCL_CLR;
}
//IIC·¢ËÍÒ»¸ö×Ö½Ú
//·µ»Ø´Ó»úÓÐÎÞÓ¦´ð
//1£¬ÓÐÓ¦´ð
//0£¬ÎÞÓ¦´ð
void IIC_Send_Byte(u8 txd)
{
    u8 t;
    SDA_OUT();
    IIC_SCL_CLR;//À­µÍÊ±ÖÓ¿ªÊ¼Êý¾Ý´«Êä
    for(t=0;t<8;t++)
    {
        //IIC_SDA=(txd&0x80)>>7;
        if((txd&0x80)>>7)
            IIC_SDA_SET;
        else
            IIC_SDA_CLR;
        txd<<=1;
        __delay_cycles(2);   //¶ÔTEA5767ÕâÈý¸öÑÓÊ±¶¼ÊÇ±ØÐëµÄ
        IIC_SCL_SET;
        __delay_cycles(2);
        IIC_SCL_CLR;
        __delay_cycles(2);
    }
}
//¶Á1¸ö×Ö½Ú£¬ack=1Ê±£¬·¢ËÍACK£¬ack=0£¬·¢ËÍnACK
u8 IIC_Read_Byte(unsigned char ack)
{
    unsigned char i,receive=0;
    SDA_IN();//SDAÉèÖÃÎªÊäÈë
    for(i=0;i<8;i++ )
    {
        IIC_SCL_CLR;
        __delay_cycles(2);
        IIC_SCL_SET;
        receive<<=1;
        if(READ_SDA)receive++;
        __delay_cycles(1);
    }
    if (!ack)
        IIC_NAck();//·¢ËÍnACK
    else
        IIC_Ack(); //·¢ËÍACK
    return receive;
}



























