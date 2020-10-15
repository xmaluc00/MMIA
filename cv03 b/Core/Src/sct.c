#include "stm32f0xx.h"
#include "sct.h"
#include "main.h"


void sct_led (uint32_t value) {

	for (uint8_t i = 0; i < 32; i++) {

		sct_sdi(value & (1 << i));
		HAL_GPIO_WritePin(SCT_CLK_GPIO_Port, SCT_CLK_Pin, 1);
		HAL_GPIO_WritePin(SCT_CLK_GPIO_Port, SCT_CLK_Pin, 0);

	}

	HAL_GPIO_WritePin(SCT_NLA_GPIO_Port, SCT_NLA_Pin, 1);
	HAL_GPIO_WritePin(SCT_NLA_GPIO_Port, SCT_NLA_Pin, 0);

}


void sct_init (void) {


	HAL_GPIO_WritePin(SCT_LED_GPIO_Port, SCT_LED_Pin, 0);
	HAL_GPIO_WritePin(SCT_NOE_GPIO_Port, SCT_NOE_Pin, 0);

}


void sct_value (uint16_t value) {

	static const uint32_t reg_values[3][10] = {

	 {
		 //PCDE--------GFAB @ DIS1			pripojeni viz schema!!
		 0b0111000000000111 << 16,
		 0b0100000000000001 << 16,
		 0b0011000000001011 << 16,
		 0b0110000000001011 << 16,
		 0b0100000000001101 << 16,
		 0b0110000000001110 << 16,
		 0b0111000000001110 << 16,
		 0b0100000000000011 << 16,
		 0b0111000000001111 << 16,
		 0b0110000000001111 << 16,
	 },
	 {
		 //----PCDEGFAB---- @ DIS2
		 0b0000011101110000 << 0,
		 0b0000010000010000 << 0,
		 0b0000001110110000 << 0,
		 0b0000011010110000 << 0,
		 0b0000010011010000 << 0,
		 0b0000011011100000 << 0,
		 0b0000011111100000 << 0,
		 0b0000010000110000 << 0,
		 0b0000011111110000 << 0,
		 0b0000011011110000 << 0,
	 },
	 {
		 //PCDE--------GFAB @ DIS3
		 0b0111000000000111 << 0,
		 0b0100000000000001 << 0,
		 0b0011000000001011 << 0,
		 0b0110000000001011 << 0,
		 0b0100000000001101 << 0,
		 0b0110000000001110 << 0,
		 0b0111000000001110 << 0,
		 0b0100000000000011 << 0,
		 0b0111000000001111 << 0,
		 0b0110000000001111 << 0,
	 },
	 };

	uint32_t reg = 0;
	reg |= reg_values[0][value/100%10];
	reg |= reg_values[0][value/10%10];
	reg |= reg_values[0][value/1%10];

	HAL_GPIO_WritePin(SCT_LED_GPIO_Port, SCT_LED_Pin, reg);

}
