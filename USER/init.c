#include "init.h"

void WarriorRobot_init()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��GPIODʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//ʹ��GPIODʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//ʹ��GPIODʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//ʹ��GPIODʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//ʹ��GPIODʱ��
	
	delay_init(168);		//��ʱ��ʼ�� 
	uart_init(1,1000000);	//���ڳ�ʼ��������Ϊ115200 
//	uart_init(2,9600);	//���ڳ�ʼ��������Ϊ115200
//	uart_init(3,9600);	//���ڳ�ʼ��������Ϊ115200    ����ָ����ӿ�

	BEEP_Init();			//��������ʼ��
	KEY_Init();				//������ʼ��
	InitLCD();        //Һ����ʼ��
	PWM_Init();       //pwm,����������ʼ��

	TIM2_Int_Init(1000-1,84-1);	//��ʱ��ʱ��84M����Ƶϵ��84000������84M/84=1M�ļ���Ƶ�ʣ�����1000��Ϊ1ms
	start_time(); //������ʱ��	
	TIM5_Int_Init(1000-1,84-1);
	start_time_1();	
	IIC_Init();                //��ʼ��IIC��IO��
	delay_ms(100);
//	AT24CXX_Init();			 //��ʼ��IIC
	LED_Init();		  		//LED��ʼ��	
	SENSOR_Init();			//ģ�⡢���ִ�������ʼ��	
//	COMPASS_NST_Init();
	
//	while(menu_run) MarineRobot_menu();      //���Ҫִ��Һ���˵���ȥ��ע�ͼ���
}





