#include "stm32f0xx.h"

static volatile uint32_t Tick;

#define LED_TIME_BLINK 300
#define BUTTON_DEBOUNCE 40
#define LED_TIME_SHORT 100
#define LED_TIME_LONG 1000

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


void EXTI0_1_IRQHandler(void)
{
	if (EXTI->PR & EXTI_PR_PR0) { // check line 0 has triggered the IT
	EXTI->PR |= EXTI_PR_PR0; // clear the pending bit
	GPIOB->ODR ^= (1<<0); // toggle ;
	}
}


void SysTick_Handler(void)
{
	Tick++;
}


void blikac(void)
{
	static uint32_t delay;
	if (Tick > delay + LED_TIME_BLINK) {
		GPIOA->ODR ^= (1<<4);
		delay = Tick;
	}
}



void tlacitka(void)
{
	static uint32_t off_time;
	static uint32_t debounce1;

	if (Tick > debounce1 + BUTTON_DEBOUNCE){

		static uint32_t old_s2;
		uint32_t new_s2 = GPIOC->IDR & (1<<0);
		static uint32_t old_s1;
		uint32_t new_s1 = GPIOC->IDR & (1<<1);

		if (old_s2 && !new_s2) { // falling edge S2

			off_time = Tick + LED_TIME_SHORT;
			GPIOB->BSRR = (1<<0);

		 }

		else if (old_s1 && !new_s1) { // falling edge S1

			off_time = Tick + LED_TIME_LONG;
			GPIOB->BSRR = (1<<0);

		 }

		 old_s2 = new_s2;
		 old_s1 = new_s1;

	}

	if (Tick > off_time) {
		GPIOB->BRR = (1<<0);
	}

}


int main(void)
{

	RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOBEN | RCC_AHBENR_GPIOCEN; // enable peripheral clock for A, B and C registers
	GPIOA->MODER |= GPIO_MODER_MODER4_0; // LED1 = PA4, output
	GPIOB->MODER |= GPIO_MODER_MODER0_0; // LED2 = PB0, output
	GPIOC->PUPDR |= GPIO_PUPDR_PUPDR0_0; // S2 = PC0, pullup
	GPIOC->PUPDR |= GPIO_MODER_MODER1_0; // S1 = PC1, pullup

	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

	SysTick_Config(8000);

//	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PC; // select PC0 for EXTI0
//	EXTI->IMR |= EXTI_IMR_MR0; // mask
//	EXTI->FTSR |= EXTI_FTSR_TR0; // trigger on falling edge
//	NVIC_EnableIRQ(EXTI0_1_IRQn); // enable EXTI0_1


	for (;;){

		blikac();

	}

}
