#include "stm32f4xx_tim.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_usart.h"
#include "tm_stm32f4_delay.h"
#include "tm_stm32f4_hcsr04.h"
#include "stm32f4xx.h"
#include <stdio.h>
#include "defines.h"
#include "misc.h"


int i=1;
int j=0;
int stan=0;
int odleglosc;

GPIO_InitTypeDef  GPIO_InitStructure;
TIM_OCInitTypeDef TIM_OCInitStructure;
TIM_ICInitTypeDef TIM_ICInitStructure;
TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
NVIC_InitTypeDef NVIC_InitStructure;
TM_HCSR04_t HCSR04;



int obrotR=0;
int obrotL=0;
int wartosc=0;
float speed;


void TIM3_IRQHandler(void)
		 {
		              if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
		              {

		            		TM_HCSR04_Read(&HCSR04);
		            		odleglosc=HCSR04.Distance;
		            		if(GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_14)==1)
		            		    	{
		            					if(odleglosc<20)
		            								{
		            									TIM9->CCR1 = 0;
		            									TIM9->CCR2 = 0;

		            								}
		            		    	}

		                 
		                     TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
		              }
		 }

void TIM5_IRQHandler(void)
		 {
		              if(TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)
		              {

		            	obrotL++;
		            	TIM_SetCounter(TIM5, 0);
		            
		                     TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
		              }
		 }

void TIM4_IRQHandler(void)
		 {
		              if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
		              {

		            	obrotR++;
		            	TIM_SetCounter(TIM4, 0);
		            
		                     TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
		              }
		 }

void USART3_IRQHandler(void)
{

if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
{
		while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
		char a=USART3->DR;

		switch( a )
		    {
		    case 'a':
		    	GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
		    				GPIO_SetBits(GPIOD, GPIO_Pin_13);
		    				GPIO_SetBits(GPIOD,GPIO_Pin_15);
		    				TIM9->CCR1 = speed;
		    				TIM9->CCR2 = speed;
		        break;
		    case 'w':
		    	GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
		    				GPIO_SetBits(GPIOD,GPIO_Pin_13);
		    				GPIO_SetBits(GPIOD,GPIO_Pin_14);
		    				TIM9->CCR1 = speed;
		    				TIM9->CCR2 = speed;
		        break;
		    case 'd':
		    	GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
		    				GPIO_SetBits(GPIOD,GPIO_Pin_14);
		    				GPIO_SetBits(GPIOD,GPIO_Pin_12);
		    				TIM9->CCR1 = speed;
		    				TIM9->CCR2 = speed;
		        break;
		    case 's':
		    	GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
		    				GPIO_SetBits(GPIOD,GPIO_Pin_15);
		    				GPIO_SetBits(GPIOD,GPIO_Pin_12);
		    				TIM9->CCR1 = speed;
		    				TIM9->CCR2 = speed;
		   		break;
		    case 'q':
		    	GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
		    				GPIO_SetBits(GPIOD,GPIO_Pin_13);
		    				GPIO_SetBits(GPIOD,GPIO_Pin_14);
		    				TIM9->CCR1 = speed;
		    			    TIM9->CCR2 = 0;
		  		break;
		    case 'e':
		    	GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
		    				GPIO_SetBits(GPIOD,GPIO_Pin_13);
		    				GPIO_SetBits(GPIOD,GPIO_Pin_14);
		    				TIM9->CCR2 = speed;
		    				TIM9->CCR1 = 0;
		    	break;
		    case 'z':
		    	GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
		    				GPIO_SetBits(GPIOD,GPIO_Pin_15);
		    				GPIO_SetBits(GPIOD,GPIO_Pin_12);
		    				TIM9->CCR1 = speed;
		    			    TIM9->CCR2 = 0;
		    	break;
		    case 'x':
		    	GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
		    				GPIO_SetBits(GPIOD,GPIO_Pin_15);
		    				TIM9->CCR2 = speed;
		    				TIM9->CCR1 = 0;
		   		break;
		    case 'r':
		    	GPIO_SetBits(GPIOA, GPIO_Pin_3);
		    	break;
		    case 'g':
		    	GPIO_ResetBits(GPIOA, GPIO_Pin_3);
		  		break;
		    case 'b':
		    	TIM9->CCR1 = 0;
		    	TIM9->CCR2 = 0;
		   		break;
		    default:
		    	speed = (a-'0');
		    	TIM9->CCR1 = speed;
		    	TIM9->CCR2 = speed;
		        break;
		    }
		while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
}
}


void Init_Time_engine()
{
	    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);
	    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

			GPIO_ResetBits(GPIOA, GPIO_Pin_3);
		   	TIM_TimeBaseStructure.TIM_Period = 10; 
			TIM_TimeBaseStructure.TIM_Prescaler = 167; 
			TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
			TIM_TimeBaseStructure.TIM_CounterMode =  TIM_CounterMode_Up;
			TIM_TimeBaseInit(TIM9, &TIM_TimeBaseStructure);

		TIM_Cmd(TIM9, ENABLE);


			 TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
			 TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
			 TIM_OCInitStructure.TIM_Pulse = 0;
			 TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

			 TIM_OC2Init(TIM9, &TIM_OCInitStructure);
			 TIM_OC2PreloadConfig(TIM9, TIM_OCPreload_Enable);

			 TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
			 TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
			 TIM_OCInitStructure.TIM_Pulse = 0;
			 TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

			 TIM_OC1Init(TIM9, &TIM_OCInitStructure);
			 TIM_OC1PreloadConfig(TIM9, TIM_OCPreload_Enable);


			GPIO_PinAFConfig(GPIOE, GPIO_PinSource5, GPIO_AF_TIM9);
			GPIO_PinAFConfig(GPIOE, GPIO_PinSource6, GPIO_AF_TIM9);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 |GPIO_Pin_6;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
			GPIO_Init(GPIOE, &GPIO_InitStructure);
}

void Init_Engine()
{

	        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);


	        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	       	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	       	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	       	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	       	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	       	GPIO_Init(GPIOA, &GPIO_InitStructure);

			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
			GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
			GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
			GPIO_Init(GPIOD, &GPIO_InitStructure);
			GPIO_SetBits(GPIOD, GPIO_Pin_13 | GPIO_Pin_14);
			GPIO_ResetBits(GPIOD, GPIO_Pin_12| GPIO_Pin_15);
}

void Init_bluetooth()
{

		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);



	
		GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOC, &GPIO_InitStructure);
		
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_USART3);
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_USART3);

		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

		USART_InitTypeDef USART_InitStructure;

	
		USART_InitStructure.USART_BaudRate = 9600;
		
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
	
		USART_InitStructure.USART_Parity = USART_Parity_No;
	
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

		
		USART_Init(USART3, &USART_InitStructure);

		
		USART_Cmd(USART3, ENABLE);

		NVIC_InitTypeDef NVIC_InitStructure;
		
		USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
		NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		
		NVIC_Init(&NVIC_InitStructure);
	
		NVIC_EnableIRQ(USART3_IRQn);

}

void Init_EncoderR()
{


	   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	   RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	   GPIO_InitTypeDef GPIO_InitStructure;
	   TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	   TIM_ICInitTypeDef  TIM_ICInitStructure;
	   NVIC_InitTypeDef NVIC_InitStructure;



	    GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM5);
	    GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM5);
	    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 |GPIO_Pin_1;
	    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	    GPIO_Init(GPIOA, &GPIO_InitStructure);

	    TIM_TimeBaseStructure.TIM_Prescaler     = 0;
	    TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up;
	    TIM_TimeBaseStructure.TIM_Period        = 3840;
	    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);

	    TIM_ICStructInit(&TIM_ICInitStructure);
	    TIM_ICInitStructure.TIM_Channel     = TIM_Channel_1;
	    TIM_ICInitStructure.TIM_ICPolarity  = TIM_ICPolarity_Rising;
	    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	    TIM_ICInitStructure.TIM_ICFilter    = 15;
	    TIM_ICInit(TIM5, &TIM_ICInitStructure);

	
	    TIM_ICInitStructure.TIM_Channel     = TIM_Channel_2;
	    TIM_ICInit(TIM5, &TIM_ICInitStructure);

	    TIM_EncoderInterfaceConfig(TIM5, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);

	   	TIM_SetCounter(TIM5, 0);

			   	TIM_Cmd(TIM5,ENABLE);


			   			NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
			   					 				
			   			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
			   			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
			   			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
			   			NVIC_Init(&NVIC_InitStructure);
			   			TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
			   			TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);

}

void Init_EncoderL()
{


	       RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
		   RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
		   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
		   GPIO_InitTypeDef GPIO_InitStructure;
		   TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		   TIM_ICInitTypeDef  TIM_ICInitStructure;
		   NVIC_InitTypeDef NVIC_InitStructure;



		    GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_TIM4);
		    GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_TIM4);
		    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 |GPIO_Pin_7;
		    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
		    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		    GPIO_Init(GPIOB, &GPIO_InitStructure);

		    TIM_TimeBaseStructure.TIM_Prescaler     = 0;
		    TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up;
		    TIM_TimeBaseStructure.TIM_Period        = 3840;
		    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
		    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
		    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

		    TIM_ICStructInit(&TIM_ICInitStructure);
		    TIM_ICInitStructure.TIM_Channel     = TIM_Channel_1;
		    TIM_ICInitStructure.TIM_ICPolarity  = TIM_ICPolarity_Rising;
		    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
		    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
		    TIM_ICInitStructure.TIM_ICFilter    = 15;
		    TIM_ICInit(TIM4, &TIM_ICInitStructure);

		    TIM_ICInitStructure.TIM_Channel     = TIM_Channel_2;
		    TIM_ICInit(TIM4, &TIM_ICInitStructure);

		    TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);

		   	TIM_SetCounter(TIM4, 0);

				   	TIM_Cmd(TIM4,ENABLE);


				   			NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
				   			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
				   			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
				   			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
				   			NVIC_Init(&NVIC_InitStructure);
				   			TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
				   			TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);

}

void Init_Servo(void) {

    GPIO_InitTypeDef            GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef     TIM_TimeBaseStructure;
    TIM_OCInitTypeDef           TIM_OCInitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13, ENABLE);


    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

    GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_100MHz;   
    GPIO_InitStructure.GPIO_OType   = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd    = GPIO_PuPd_UP;         
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_TIM13);



    TIM_TimeBaseStructure.TIM_Period        = 1999;
    TIM_TimeBaseStructure.TIM_Prescaler     = 839;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM13, &TIM_TimeBaseStructure);

    TIM_OCInitStructure.TIM_OCMode      = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse       = 0;                       
    TIM_OCInitStructure.TIM_OCPolarity  = TIM_OCPolarity_High;


    TIM_OC1Init(TIM13, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM13, TIM_OCPreload_Enable);


    TIM_ARRPreloadConfig(TIM13, ENABLE);


    TIM_Cmd(TIM13, ENABLE);
}

void Init_HCSR04()
{


	TM_DELAY_Init();


	TM_HCSR04_Init(&HCSR04, GPIOD, GPIO_PIN_0, GPIOC, GPIO_PIN_1);
	

	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);


			TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
			TIM_TimeBaseStructure.TIM_Period = 999;
				TIM_TimeBaseStructure.TIM_Prescaler = 8399;
				TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;      
				TIM_TimeBaseStructure.TIM_CounterMode =  TIM_CounterMode_Up;
				TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

			TIM_Cmd(TIM3, ENABLE);



				 NVIC_InitTypeDef NVIC_InitStructure;
				
				 NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
				
				 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
				
				 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
				
				 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
				
				 NVIC_Init(&NVIC_InitStructure);


			
				 TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
				
				 TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);



}


int main(void)
{
	SystemInit();

	Init_Time_engine();
	Init_Engine();
	Init_bluetooth();
	Init_EncoderL();
	Init_EncoderR();
	Init_Servo();
	Init_HCSR04();






    while(1)
    {

    }
}
