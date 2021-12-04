#include "stm32f401cc_interface.h"

int main(void) {
	// Enabling GPIOB
	RCC_AHB1ENR |= (0x01 << 1);

	// setting pin3 as input for the push button
	GPIOB_MODER &= ~(0x03 << 6);

	// internal pull-up resistor enabled
	GPIOB_PUPDR &= ~(0x01 << 6);
	GPIOB_PUPDR |= (0x01 << 6);

	// setting pins 5,6,7 as output
	// 0001 0101 >> 0x15
	GPIOB_MODER &= ~(0x15 << 10);
	GPIOB_MODER |= (0x15 << 10);

	// type of 3 output pins as push-pull
	GPIOB_OTYPER &= ~(0x07 << 5);


	unsigned char color = 0x00;



	while(1)
	{
		unsigned int reading1 = GPIOB_IDR & 0x08;

		// approximatly  1 ms before 2nd reading for debouncing
		for(unsigned int i = 0; i < 1000; i++)
		{}

		unsigned char reading2 = GPIOB_IDR & 0x08;

		// Falling edge -> reading1 is 1 (not pushed) and reading2 is 0 (pushed)
		if(reading1 && reading2 != reading1)
		{
			color += 0x01;
			if (color == 0x08)
			{
				color = 0x00;
			}
			GPIOB_ODR &= ~(0x07 << 5); //clear the 3 pins 5,6,7
			GPIOB_ODR |= (color << 5); //set color

			for(unsigned int i = 0; i < 10000; i++)
			{}

		}



	}

  return 0;
}
