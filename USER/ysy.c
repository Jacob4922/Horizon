#include "ysy.h"//ע�ͼ�ͷ�ļ�
#include "edge.h"
#define front_get			analog_scan_close()==2||analog_scan_close()==3
#define back_get				analog_scan_close()==7||analog_scan_close()==8

void GoodMoto(int lspeed,int rspeed);
extern void AD_Detection(void);
extern int Rs,Ls;

void speed_dispaly(void)
{
	ShowStr(0,1,"��ǰ�ٶ�");
	ShowStr(2,1,"Left      Right");
	ShowAI(4,1,Ls);
	ShowAI(4,80,Rs);
}

int abs(int a,int b)//��ľ���ֵ
{
	if((a-b)>=0)
		return a-b;
	else
		return b-a;
}

//int Touch(void)//����ADת��
//{
//	if(AI(12)>2000)
//	{
//		led_on();
//		delay_ms(10);
//		if(AI(12)>2000)
//		{
//			led_off();
//			return 1;
//		}
//	}
//	else 
//		return 0;
//}

void up_stage(void)//��̨�׶�
{
	while(AI(10)<2000)
	{
			ClearScreen();
			ShowStr(2,5,"Stand By");
	}
	ClearScreen();
	ShowStr(2,5,"��̨");
	{
			GoodMoto(-450,-450);
			delay_ms(1800);
			GoodMoto(0,0);
			delay_ms(100);
			GoodMoto(300,-300);
			delay_ms(1000);
			GoodMoto(50,50);
			delay_ms(100);
	}
}

void start_feedback(void)//��������
{
	ShowStr(2,1,"  The Warrior");
	delay_ms(2000);
	beep();
	led_on();
	delay_ms(300);
	beep();
	led_off();
	ClearScreen();
}

int analog_scan_close(void)//��ӽ���������¼
{
	int j,t=0,temp=1200;  //1200��Ӧ�ĺ��⴫��������з��ľ�������45cm
	for(j=1;j<=11;j++)
	{
		if(temp<AI(j))
		{
			temp=AI(j);
			t=j;
		}
	}
	ShowAI(4,1,t);
	return t;
}

int analog_scan_far(void)//��Զ�봫������¼
{
	int j,t,temp=AI(1);
	for(j=1;j<=10;j++)
	{
		if(temp>AI(j)&&j!=5&&j!=10)
		{
			temp=AI(j);
			t=j;
		}
	}
	return t;
}

void touch_sensor()//����ģ��AI(12)//��ʱδ֪
{
	u8 Key = 0;
	ShowStr(2,0,"Touch Sensor");	
	while(1)
	{
		Key=KEY_Scan(0);
		if(Key==2)
			{
				delay_ms(1000);
				ClearScreen();
				break;
			}
	}
}

void test(void)//���Ժ���
{
	int i;
	u8 Key = 0;
	ClearScreen();
	while(1)
		{
			ShowStr(0,1,"1�����������");
			ShowStr(2,1,"2��������");
			ShowStr(4,1,"3��������");
			ShowStr(6,1,"4������");
			Key=KEY_Scan(0);
			if(Key==1)
			{
				AD_Detection();
				ClearScreen();
			}
			else if(Key==2)
			{
				while(1)
				{
					ClearScreen();
					for(i=0;i<=180;)
					{
						ShowStr(0,1,"����������");
						ShowStr(2,1,"���PWM:");
						ShowAI(4,30,i);
						servos(1,i);
						servos(2,i);
						delay_ms(100);
						//if(Touch()==1) {i++;delay_ms(100);}
					}
				}
			}
			else if(Key==3)
			{
				while(1)
				{
					ClearScreen();

					for(i=0;i<=1000;)
					{
						ShowStr(0,1,"�����Ըı�");
						ShowStr(2,1,"���ת��:");
						if(i>=0)
						{
							ShowStr(4,20," ");
							ShowAI(4,30,i);
						}
						else
						{
							ShowStr(4,20,"-");
							ShowAI(4,30,-i);
						}
						GoodMoto(i,i);
//						if(Touch()==1) {i=i+50;delay_ms(500);}
						Key=KEY_Scan(0);
						if(Key==1&&i<1000)	{i=i+50;delay_ms(100);}
						else if(Key==2&&i>-1000) {i=i-50;delay_ms(100);}
						else if(Key==3) {i=-i;delay_ms(100);}
						else if(Key==4) goto end;
						Key=0;
					}
				}
			}
			else if(Key==4)
			{
				end:
				Key=0;
				break;
				ClearScreen();
			}
		}
}

int select_high(void)//��̨���
{
	int i;
	ClearScreen();
	for(i=1;i<=7;i++)
	{
			if(AI(i)>1000&&AI(i+1)>1000&&AI(i+4)>1000)	//�м���һ��������һ���̶��ϼ������У�������̨ ��Ӧ�Գٶ�һ�
			{
				ShowStr(0,1,"��̨");
				GoodMoto(0,0);//ɲ��
				//Find_Taizi();	
				return 1;
			}
	}
//	if(AI(2)>1000&&AI(3)>1000&&AI(11)>1000)
//	{
//		ShowStr(0,1,"�����̨��");
//		GoodMoto(0,0);
//	  touch_sensor();
//		Find_Taizi();
//	}
//	if(AI(2)>1000&&AI(3)>1000&&AI(7)>1000)
//	{
//		ShowStr(0,1,"�����̨��");
//		GoodMoto(0,0);
//	  touch_sensor();
//		Find_Taizi();
//	}
	return 0;//����̨��
}

void find_single()
{   
	if(tagIdDetected(2))
	{
		beep();
		reset_time();
		while(1)
		{
			if(F_G_E||mseconds()>200)	break;//�����̨����Ե�����
			GoodMoto(-300,300);
		}
	}
	else
	{
		switch(analog_scan_close())
		{
			case 1:		//��ǰ40��
			{
				reset_time();
				while(1)
				{
					if(get_edge()||mseconds()>80)	break;//�����̨����Ե�����
					GoodMoto(-300,300);
				}
				break;
			}
			case 2:		//ǰ
			{   
			  GoodMoto(0,0);
			  delay_ms(500);
				updateResult();
				reset_time();
				while(1)
				{    				
					if(tagIdDetected(2))
					{   
						reset_time();
						beep();
						while(1)
						{
							if(F_G_E||mseconds()>200)	break;//�����̨����Ե�����
							GoodMoto(-300,300);
						}
					    reset_time();    
						while(1)
						{
							if(F_G_E||mseconds()>500)	break;//�����̨����Ե�����
							GoodMoto(350,350);
						}
						updateResult();
						break;
					}
					else if(F_G_E||mseconds()>300)	break;//�����̨����Ե�����
						GoodMoto(350,350);
				}
				break;
			}
			case 3:		//ǰ
			{
				GoodMoto(0,0);
				delay_ms(500);
				updateResult();
				reset_time();
				while(1)
				{    
					if(tagIdDetected(2))
					{   
						reset_time();
						beep();
						while(1)
						{
							if(F_G_E||mseconds()>200)	break;//�����̨����Ե�����
							GoodMoto(-300,300);
						}
						reset_time();
						while(1)
						{
							if(F_G_E||mseconds()>500)	break;//�����̨����Ե�����
							GoodMoto(350,350);
						}
						updateResult();
						break;
					}
					else if(F_G_E||mseconds()>300)	break;//�����̨����Ե�����
						GoodMoto(350,350);
				}
				break;
			}
			case 4:		//��ǰ40��
			{
				reset_time();
				while(1)
				{
					if(get_edge()||mseconds()>80)	break;//�����̨����Ե�����
					GoodMoto(300,-300);
				}
				break;
			}
			case 5:		//��ǰ60��
			{
				reset_time();
				while(1)
				{
					if(get_edge()||mseconds()>90)	break;//�����̨����Ե�����
					GoodMoto(300,-300);
				}
				break;
			}
			case 6:		//��90��
			{
				reset_time();
				while(1)
				{
					if(get_edge()||mseconds()>100)	break;//�����̨����Ե�����
					GoodMoto(300,-300);
				}
				break;
			}
			case 7:		//�Һ�45��
			{
				reset_time();
				while(1)
				{
					if(get_edge()||mseconds()>150)	break;//�����̨����Ե�����
					GoodMoto(300,-300);
				}
				break;
			}
			case 8:		//��
			{
				reset_time();
				while(1)
				{
					if(get_edge()||mseconds()>800)	break;//�����̨����Ե�����
					GoodMoto(300,-300);
				}
				break;
			}
			case 9:		//���45��
			{
				reset_time();
				while(1)
				{
					if(get_edge()||mseconds()>150)	break;//�����̨����Ե�����
					GoodMoto(-300,300);
				}
				break;
			}
			case 10:		//��90��
			{
				reset_time();
				while(1)
				{
					if(get_edge()||mseconds()>100)	break;//�����̨����Ե�����
					GoodMoto(-300,300);
				}
				break;
			}
			case 11:		//��ǰ60��
			{
				reset_time();
				while(1)
				{
					if(get_edge()||mseconds()>80)	break;//�����̨����Ե�����
					GoodMoto(-300,300);
				}
				break;
			}
			default:
			{
				GoodMoto(300,300);
				break;
			}
		}
	}
}
//int Find_Taizi()
//{ 
//	while(1)
//	 {
//		 	ClearScreen();
//		    if((AI(9)>1000&&AI(2)>1500&&AI(3)>1500&&AI(6)<200&&AI(10)>1000)||((AI(7)>1000&&AI(2)>1500&&AI(3)>1500)&&AI(10)<400)&&AI(6)>1000)       
//				{ GoodMoto(-250,-250); 
//	      ShowStr(0,3,"���ٺ���");}
//		   else if((AI(2)>1000||AI(3)>1000)&&AI(5)>1500&&AI(11)>1500&&AI(7)<200&&AI(9)<200)      
//			 {GoodMoto(-250,250); 
//	      ShowStr(0,3,"�����������");		}
//		   else if((AI(1)>1900||AI(4)>900)&&(AI(5)>1000&&AI(16)>1000&&AI(10)<100&&AI(11)<100)||(AI(5)<100&&AI(16)<100&&AI(10)>1000&&AI(11)>1000))       
//			 {GoodMoto(250,-250); 
//	      ShowStr(0,3,"���뿨̨");	}			 
//	     else if(AI(6)>1000&&AI(10)>1000)         
//			   {
//          reset_time();
//				  while(1)
//				   {
//					   GoodMoto(250,250);
//					   if(mseconds()>50)
//						   break;
//				   }
//				 }
////	      ShowStr(0,3,"90��ת��");						 
//	     else if((abs(AI(1),AI(4))<400)&&(abs(AI(7),AI(9))<400)&&AI(2)>1000&&AI(3)>1000&&AI(8)>700&&AI(12)>1500) 
//			 {
//				  GoodMoto(250,250);  
//			    delay_ms(1000);
//			    GoodMoto(0,0);
//				  delay_ms(100);
//			    up_stage();	
//				 return 0;
//			 }				 
////	      break; 
////	      ShowStr(0,3,"׼����̨");	
//	     else if(AI(12)<1000&&AI(2)>1000&&AI(3)>1000)         
//			  {
//				 reset_time();  
//			   while(1)
//				   {
//					   GoodMoto(250,-250);
//					   if(mseconds()>80)
//						   break;
//				   }
//				 }
////	      ShowStr(0,3,"180��ת��");		
//		   else if(AI(7)<500&&AI(8)>1000&&AI(9)<500&&AI((6)<500||AI(10)<500))       
//			  {
//				 reset_time();
//				 while(1)
//				   {
//					   GoodMoto(250,250);
//					   if(mseconds()>500)
//						   break;
//				   }
//				}
////	      ShowStr(0,3,"�尡��������");					 
//	     else
//	     	  GoodMoto(-300,-300); 
////	      ShowStr(0,3,"������");
// }
//}

void Find_Taizi(void)
{ 
  while(1)
  {
	  if(AI(8)>1000&&AI(12)<1000&&AI(13)<1000&&(AI(10)<500||AI(6)<500))
	  {
		  GoodMoto(-500,-500);
		  LOOP:delay_ms(1500);
		  if(AI(0)>2300) goto LOOP;
	  }
	  else if(AI(1)<200&&AI(2)>2000)
	  {   
		  reset_time();
		  while(1)
		  { 
			if(mseconds()>1000) break;
			GoodMoto(-150,-150);
		  }
	  }
	  else if(AI(2)>2000&&AI(3)<200)
	  {   
		  reset_time();
		  while(1)
		  { 
			if(mseconds()>1000) break;
			GoodMoto(-150,-150);
		  }
	  }
	  else if(AI(12)>2000&&AI(13)>2000)
	  {   
		  reset_time();
		  while(1)
		  { 
			if(mseconds()>1000) break;
			GoodMoto(150,150);
		  }
	  }
	  else if(!select_high())
		  break;
	  else
		  GoodMoto(-250,250);
	  
  }
}

