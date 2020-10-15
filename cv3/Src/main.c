#include "stm32f0xx.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


int main(void)
{

	sct_init();
	svt_led(0x7A5C36DE);

	for (;;){

	}

}
