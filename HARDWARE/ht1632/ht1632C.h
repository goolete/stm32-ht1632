/*------------------------------------------------------------------------------------
 * ��Ŀ����:

     HT1632C��������v1.0

 * ��������:

     1���ӿڳ�ʼ��
	 2����������
	 3������һ�У����������У�����һ��
	 4����ȡһ�����ݣ���ȡ���������ݣ���ȡһ������

 * ��ע:
     - ʹ��ǰ��Ҫ������Ľӿ����ò�������ͨ�Žӿ�
----------------------------------------------------------------------------------------*/

#ifndef _HT1632C_H_
#define _HT1632C_H_
#include "sys.h"
/*---------------------------�ӿ�����---------------------------------------------------*/

#define DAT_SET GPIO_SetBits(GPIOA,GPIO_Pin_7);	// PA7
#define	LCD_CS_SET  GPIO_SetBits(GPIOA,GPIO_Pin_5);    //Ƭѡ�˿�  		 
#define	LCD_WR_SET	GPIO_SetBits(GPIOA,GPIO_Pin_6);   //д����			
#define	LCD_RD_SET	GPIO_SetBits(GPIOA,GPIO_Pin_4);    //������			
							
#define DAT_CLR GPIO_ResetBits(GPIOA,GPIO_Pin_7);	// PA7							
#define	LCD_CS_CLR  GPIO_ResetBits(GPIOA,GPIO_Pin_5);     //Ƭѡ�˿�  		 
#define	LCD_WR_CLR	GPIO_ResetBits(GPIOA,GPIO_Pin_6);     //д����		
#define	LCD_RD_CLR	GPIO_ResetBits(GPIOA,GPIO_Pin_4);    //������			
/*---------------------------��������---------------------------------------------------*/
	

/*------------------------��������ģʽ��ָ����------------------------------------------*/
#define MOD_READ			0xC0			//������ģʽ
#define MOD_WRITE			0xA0			//д����ģʽ
#define MOD_RMW				0xA0			//���޸�дģʽ
#define MOD_CMD				0x80			//����ģʽ

#define SYS_DIS				0x00			//�ر�ϵͳʱ��
#define SYS_EN				0x01			//��ϵͳʱ��
#define LED_OFF				0x02			//�ر�LED��ʾ
#define LED_ON				0x03			//��LED��ʾ
#define BLINK_OFF			0x08		   	//�ر���˸
#define	BLINK_ON			0X09		   	//����˸
#define	SLAVE_MODE			0X10		   	//��ģʽ
#define	RC_MASTER_MODE		0X18	   		//�ڲ�RCʱ��
#define	EXT_CLK_MASTER_MODE	0X1C   			//�ⲿʱ��
#define COM_OPTION			0X24		   	//16COM��NMOS��©ģʽ 0x2C��16COM��PMOS��©���
#define PWM_DUTY			0XA0			//PWM���ȿ���

/*---------------------------��������---------------------------------------------------*/
void HT1632C_Interface_Init(void);			//ͨ�Žӿڳ�ʼ��
void HT1632C_Init(void);					//HT1632C��ʼ������
void HT1632C_clr(void);						//��������

//��ָ����row��ʼд���������ݣ�cntΪд��������pָ��Ҫ���͵����ݵ�����
void HT1632C_Write_MultiRow(unsigned char row,unsigned char *p,unsigned char cnt);
//���µ�row�е�һ�����ݣ�pָ��Ҫ���͵����ݵ�����
void HT1632C_Update_Onerow(unsigned char row,unsigned char *p);
//����һ�������ݣ�pָ��Ҫ���͵����ݵ�����
void HT1632C_Update_OnePage(unsigned char *p);
#endif

