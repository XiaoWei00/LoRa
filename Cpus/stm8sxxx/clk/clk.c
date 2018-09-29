#include "clk.h"


void clk_init()
{
    CLK_CKDIVR = 0x08;         // 16M内部RC经2分频后系统时钟为8M
}

