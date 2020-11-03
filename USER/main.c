#include "stm32f10x.h"
#include "ht1632c.h"
#include "delay.h"
//���ߵ�С��ͼ��1
//һ��ҳ����Ҫ48���ֽ�����
unsigned char page1[48]={
0X00,0X00,0X01,0XC0,0X06,0X30,0X04,0X10,0X08,0X08,0X08,0X08,0X08,0X08,0X04,0X10,
0X06,0X30,0X03,0XE0,0X00,0X80,0X00,0X80,0X03,0XC0,0X0C,0XB0,0X10,0X88,0X00,0X84,
0X01,0XC0,0X01,0XC0,0X03,0X60,0X06,0X30,0X0C,0X18,0X0C,0X0E,0X00,0X00,0X00,0X00};

//���ߵ�С��ͼ��2
//һ��ҳ����Ҫ48���ֽ�����
unsigned char page2[48]={
0X00,0X00,0X01,0XC0,0X06,0X30,0X04,0X10,0X08,0X08,0X08,0X08,0X08,0X08,0X04,0X10,
0X06,0X30,0X03,0XE0,0X00,0X80,0X00,0X80,0X03,0XC0,0X0C,0XB0,0X10,0X88,0X00,0X84,
0X01,0XC0,0X01,0XC0,0X01,0X40,0X01,0X40,0X01,0X40,0X01,0X60,0X00,0X00,0X00,0X00};


//���ߵ�С��·��1���ݣ�ֻ��һ�����ݣ�2���ֽ�
unsigned char road1[2]={0xF3,0xCF};
//���ߵ�С��·��2���ݣ�ֻ��һ�����ݣ�2���ֽ�
unsigned char road2[2]={0xCF,0x3C};
//���ߵ�С��·��3���ݣ�ֻ��һ�����ݣ�2���ֽ�
unsigned char road3[2]={0x3C,0xF3};





 int main(void)
 {	
	unsigned char *p1,*p2;						 //����ָ��page�����ָ��

	delay_init();
	 
	p1=&page1[0];								 //ʹָ��ָ�������ַ
	p2=&page2[0];								 //ʹָ��ָ�������ַ


	HT1632C_Interface_Init();				 //��ʼ��1632�ӿ�
	HT1632C_Init();							 //��ʼ��HT1632
	HT1632C_clr();							 //����
	while(1)
	{
		HT1632C_Update_OnePage(p1);			//��ʾ����1	
		HT1632C_Update_Onerow(24,road1);	//��ʾ·��1
		delay_ms(60);					 	//�ƶ���ʱ
		HT1632C_Update_Onerow(24,road2);	//��ʾ·��2
		delay_ms(50);					 	//�ƶ���ʱ						
		HT1632C_Update_OnePage(p2);			//��ʾ����2	
		delay_ms(50);					 	//�ƶ���ʱ					
		HT1632C_Update_Onerow(24,road3);	//��ʾ·��3
		delay_ms(60);					 	//�ƶ���ʱ
	}		
 }

