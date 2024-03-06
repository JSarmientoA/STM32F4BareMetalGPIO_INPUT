#include "stm32f4xx.h"//Se deben cargar el dispositivo, el include y la referencia especifica

#define GPIOAEN			(1U<<0)
#define GPIOCEN			(1U<<2)

#define PIN5			(1U<<5)
#define PIN13			(1U<<13)
#define LED_PIN			PIN5
#define BUTTONuSER		PIN13
int main(void)
{
	/*Habilitación del reoj para los puertos GPIOA y GPIOC*/
	RCC->AHB1ENR |= GPIOAEN;
	RCC->AHB1ENR |= GPIOCEN;
	/*El regsitro OSPEEDR configura la velocidad del puerto desde baja veida a hasta alta velocidad*/
	GPIOC->OSPEEDR |= (1U<<27);
	GPIOC->OSPEEDR |= (1U<<26);

	/*El registro PUPDR configura los modos pull-up, pull-down*/
	GPIOA ->PUPDR &=~ (1U<<10);
	GPIOA ->PUPDR |=  (1U<<11);

	/*Estableser el pin PA5 como salida usando el registro MODER del preriferico GPIOA*/
	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &=~(1U<<11);

	/*Estableser el pin PC13 como entrada usando el registro MODER del preriferico GPIOC*/
	GPIOC->MODER &=~(1U<<26);//Coloca a cero el bit # 26. Donde &=~ es invertir
	GPIOC->MODER &=~(1U<<27);//Coloca a cero el bit # 27. Donde &=~ es invertir

	while(1)
	{
		/*El registro IDR almacena los datos de entrada del puerto*/
		if(GPIOC->IDR & BUTTONuSER)
		{
			GPIOA->ODR &=~ LED_PIN;
			/*Esta configuración del registro BSRR grantiza un 1 logico (3.3v) en el pin 5*/
			//GPIOA->BSRR = LED_PIN;
			//GPIOA->BSRR = (0U<<21);
			/******************************************************************************/
		}
		else{
			GPIOA->ODR |= LED_PIN;
			/*Esta configuración del registro BSRR grantiza un 0 logico (0.0v) en el pin 5*/
			//GPIOA->BSRR = (1U<<21);
			//GPIOA->BSRR = (0U<<5);
			/*****************************************************************************/
		}
	}
}

/*Al igual que el registro BSRR, el registro ODR se utiliza para poner un uno(1) o cero(0) logico el un pueto.
 * El registro IDR almacena el dato que se haya leido en el puerto*/
