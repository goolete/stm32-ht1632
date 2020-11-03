/*------------------------------------------------------------------------------------
 * ��Ŀ����:

     HT1632C��������v1.0

 * ��������:

     1���ӿڳ�ʼ��
	 2����������
	 3������һ�У����������У�����һ��
	 4����ȡһ�����ݣ���ȡ���������ݣ���ȡһ������

 * ��ע:
     - ʹ��ǰ��Ҫ��HT1632C.h�ļ�����ͨ�Žӿڡ����������ͳ�ʼ������
	 - ȡģ�������ֽ�Ϊ��λ�����Ҵ��ϵ��°���ȡģ
-------------------------------------------------------------------------------------*/

/************************����ͷ�ļ�***************************************************/

#include "ht1632c.h"


/*************************************************************************************
*��������void HT1632C_Interface_Init(void)
*��  �ܣ���ʼ��HT1632C�ӿ� 
*˵  ����
**************************************************************************************/
void HT1632C_Interface_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //ʹ��PA,PD�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_6|GPIO_Pin_5|GPIO_Pin_4;				
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
 GPIO_Init(GPIOA, &GPIO_InitStructure);					
}
/*************************************************************************************
*��������void HT1632C_Writer(unsigned char Data,unsigned char cnt)
*��  �ܣ�HT1632C�������ݺ�������λ��ǰ������λ��������
*˵  ����
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
*��������void HT1632C_Writer_CMD(unsigned char cmd)	
*��  �ܣ�HT1632C���������
*˵  ����
**************************************************************************************/
void HT1632C_Writer_CMD(unsigned char cmd)				
{
	LCD_CS_CLR;											  
	HT1632C_Writer(MOD_CMD,3);			//����ģʽ���룬ֻ����ǰ��λ100
	HT1632C_Writer(cmd,9);				//�������ݣ���9λΪ0
	LCD_CS_SET;
}
/*************************************************************************************
*��������void HT1632C_Update_Onerow(unsigned char col,unsigned char row,unsigned char c)		
*��  �ܣ�����ָ��һ��
*˵  ����row���ڼ��У�1-24��*p������Ҫ���͵����ݵĵ�ַ
**************************************************************************************/
void HT1632C_Update_Onerow(unsigned char row,unsigned char *p)	
{
	row=(row-1)<<2;							//����ʵ�ʵ�ַ

	LCD_CS_CLR;
	HT1632C_Writer(MOD_WRITE,3);
	HT1632C_Writer(row<<1,7);
	HT1632C_Writer(*p,8);
	HT1632C_Writer(*(p+1),8);
	LCD_CS_SET;
} 
/*************************************************************************************
*��������void HT1632C_Write_MultiRow(unsigned char row,unsigned char *p,unsigned char cnt)
*��  �ܣ���ָ����row��ʼд���������ݣ�cntΪд������
*˵  ����
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
*��������void HT1632C_Update_OnePage(unsigned char *p)
*��  �ܣ�����һ�������ݣ�һ����Ҫ48���ֽڵ����ݣ�
*˵  ����*p����Ҫ���͵���������ĵ�ַ
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
*��������void HT1632C_clr(void)	
*��  �ܣ���������
*˵  ����
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
*��������void HT1632C_clr(void)	
*��  �ܣ�HT1632C��ʼ������
*˵  ����
**************************************************************************************/
void HT1632C_Init(void)		//HT1632C��ʼ������
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
