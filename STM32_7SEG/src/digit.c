
#include "stm32f10x.h"
#include "digit.h"


unsigned short digit_main = 0, tiker = 0;



#define sig_a 			GPIO_BSRR_BS4		// A
#define sig_b 			GPIO_BSRR_BS7		// A
#define sig_c 			GPIO_BSRR_BS15		// B
#define sig_d 			GPIO_BSRR_BS13		// B
#define sig_e 			GPIO_BSRR_BS12		// B
#define sig_f 			GPIO_BSRR_BS5		// A
#define sig_g 			GPIO_BSRR_BS8		// A
#define sig_dp 			GPIO_BSRR_BS14		// B




unsigned short Digit_val_portB [23] = {
		sig_c | sig_d | sig_e,				// 0 // 0 - a-b-c-d-e-f
		sig_c ,								// 1 // 1 - b-c
		sig_d | sig_e,						// 2 // 2 - a-b-d-e-g
		sig_c | sig_d,						// 3 // 3 - a-b-c-d-g
		sig_c,								// 4 // 4 - b-c-f-g
		sig_c | sig_d,						// 5 // 5 - a-c-d-f-g
		sig_c | sig_d | sig_e,				// 6 // 6 - a-c-d-e-f-g
		sig_c ,								// 7 // 7 - a-b-c
		sig_c | sig_d | sig_e,				// 8 // 8 - a-b-c-d-e-f-g
		sig_c | sig_d,						// 9 // 9 - a-b-c-d-f-g
		sig_c | sig_e,						// 10 // A - a-b-c-e-f-g
		sig_c | sig_d | sig_e,				// 11 // b - c-d-e-f-g
		sig_d | sig_e,						// 12 // c - a-d-e-f
		sig_c | sig_d | sig_e,				// 13 // d - b-c-d-e-g
		sig_d | sig_e,						// 14 // E - a-d-e-f-g
		sig_e,								// 15 // F - a-e-f-g
		sig_c | sig_d | sig_e,				// 16 // U
		sig_c | sig_e,						// 17 // n
		sig_c | sig_e,						// 18 // H
		sig_c | sig_e,						// 19 // h
		sig_dp,								// 21 // DP
		sig_e								// 22 // r

};




unsigned short Digit_val_portA [23] = {
		sig_a | sig_b | sig_f,				// 0 // 0 - a-b-c-d-e-f
		sig_b,								// 1 // 1 - b-c
		sig_a | sig_b | sig_g,				// 2 // 2 - a-b-d-e-g
		sig_a | sig_b | sig_g,				// 3 // 3 - a-b-c-d-g
		sig_b | sig_f | sig_g,				// 4 // 4 - b-c-f-g
		sig_a | sig_f | sig_g,				// 5 // 5 - a-c-d-f-g
		sig_a | sig_f | sig_g,				// 6 // 6 - a-c-d-e-f-g
		sig_a | sig_b,						// 7 // 7 - a-b-c
		sig_a | sig_b | sig_f | sig_g,		// 8 // 8 - a-b-c-d-e-f-g
		sig_a | sig_b | sig_c | sig_f | sig_g,// 9 // 9 - a-b-c-d-f-g
		sig_a | sig_b | sig_f | sig_g,		// 10 // A - a-b-c-e-f-g
		sig_f | sig_g,						// 11 // b - c-d-e-f-g
		sig_a | sig_f,						// 12 // c - a-d-e-f
		sig_b | sig_g,						// 13 // d - b-c-d-e-g
		sig_a | sig_f | sig_g,				// 14 // E - a-d-e-f-g
		sig_a | sig_f | sig_g,				// 15 // F - a-e-f-g
		sig_b | sig_f,						// 16 // U
		sig_g,								// 17 // n
		sig_b | sig_g | sig_f,				// 18 // H
		sig_f | sig_g,						// 19 // h
		sig_g,								// 20 // -
		sig_g								// 22 // r
};

unsigned short DIG_0;
unsigned short DIG_1;
unsigned short DIG_2;


		int i = 0,
		flag_next = 0,
		ind=0;



void init_Digit(void){
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;   // ��������� ������������ GPIOA
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;   // ��������� ������������ GPIOB
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;   // ��������� ������������ GPIOC




	// a	PA4

			GPIOA->CRL &= ~GPIO_CRL_MODE4;  //�������� ������� MODE
			GPIOA->CRL &= ~GPIO_CRL_CNF4;   //�������� ������� CNF
			GPIOA->CRL |=  GPIO_CRL_MODE4;  //�����, 50MHz
			GPIOA->CRL &= ~GPIO_CRL_CNF4;   //������ ����������, �����������
			GPIOA->BSRR =  GPIO_BSRR_BR4;

	// b	PA7

			GPIOA->CRL &= ~GPIO_CRL_MODE7;  //�������� ������� MODE
			GPIOA->CRL &= ~GPIO_CRL_CNF7;   //�������� ������� CNF
			GPIOA->CRL |=  GPIO_CRL_MODE7;  //�����, 50MHz
			GPIOA->CRL &= ~GPIO_CRL_CNF7;   //������ ����������, �����������
			GPIOA->BSRR =  GPIO_BSRR_BR7;

	// c	PB15

			GPIOB->CRH &= ~GPIO_CRH_MODE15;   //�������� ������� MODE
			GPIOB->CRH &= ~GPIO_CRH_CNF15;    //�������� ������� CNF
			GPIOB->CRH |=  GPIO_CRH_MODE15;   //�����, 50MHz
			GPIOB->CRH &= ~GPIO_CRH_CNF15;    //������ ����������, �����������
			GPIOB->BSRR =  GPIO_BSRR_BR15;

	// d	PB13

			GPIOB->CRH &= ~GPIO_CRH_MODE13;   //�������� ������� MODE
			GPIOB->CRH &= ~GPIO_CRH_CNF13;    //�������� ������� CNF
			GPIOB->CRH |=  GPIO_CRH_MODE13;   //�����, 50MHz
			GPIOB->CRH &= ~GPIO_CRH_CNF13;    //������ ����������, �����������
			GPIOB->BSRR =  GPIO_BSRR_BR13;

	// e	PB12

			GPIOB->CRH &= ~GPIO_CRH_MODE12;   //�������� ������� MODE
			GPIOB->CRH &= ~GPIO_CRH_CNF12;    //�������� ������� CNF
			GPIOB->CRH |=  GPIO_CRH_MODE12;   //�����, 50MHz
			GPIOB->CRH &= ~GPIO_CRH_CNF12;    //������ ����������, �����������
			GPIOB->BSRR =  GPIO_BSRR_BR12;

	// f	PA5

			GPIOA->CRL &= ~GPIO_CRL_MODE5;   //�������� ������� MODE
			GPIOA->CRL &= ~GPIO_CRL_CNF5;    //�������� ������� CNF
			GPIOA->CRL |=  GPIO_CRL_MODE5;   //�����, 50MHz
			GPIOA->CRL &= ~GPIO_CRL_CNF5;    //������ ����������, �����������
			GPIOA->BSRR =  GPIO_BSRR_BR5;

	// g	PA8

			GPIOA->CRH &= ~GPIO_CRH_MODE8;   //�������� ������� MODE
			GPIOA->CRH &= ~GPIO_CRH_CNF8;    //�������� ������� CNF
			GPIOA->CRH |=  GPIO_CRH_MODE8;   //�����, 50MHz
			GPIOA->CRH &= ~GPIO_CRH_CNF8;    //������ ����������, �����������
			GPIOA->BSRR =  GPIO_BSRR_BR8;

	// DP	PB14

			GPIOB->CRH &= ~GPIO_CRH_MODE14;   //�������� ������� MODE
			GPIOB->CRH &= ~GPIO_CRH_CNF14;    //�������� ������� CNF
			GPIOB->CRH |=  GPIO_CRH_MODE14;   //�����, 50MHz
			GPIOB->CRH &= ~GPIO_CRH_CNF14;    //������ ����������, �����������
			GPIOB->BSRR =  GPIO_BSRR_BR14;




	// dig0 PA3

			GPIOA->CRL &= ~GPIO_CRL_MODE3;  //�������� ������� MODE
			GPIOA->CRL &= ~GPIO_CRL_CNF3;   //�������� ������� CNF
			GPIOA->CRL |=  GPIO_CRL_MODE3;  //�����, 50MHz
			GPIOA->CRL |=  GPIO_CRL_CNF3;  //������ ����������, �����������

			GPIOA->BSRR =  GPIO_BSRR_BR3;


	// dig1 PA6

			GPIOA->CRL &= ~GPIO_CRL_MODE6;   //�������� ������� MODE
			GPIOA->CRL &= ~GPIO_CRL_CNF6;    //�������� ������� CNF
			GPIOA->CRL |=  GPIO_CRL_MODE6;   //�����, 50MHz
			GPIOA->CRL |=  GPIO_CRL_CNF6;  //������ ����������, �����������

			GPIOA->BSRR =  GPIO_BSRR_BR6;


	// dig2 PB0

			GPIOB->CRL &= ~GPIO_CRL_MODE0;   //�������� ������� MODE
			GPIOB->CRL &= ~GPIO_CRL_CNF0;    //�������� ������� CNF
			GPIOB->CRL |=  GPIO_CRL_MODE0;   //�����, 50MHz
			GPIOB->CRL |=  GPIO_CRL_CNF0;  //������ ����������, �����������

			GPIOB->BSRR =  GPIO_BSRR_BR0;
}



//��������� ������� 2 - ������������ ��������
void init_timer2(void){

 RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
//TIM2->CR1 |= TIM_CR1_CKD_1;
TIM2->CR1 |= TIM_CR1_ARPE; //shadow
//TIM2->CR1 |= TIM_CR1_URS;
//TIM2->CR1 |= TIM_CR1_DIR;

TIM2->PSC = 35;// 72MHz/(PSC+1);//���� ��� 0,5 ���
TIM2->ARR = 1999;//(ARR)//1000 �� // 1 mc

//TIM2->DIER |= TIM_DIER_TIE;
TIM2->DIER |= TIM_DIER_UIE;
TIM2->DIER |= TIM_DIER_CC1IE;
//TIM2->DIER |= TIM_DIER_CC2IE;
//TIM2->DIER |= TIM_DIER_CC3IE;



TIM2->CCR1 = 2000;//200 ���  120; //  �� ����������� - ����������
//TIM2->CCR3 = 50;

TIM2->CR1 |= TIM_CR1_CEN;
NVIC_EnableIRQ (TIM2_IRQn);


}





//���������� ������� 2 - ������������ ��������
void TIM2_IRQHandler (void){
unsigned short status;
//unsigned int temp;
status = TIM2->SR;//~TIM_SR_UIF; //= 0;//&
TIM2->SR = ~status;
//----------------------------------------------------------------
if(status & TIM_SR_CC1IF){	// ���������
	// 15-0-1-2-3
	GPIOA->BSRR =  GPIO_BSRR_BR3 | GPIO_BSRR_BR6;
	GPIOB->BSRR =  GPIO_BSRR_BR0;

}
//----------------------------------------------------------------
//if(status & TIM_SR_CC2IF){
//}
//----------------------------------------------------------------
//if(status & TIM_SR_CC3IF){

//}

tiker ++;
if (tiker == 30){//500
	tiker = 0;
	flag_next = 1;

}
//----------------------------------------------------------------
// ��������� �� ��������� ����� � ��������
if(status & TIM_SR_UIF){

	GPIOA->BSRR = GPIO_BSRR_BR4 | GPIO_BSRR_BR7 | GPIO_BSRR_BR8;
	GPIOB->BSRR = GPIO_BSRR_BR15 | GPIO_BSRR_BR13 | GPIO_BSRR_BR12 | GPIO_BSRR_BR5 | GPIO_BSRR_BR14;


	if( digit_main == 0){
		GPIOA->BSRR =  GPIO_BSRR_BS3;  //GPIOA.3=0
		digit_main++;

		GPIOA->BSRR = DIG_0;
		GPIOB->BSRR = DIG_0;

		return;
	}
	if( digit_main == 1){
		GPIOA->BSRR =  GPIO_BSRR_BS6;  //GPIOA.6=0
		digit_main++;

		GPIOA->BSRR = DIG_1;
		GPIOB->BSRR = DIG_1;
		return;
	}
	if( digit_main ==2){
		GPIOB->BSRR =  GPIO_BSRR_BS0;  //GPIOB.0=0
		digit_main=0;

		GPIOA->BSRR = DIG_2;
		GPIOB->BSRR = DIG_2;
		return;
	}

}

}






void nomb_to_digit (unsigned short *pointMas, unsigned int n)
{

	for (unsigned int i = 0; i<5; i++) {pointMas[i] = 0;}			// ������ ������ ����� �������. ���� �� ���� ��������� ����� ������� ����


	for (unsigned int i = 0; i<5; i++)
	{
		unsigned short digit = n%10;
		n /= 10;

		pointMas[i] = digit;
	}
}



void encryption_function(unsigned short *mass)
{
	for(int i = 0; i <= 5; i++)								// �������� ������ � ��������.
	{
		switch(mass[i])
		{
			case 0:{mass[i] = Digit_val[0];}
			break;
			case 1:{mass[i] = Digit_val[1];}
			break;
			case 2:{mass[i] = Digit_val[2];}
			break;
			case 3:{mass[i] = Digit_val[3];}
			break;
			case 4:{mass[i] = Digit_val[4];}
			break;
			case 5:{mass[i] = Digit_val[5];}
			break;
			case 6:{mass[i] = Digit_val[6];}
			break;
			case 7:{mass[i] = Digit_val[7];}
			break;
			case 8:{mass[i] = Digit_val[8];}
			break;
			case 9:{mass[i] = Digit_val[9];}
			break;

		}// ������ �����
	}// ������ ����
}


unsigned short	decryption_digit_function(unsigned short digit)
{

	unsigned short out_digit;

	if(digit == Digit_val[0]){out_digit = 0;}
	if(digit == Digit_val[1]){out_digit = 1;}
	if(digit == Digit_val[2]){out_digit = 2;}
	if(digit == Digit_val[3]){out_digit = 3;}
	if(digit == Digit_val[4]){out_digit = 4;}
	if(digit == Digit_val[5]){out_digit = 5;}
	if(digit == Digit_val[6]){out_digit = 6;}
	if(digit == Digit_val[7]){out_digit = 7;}
	if(digit == Digit_val[8]){out_digit = 8;}
	if(digit == Digit_val[9]){out_digit = 9;}

	return (out_digit);
}


