/*------------------------------------------------------------------------------------
 * 项目名称:

     HT1632C驱动程序v1.0

 * 功能描述:

     1、接口初始化
	 2、清屏函数
	 3、更新一行，更新若干行，更新一屏
	 4、读取一行数据，读取若干行数据，读取一屏数据

 * 备注:
     - 使用前需要在HT1632C.h文件设置通信接口、级联个数和初始化数据
	 - 取模方向，以字节为单位从左到右从上到下按行取模
-------------------------------------------------------------------------------------*/

/************************包含头文件***************************************************/

#include "ht1632c.h"


/*************************************************************************************
*函数名：void HT1632C_Interface_Init(void)
*功  能：初始化HT1632C接口 
*说  明：
**************************************************************************************/
void HT1632C_Interface_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能PA,PD端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_6|GPIO_Pin_5|GPIO_Pin_4;				
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
 GPIO_Init(GPIOA, &GPIO_InitStructure);					
}
/*************************************************************************************
*函数名：void HT1632C_Writer(unsigned char Data,unsigned char cnt)
*功  能：HT1632C发送数据函数，高位在前，发送位数可设置
*说  明：
**************************************************************************************/
void HT1632C_Writer(unsigned char dat,unsigned char cnt)
{
	unsigned char i;
	for(i=0;i<cnt;i++)
	{
		LCD_WR_CLR;
		if(dat&0x80)
			 GPIO_SetBits(GPIOA,GPIO_Pin_7);
		else
			GPIO_ResetBits(GPIOA,GPIO_Pin_7);
		dat<<=1;
		LCD_WR_SET;
	}
}

/*************************************************************************************
*函数名：void HT1632C_Writer_CMD(unsigned char cmd)	
*功  能：HT1632C发送命令函数
*说  明：
**************************************************************************************/
void HT1632C_Writer_CMD(unsigned char cmd)				
{
	LCD_CS_CLR;											  
	HT1632C_Writer(MOD_CMD,3);			//命令模式代码，只发送前三位100
	HT1632C_Writer(cmd,9);				//命令数据，第9位为0
	LCD_CS_SET;
}
/*************************************************************************************
*函数名：void HT1632C_Update_Onerow(unsigned char col,unsigned char row,unsigned char c)		
*功  能：更新指定一行
*说  明：row：第几行，1-24；*p：传递要发送的数据的地址
**************************************************************************************/
void HT1632C_Update_Onerow(unsigned char row,unsigned char *p)	
{
	row=(row-1)<<2;							//计算实际地址

	LCD_CS_CLR;
	HT1632C_Writer(MOD_WRITE,3);
	HT1632C_Writer(row<<1,7);
	HT1632C_Writer(*p,8);
	HT1632C_Writer(*(p+1),8);
	LCD_CS_SET;
} 
/*************************************************************************************
*函数名：void HT1632C_Write_MultiRow(unsigned char row,unsigned char *p,unsigned char cnt)
*功  能：从指定行row开始写入连续数据，cnt为写入行数
*说  明：
**************************************************************************************/
void HT1632C_Write_MultiRow(unsigned char row,unsigned char *p,unsigned char cnt)
{
	unsigned char i,addr;

	addr=(row-1)<<2;
	LCD_CS_CLR;	
	HT1632C_Writer(MOD_WRITE,3);
	HT1632C_Writer(addr<<1,7);
	for(i=0;i<cnt;i++)
		{
			HT1632C_Writer(*p,8);
			p++;
			HT1632C_Writer(*p,8);
			p++;
		}
	LCD_CS_SET;
} 

/*************************************************************************************
*函数名：void HT1632C_Update_OnePage(unsigned char *p)
*功  能：更新一整屏数据（一屏需要48个字节的数据）
*说  明：*p传递要发送的数据数组的地址
**************************************************************************************/
void HT1632C_Update_OnePage(unsigned char *p)
{
	unsigned char i;

	LCD_CS_CLR;	
	HT1632C_Writer(MOD_WRITE,3);
	HT1632C_Writer(0,7);
	for(i=0;i<48;i++)
		{
			HT1632C_Writer(*p,8);
			p++;
		}
	LCD_CS_SET;
} 
/*************************************************************************************
*函数名：void HT1632C_clr(void)	
*功  能：清屏函数
*说  明：
**************************************************************************************/
void HT1632C_clr(void)	
{
	unsigned char i;
	LCD_CS_CLR;
	HT1632C_Writer(MOD_WRITE,3);
	HT1632C_Writer(0x00,7);
	for(i=0;i<48;i++)
	{
		HT1632C_Writer(0x00,8);
	}
	LCD_CS_SET;
} 
/*************************************************************************************
*函数名：void HT1632C_clr(void)	
*功  能：HT1632C初始化函数
*说  明：
**************************************************************************************/
void HT1632C_Init(void)		//HT1632C初始化函数
{
	LCD_CS_SET;
	LCD_WR_SET;
	DAT_SET;
	HT1632C_Writer_CMD(SYS_DIS);
	HT1632C_Writer_CMD(COM_OPTION);
	HT1632C_Writer_CMD(RC_MASTER_MODE);
	HT1632C_Writer_CMD(SYS_EN);
	HT1632C_Writer_CMD(PWM_DUTY);
	HT1632C_Writer_CMD(BLINK_OFF);
	HT1632C_Writer_CMD(LED_ON);
}


/*************************************************************************************/
