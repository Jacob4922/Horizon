#include "init.h"

# define AI 				analog
# define DI					digital

# define F_G_E			DI(1)==1 || DI(2)==1			// ǰ������̨
# define LF_G_E			DI(1)==1 && DI(2)==0			// ǰ���󷽳���̨
# define RF_G_E			DI(1)==0 && DI(2)==1			// ǰ���ҷ�����̨

# define A_S_C			0//analog_scan_close()					//����

#define AI 							analog
#define DI							digital
#define ClearScreen 		clear_screen
#define ShowStr 				display_GB2312_string		//�ַ�������
#define ShowAI					display_GB2312_u16 //��λ����
#define ShowDI					display_GB2312_u1		//һλ����
#define ServoSetMode		UP_CDS_SetMode					
#define ServoSetAngle		UP_CDS_SetAngle

int get_edge(void);//Ѳ̨
