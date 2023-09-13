#include "edge.h"
#include "ysy.h"
#include "pwm.h"


extern void GoodMoto(int lspeed,int rspeed);
//光电返回1出台  st188返回0出台     



void back()
{
	reset_time();
	while(1)
	{
		GoodMoto(-100,-100);
		if(mseconds()>200||A_S_C)	break;
	}	
}

void forward_stop()//前进时反向刹车
{
	reset_time();
	while(1)
	{
		GoodMoto(-200,-200);	
		if(mseconds()>200)	break;
	}
	back();
}

void back_S90()//逆时针90
{
	reset_time();
	while(1)
	{
		GoodMoto(150,-150);
		if(mseconds()>200||A_S_C)	break;
	}	
}

void back_N90()//顺时针90
{
	reset_time();
	while(1)
	{
		GoodMoto(-150,150);
		if(mseconds()>200||A_S_C)	break;
	}
}

void edge_spin()//边缘转身
{
	reset_time();
	while(1)
	{
		GoodMoto(-100,100);	
		if(mseconds()>400||A_S_C)	break;
	}
}
int get_edge()
{
	if(F_G_E)//前铲出台
	{
		if(LF_G_E)
		{
			ShowStr(2,1,"---左侧");
			forward_stop();
			back_S90();
		}
		else if(RF_G_E)
		{
			ShowStr(2,1,"右侧---");
			forward_stop();
			back_S90();
		}
		else
		{
			forward_stop();
			edge_spin();
//			GoodMoto(0,0);
//			delay_ms(1000);
		}
		GoodMoto(300,300);//前进
		delay_ms(100);
		return 1;
	}
	else
	{
		GoodMoto(300,300);
		return 0;
	}
}
