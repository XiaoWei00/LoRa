#include "clk.h"


void clk_init()
{
    CLK_CKDIVR = 0x08;         // 16M�ڲ�RC��2��Ƶ��ϵͳʱ��Ϊ8M
}

