#include "stm32f4xx_tim.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_usart.h"
#include "misc.h"


int i=1;
int j=0;
int stan=0;
GPIO_InitTypeDef  GPIO_InitStructure;
TIM_OCInitTypeDef TIM_OCInitStructure;


void USART3_IRQHandler(void)
{
// sprawdzenie flagi zwiazanej z odebraniem danych przez USART
if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
{
// odebrany bajt znajduje sie w rejestrze USART3->DR
		while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
		char a=USART3->DR;
		if(a=='a')
		{
			GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
			GPIO_SetBits(GPIOD, GPIO_Pin_13);

		}
		if(a=='w')
		{
			GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
			GPIO_SetBits(GPIOD,GPIO_Pin_13);
			GPIO_SetBits(GPIOD,GPIO_Pin_14);
		}
		if(a=='d')
		{
			GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
			GPIO_SetBits(GPIOD,GPIO_Pin_14);
		}
		if(a=='s')
		{
			GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
			GPIO_SetBits(GPIOD,GPIO_Pin_15);
			GPIO_SetBits(GPIOD,GPIO_Pin_12);
		}
		if(a=="START")
				{
						GPIO_SetBits(GPIOA, GPIO_Pin_3);
				}
		if(a=="STOP")
				{
						GPIO_ResetBits(GPIOA, GPIO_Pin_3);
				}

		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
}
}

void Init_Time_engine()
{
	    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;


		   TIM_TimeBaseStructure.TIM_Period = 16; //plynne zmienianie 999
			TIM_TimeBaseStructure.TIM_Prescaler = 83; //plynne zmienianie 839
			TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
			TIM_TimeBaseStructure.TIM_CounterMode =  TIM_CounterMode_Up;
			TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);

		TIM_Cmd(TIM5, ENABLE);

			    /* PWM1 Mode configuration: */
			 TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
			 TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
			 TIM_OCInitStructure.TIM_Pulse = 0;
			 TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

			 TIM_OC2Init(TIM5, &TIM_OCInitStructure);
			 TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);

			 TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
			 TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
			 TIM_OCInitStructure.TIM_Pulse = 0;
			 TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

			 TIM_OC3Init(TIM5, &TIM_OCInitStructure);
			 TIM_OC3PreloadConfig(TIM5, TIM_OCPreload_Enable);


			GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM5);
			GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_TIM5);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 |GPIO_Pin_2;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
			GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void Init_Engine()
{
	        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
			GPIO_Init(GPIOD, &GPIO_InitStructure);
			GPIO_SetBits(GPIOD, GPIO_Pin_13 | GPIO_Pin_14);
			GPIO_ResetBits(GPIOD, GPIO_Pin_12| GPIO_Pin_15);
}

void EXTI0_IRQHandler(void)
{    if(EXTI_GetITStatus(EXTI_Line0) != RESET)
	{
	TIM_Cmd(TIM3, ENABLE);
	EXTI_ClearITPendingBit(EXTI_Line0);
	}
}
void TIM3_IRQHandler(void)
		 {
		              if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
		              {

						 if(stan){

							 GPIO_ResetBits(GPIOA, GPIO_Pin_3);
							 stan=0;
						 }
						 else {
							 GPIO_SetBits(GPIOA, GPIO_Pin_3);
							 stan=1;
						}

		            	  TIM_Cmd(TIM3, DISABLE);
		            	  TIM_SetCounter(TIM3, 0);
		                     // wyzerowanie flagi wyzwolonego przerwania
		                     TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
		              }
		 }

void Init_Buttom()
{
	    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

		TIM_TimeBaseStructure.TIM_Period = 1999;
		TIM_TimeBaseStructure.TIM_Prescaler = 8399;
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;       //2Hz
		TIM_TimeBaseStructure.TIM_CounterMode =  TIM_CounterMode_Up;
		TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

		NVIC_InitTypeDef NVIC_InitStructure;
		NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
				 				 // priorytet g��wny
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
				 				 // subpriorytet
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
				 				 // uruchom dany kana�
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
				 				 // zapisz wype�nion� struktur� do rejestr�w
		NVIC_Init(&NVIC_InitStructure);
				 				 // wyczyszczenie przerwania od timera 4 (wyst�pi�o przy konfiguracji timera)
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
				 				 // zezwolenie na przerwania od przepe�nienia dla timera 4
		TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

		GPIO_InitTypeDef  GPIO_InitStructure;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;		//plytka
		GPIO_Init(GPIOA, &GPIO_InitStructure);



			// numer przerwania
			NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
			// priorytet g��wny
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
			// subpriorytet
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
			// uruchom dany kana�
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
			// zapisz wype�nion� struktur� do rejestr�w
			NVIC_Init(&NVIC_InitStructure);


			 EXTI_InitTypeDef EXTI_InitStructure;
			 // wyb�r numeru aktualnie konfigurowanej linii przerwa�
			 EXTI_InitStructure.EXTI_Line = EXTI_Line0;
			 // wyb�r trybu - przerwanie b�d� zdarzenie
			 EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
			 // wyb�r zbocza, na kt�re zareaguje przerwanie
			 EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
			 // uruchom dan� lini� przerwa�
			 EXTI_InitStructure.EXTI_LineCmd = ENABLE;
			 // zapisz struktur� konfiguracyjn� przerwa� zewn�trznych do rejestr�w
			 EXTI_Init(&EXTI_InitStructure);


			 SYSCFG_EXTILineConfig(GPIOA, EXTI_PinSource0);


			 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
			 			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
			 			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
			 			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
			 			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
			 			GPIO_Init(GPIOA, &GPIO_InitStructure);

}

void Init_bluetooth()
{
	// wlaczenie taktowania wybranego portu
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
		// wlaczenie taktowania wybranego uk�adu USART
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);



		// konfiguracja linii Rx i Tx
		GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOC, &GPIO_InitStructure);
		// ustawienie funkcji alternatywnej dla pin�w (USART)
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_USART3);
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_USART3);

		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

		USART_InitTypeDef USART_InitStructure;

		// predkosc transmisji (mozliwe standardowe opcje: 9600, 19200, 38400, 57600, 115200, ...)
		USART_InitStructure.USART_BaudRate = 9600;
		// d�ugo�� s�owa (USART_WordLength_8b lub USART_WordLength_9b)
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		// liczba bit�w stopu (USART_StopBits_1, USART_StopBits_0_5, USART_StopBits_2, USART_StopBits_1_5)
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		// sprawdzanie parzysto�ci (USART_Parity_No, USART_Parity_Even, USART_Parity_Odd)
		USART_InitStructure.USART_Parity = USART_Parity_No;
		// sprz�towa kontrola przep�ywu (USART_HardwareFlowControl_None, USART_HardwareFlowControl_RTS, USART_HardwareFlowControl_CTS, USART_HardwareFlowControl_RTS_CTS)
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		// tryb nadawania/odbierania (USART_Mode_Rx, USART_Mode_Rx )
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

		// konfiguracja
		USART_Init(USART3, &USART_InitStructure);

		// wlaczenie ukladu USART
		USART_Cmd(USART3, ENABLE);

		NVIC_InitTypeDef NVIC_InitStructure;
		// wlaczenie przerwania zwi�zanego z odebraniem danych (pozostale zrodla przerwan zdefiniowane sa w pliku stm32f4xx_usart.h)
		USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
		NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		// konfiguracja kontrolera przerwan
		NVIC_Init(&NVIC_InitStructure);
		// wlaczenie przerwan od ukladu USART
		NVIC_EnableIRQ(USART3_IRQn);

}

int main(void)
{
	SystemInit();

	Init_Time_engine();
	Init_Engine();
	Init_Buttom();
	Init_bluetooth();




    while(1)
    {

	//plynne zmienianie
    	i++;
    	for(j=0;j<10000000;j++){}
    	TIM5->CCR2 =20;
    	TIM5->CCR3 =20;
    	//for(j=0;j<10000;j++){}
    	//TIM5->CCR3 =k;
    	//for(j=0;j<1000;j++){}
    	//TIM5->CCR4 =l;
    }
}
