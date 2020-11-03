#include "stm32f10x.h"
#include "ht1632c.h"
#include "delay.h"
//行走的小人图像1
//一个页面需要48个字节数据
unsigned char page1[48]={
0X00,0X00,0X01,0XC0,0X06,0X30,0X04,0X10,0X08,0X08,0X08,0X08,0X08,0X08,0X04,0X10,
0X06,0X30,0X03,0XE0,0X00,0X80,0X00,0X80,0X03,0XC0,0X0C,0XB0,0X10,0X88,0X00,0X84,
0X01,0XC0,0X01,0XC0,0X03,0X60,0X06,0X30,0X0C,0X18,0X0C,0X0E,0X00,0X00,0X00,0X00};

//行走的小人图像2
//一个页面需要48个字节数据
unsigned char page2[48]={
0X00,0X00,0X01,0XC0,0X06,0X30,0X04,0X10,0X08,0X08,0X08,0X08,0X08,0X08,0X04,0X10,
0X06,0X30,0X03,0XE0,0X00,0X80,0X00,0X80,0X03,0XC0,0X0C,0XB0,0X10,0X88,0X00,0X84,
0X01,0XC0,0X01,0XC0,0X01,0X40,0X01,0X40,0X01,0X40,0X01,0X60,0X00,0X00,0X00,0X00};


//行走的小人路面1数据，只是一行数据，2个字节
unsigned char road1[2]={0xF3,0xCF};
//行走的小人路面2数据，只是一行数据，2个字节
unsigned char road2[2]={0xCF,0x3C};
//行走的小人路面3数据，只是一行数据，2个字节
unsigned char road3[2]={0x3C,0xF3};





 int main(void)
 {	
	unsigned char *p1,*p2;						 //定义指向page数组的指针

	delay_init();
	 
	p1=&page1[0];								 //使指针指向数组地址
	p2=&page2[0];								 //使指针指向数组地址


	HT1632C_Interface_Init();				 //初始化1632接口
	HT1632C_Init();							 //初始化HT1632
	HT1632C_clr();							 //清屏
	while(1)
	{
		HT1632C_Update_OnePage(p1);			//显示人物1	
		HT1632C_Update_Onerow(24,road1);	//显示路面1
		delay_ms(60);					 	//移动延时
		HT1632C_Update_Onerow(24,road2);	//显示路面2
		delay_ms(50);					 	//移动延时						
		HT1632C_Update_OnePage(p2);			//显示人物2	
		delay_ms(50);					 	//移动延时					
		HT1632C_Update_Onerow(24,road3);	//显示路面3
		delay_ms(60);					 	//移动延时
	}		
 }

