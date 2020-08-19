#include "stm32f10x.h"
#include "system.h"

#include "digit.h"

unsigned short 	mass_digit[5];								// массив для складывание преобразваных цыферок



int main(void)
{
	InitClk();
	init_timer2();
	init_Digit();


	for(;;)
	{

	} // скобочка бесконечного цикла
} // скобочка мейна
