/********************************************
* �汾:	TheWarrior_1.1_2022.06
*********************************************/
#include "init.h"
#include "function.h"		//����ҵ����ϸ�ӳ������ϸģ����򶼷���function.hͷ�ļ���main.c�ļ���Ҫд�ܵ�ģ�����
#include "ysy.h"				
#include "edge.h"

#define AI 							analog
#define DI							digital
#define ClearScreen 		clear_screen
#define ShowStr 				display_GB2312_string		//�ַ�������
#define ShowAI					display_GB2312_u16 //��λ����
#define ShowDI					display_GB2312_u1		//һλ����
#define ServoSetMode		UP_CDS_SetMode					
#define ServoSetAngle		UP_CDS_SetAngle	

void RobotInit(void);
void GoodMoto(int lspeed,int rspeed);

u8 Key = 0;
u8 Key_Temp = 0;
extern int Rs,Ls;
int temp,t=0;

int main(void)
{
	//int i,n=0;
	WarriorRobot_init();
	start_feedback();//��������
	
	changeFunc(APPLICATION_APRILTAG);
	setLed(true);	
		


	while(1)
	{  
		updateResult(); //����ͷģ�飬���½��
//		GoodMoto(60,60);
//		if (anyTagDetected()) //�Ƿ�ʶ����AprilTag
//		{ 	
//				//for (int i = 0; i < 200; i++) 
//			  //{
//           if (tagIdDetected(1)) 
//					 {
//               beep();
//						 
//           }
//         //}
//    }
		
		
		Key = KEY_Scan(0);
		Key_Temp = Key;
		ShowStr(0,1,"1�����ģʽ");
		ShowStr(2,1,"2��������");
		ShowStr(4,1,"3�����Գ���");
		ShowStr(6,1,"4������");
		Key = KEY_Scan(0);
		if(Key != 0) Key_Temp = Key;
		if(Key_Temp==1)//����1�����
		{
			test();
		}
		else if(Key_Temp==2)//����2�����
		{
			ClearScreen();
	  	up_stage();
			while(1)
			{   
				updateResult();
				get_edge();
				if(select_high()) 
					Find_Taizi();
				find_single();
			}
		}
		else if(Key_Temp==3)//����3�����
		{
			ClearScreen();
			while(1)
			{
				emagnet_off();
				delay_ms(1000);
				emagnet_on();
				delay_ms(1000);


//				ShowAI(0,1,n);
//				if(DI(1)==1)
//				{
//					while(1)
//					{
//						if(DI(1)==0)
//						{
//							n=n+1;
//							break;
//						}
//				}
//				}
		    }
//			up_stage();
//			GoodMoto(0,0);
		}
		else if(Key_Temp==4)//����4�����
		{
				
			ClearScreen();
			touch_sensor();
		}
	}
}
