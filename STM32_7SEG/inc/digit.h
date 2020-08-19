#ifndef DIGIT_H_
#define DIGIT_H_



extern void TIM2_IRQHandler (void);
extern void init_timer2(void);
extern void init_Digit(void);

unsigned short	decryption_digit_function(unsigned short digit);
void encryption_function(unsigned short *mass);
void nomb_to_digit (unsigned short *pointMas, unsigned int n);

extern unsigned short DIG_0;
extern unsigned short DIG_1;
extern unsigned short DIG_2;

extern unsigned short Digit_val [23];

extern int //i,
flag_next,
ind;



#endif /* DIGIT_H_ */
