#include "stm32f0xx.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


int main(void)
{

	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	GPIOA->MODER |= GPIO_MODER_MODER5_0;

	uint32_t pole = 0xA9DDCA80; 								// SOS

	for (;;){

		for(uint8_t i = 0;i<31;i++){

			if (pole & (1 << i)) GPIOA->BSRR = (1<<5);			// smer irelevantni, zleva doprava (pole & (0x8000 >> i))
			else GPIOA->BRR = (1<<5);

		}

	}

}
