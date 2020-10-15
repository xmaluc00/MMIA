#include "stm32f0xx.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


int main(void)
{

	sct_init();
	sct_led(0x7A5C36DE);
	for (volatile uint32_t j = 0; j < 3000000; j++) {}

	for (;;){

		for (volatile uint32_t i = 0; i < 1000; i += 111) {
			sct_value(i);
			for (volatile uint32_t j = 0; j < 500000; j++) {}
		}

	}

}
