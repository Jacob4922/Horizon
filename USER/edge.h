#include "init.h"

# define AI 				analog
# define DI					digital

# define F_G_E			DI(1)==1 || DI(2)==1			// 前铲出擂台
# define LF_G_E			DI(1)==1 && DI(2)==0			// 前铲左方出擂台
# define RF_G_E			DI(1)==0 && DI(2)==1			// 前铲右方出擂台

# define A_S_C			0//analog_scan_close()					//遇敌

#define AI 							analog
#define DI							digital
#define ClearScreen 		clear_screen
#define ShowStr 				display_GB2312_string		//字符串数显
#define ShowAI					display_GB2312_u16 //四位数显
#define ShowDI					display_GB2312_u1		//一位数显
#define ServoSetMode		UP_CDS_SetMode					
#define ServoSetAngle		UP_CDS_SetAngle

int get_edge(void);//巡台
