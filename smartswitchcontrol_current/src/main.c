/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32l1xx.h"
#include <string.h>
#include "Utilities.h"
#include "uart.h"
#include "bitbanding.h"
#include "stdlib.h"
#include <strings.h>
#include <math.h>
//#define DMA_
#define DAC_
//#define TIM_
#define L100
//#define L152

#ifdef L152
#define green_led_set GPIO_SetBits(GPIOB, GPIO_Pin_7)
#define blue_led_set GPIO_SetBits(GPIOB, GPIO_Pin_6)
#define green_led_reset GPIO_ResetBits(GPIOB, GPIO_Pin_7)
#define blue_led_reset GPIO_ResetBits(GPIOB, GPIO_Pin_6)
#define green_led_toggle GPIO_ToggleBits(GPIOB, GPIO_Pin_7)
#define blue_led_toggle GPIO_ToggleBits(GPIOB, GPIO_Pin_6)
#endif

#ifdef L100
#define green_led_set GPIO_SetBits(GPIOC, GPIO_Pin_9)
#define blue_led_set GPIO_SetBits(GPIOC, GPIO_Pin_8)
#define green_led_reset GPIO_ResetBits(GPIOC, GPIO_Pin_9)
#define blue_led_reset GPIO_ResetBits(GPIOC, GPIO_Pin_8)
#define green_led_toggle GPIO_ToggleBits(GPIOC, GPIO_Pin_9)
#define blue_led_toggle GPIO_ToggleBits(GPIOC, GPIO_Pin_8)
#endif

void clear_buff();
void USART2_IRQHandler();
void command_splitter();
void command_handler();
void set_code(char* mass);
void dtb(int x, char* ch);
void meas_sender();
void clear_meas();
int ADC_Tim_Conf(int freq);
int Exp_Tim_Conf(int time);
void GetADC();

#define buf_size 6000
unsigned char usartData;
char buff[512]; //Буфер для приёма сообщения.
char command[512];
char argument[512];
//uint16_t buf_size = 3000;
uint16_t meas_res[buf_size];
int q = 0;
int pins [7];
unsigned char usart_bit=0; //Номер байта UART принимаемого в буфер.
char flag = 0;
unsigned char string = 'A';
int num=0;
int radix = 10;  //система счисления
char buffer[1000]; //результат
char *p;  //указатель на результат
uint32_t time=1000;
uint32_t ADC_Result;
uint32_t ADC_Result2;
const uint16_t sine[32] = {2047, 2447, 2831, 3185, 3498, 3750, 3939, 4056, 4095, 4056,
3939, 3750, 3495, 3185, 2831, 2447, 2047, 1647, 1263, 909,
599, 344, 155, 38, 0, 38, 155, 344, 599, 909, 1263, 1647};
int h=0;
uint32_t ADC_Freq = 1600000;
uint32_t DAC_Freq = 100;


			

int main(void)
{
	SystemInit();
	DWT_Init();

	ADC_InitTypeDef ADC_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
#ifdef DMA_
	DMA_InitTypeDef DMA_InitStructure;
#endif
	TIM_TimeBaseInitTypeDef Trig_TIMInitStructure;
    GPIO_InitTypeDef  GPIO_InitStructure;


	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10, ENABLE);


	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);


    // настроили ногу АЦП и ЦАП

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // настроили ноги на дерганья ключом и светодиодами
#ifdef L152
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   	GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   	GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   	GPIO_Init(GPIOC, &GPIO_InitStructure);
#endif

#ifdef L100
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   	GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   	GPIO_Init(GPIOC, &GPIO_InitStructure);
#endif
#ifdef TIM_
   	//таймер, вместо DAC
   	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
   	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
   	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
   	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   	GPIO_Init(GPIOB, &GPIO_InitStructure);

   	GPIO_PinAFConfig(GPIOB, GPIO_PinSource12, GPIO_AF_TIM10);

    Trig_TIMInitStructure.TIM_Prescaler = 32;
    Trig_TIMInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    Trig_TIMInitStructure.TIM_Period = 20;
    Trig_TIMInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;

    TIM_SelectOCxM(TIM10, TIM_Channel_1, TIM_OCMode_Toggle);
    TIM_TimeBaseInit(TIM10, &Trig_TIMInitStructure);
    TIM_CCxCmd(TIM10, TIM_Channel_1, TIM_CCx_Enable);
    TIM_Cmd(TIM10, ENABLE);
#endif


   	// настроили ноги Rx и Tx

   	GPIO_InitTypeDef A_Config;
   	A_Config.GPIO_Mode = GPIO_Mode_AF;
   	A_Config.GPIO_Pin = GPIO_Pin_2;
   	A_Config.GPIO_Speed = GPIO_Speed_10MHz;

   	GPIO_Init(GPIOA, &A_Config);
   	GPIO_PinAFConfig( GPIOA, GPIO_PinSource2, GPIO_AF_USART2);

   	A_Config.GPIO_Mode = GPIO_Mode_AF;
   	A_Config.GPIO_Pin = GPIO_Pin_3;
   	A_Config.GPIO_Speed = GPIO_Speed_10MHz;

   	GPIO_Init(GPIOA, &A_Config);
   	GPIO_PinAFConfig( GPIOA, GPIO_PinSource3, GPIO_AF_USART2);



#ifdef DMA_

    // Настройки DMA
    DMA_DeInit(DMA1_Channel1);
    // Данные будем брать из регистра данных ADC1
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&(ADC1->DR);
    // Переправлять данные будем в переменную
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)ADC_Result2;
    // Передача данных из периферии в память
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = 1;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    // Настройки размера данных
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);

    // Включаем первый канал DMA1
    DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE);
    DMA_ClearFlag(DMA1_FLAG_TC1);
    DMA_ClearFlag(DMA1_FLAG_GL1);
    DMA_ClearFlag(DMA1_FLAG_HT1);
    DMA_ClearFlag(DMA1_FLAG_TE1);
    NVIC_EnableIRQ(DMA1_Channel1_IRQn);

#endif
    // настроили АЦП
    // настроили тактированиe?
    ADC_CommonStructInit(&ADC_CommonInitStructure);
    ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
    ADC_CommonInit(&ADC_CommonInitStructure);

    ADC_StructInit(&ADC_InitStructure);
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_Rising;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T3_TRGO;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfConversion = 1;

    ADC_Init(ADC1, &ADC_InitStructure);
    ADC_BankSelection(ADC1, ADC_Bank_A);
//    ADC_SoftwareStartConv(ADC1);
//    ADC_DiscModeChannelCountConfig(ADC1,1);
//    ADC_PowerDownCmd(ADC1, ADC_PowerDown_Idle, ENABLE);
#ifndef DMA_
//    //прерывание по окончанию преобразования
    ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);
    NVIC_EnableIRQ(ADC1_IRQn);
#endif

    // Включаем первый канал первого модуля АЦП
    ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_4Cycles);
    ADC_Cmd(ADC1, ENABLE);


#ifdef DMA_
    // Включаем работу ДМА через АЦП
    ADC_DMACmd(ADC1, ENABLE);
    ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);
//    ADC_DelaySelectionConfig(ADC1, ADC_DelayLength_7Cycles);

#endif

    // настроили таймер-триггер ADC

    Trig_TIMInitStructure.TIM_Prescaler = 0;
    Trig_TIMInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    Trig_TIMInitStructure.TIM_Period = 10;
    Trig_TIMInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;

    TIM_SelectOutputTrigger(TIM3,TIM_TRGOSource_Update);
    TIM_TimeBaseInit(TIM3, &Trig_TIMInitStructure);
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    TIM_GenerateEvent(TIM3, TIM_EventSource_Update);
    TIM_ClearFlag(TIM3, TIM_FLAG_Update);

#ifdef DAC_
    DAC_InitTypeDef   DACch1;
    DAC_StructInit(&DACch1);
    /* Reset DAC configuration */
    DAC_DeInit();

    /* Configure DAC */
    DACch1.DAC_Trigger = DAC_Trigger_T6_TRGO;
    DACch1.DAC_WaveGeneration = DAC_WaveGeneration_None;
    DACch1.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bits2_0;
    DACch1.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
    /* DAC channel 1 configuration*/
    DAC_Init( DAC_Channel_1, &DACch1 );
    /* Enable DAC channel 1       */
    DAC_Cmd( DAC_Channel_1, ENABLE);


    //таймер DAC
    Trig_TIMInitStructure.TIM_Prescaler = 16;
    Trig_TIMInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    Trig_TIMInitStructure.TIM_Period = 10;
    Trig_TIMInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;

    TIM_SelectOutputTrigger(TIM6,TIM_TRGOSource_Update);
    TIM_TimeBaseInit(TIM6, &Trig_TIMInitStructure);
    TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);
    TIM_GenerateEvent(TIM6, TIM_EventSource_Update);
    TIM_ClearFlag(TIM6, TIM_FLAG_Update);
    NVIC_EnableIRQ(TIM6_IRQn);
    TIM_Cmd(TIM6, ENABLE);
#endif

//    NVIC_EnableIRQ(TIM3_IRQn); // Разрешаем прерывание
//    TIM_Cmd(TIM3, ENABLE);     // Включаем таймер

//    delay_ms(500);

	// таймер для экспозиции
    Trig_TIMInitStructure.TIM_Prescaler = 32;
    Trig_TIMInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    Trig_TIMInitStructure.TIM_Period = 2000;
    Trig_TIMInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;

    TIM_SelectOutputTrigger(TIM2,TIM_TRGOSource_Update);
    TIM_TimeBaseInit(TIM2, &Trig_TIMInitStructure);
    TIM_SelectOnePulseMode(TIM2, TIM_OPMode_Single);
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    TIM_GenerateEvent(TIM2, TIM_EventSource_Update);
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);
    NVIC_EnableIRQ(TIM2_IRQn);

	// настроили USART

	USART_InitTypeDef usart2;
	usart2.USART_BaudRate = 256000;
	usart2.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usart2.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
	usart2.USART_Parity = USART_Parity_No;
	usart2.USART_StopBits = USART_StopBits_1;
	usart2.USART_WordLength = USART_WordLength_8b;

	USART_Init(USART2, &usart2);


	NVIC_EnableIRQ(USART2_IRQn);
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    USART_Cmd(USART2, ENABLE);

	green_led_set;
	blue_led_set;
    clear_meas();
    clear_buff();
    DMA_Cmd(DMA1_Channel1, ENABLE);

	SEND_UART_STR(USART2, "INIT");

	GPIO_SetBits(GPIOA, GPIO_Pin_8);


	while (1)
	{

	}
}

void USART2_IRQHandler()
{
    //Проверяем, действительно ли прерывание вызвано приемом нового байта
    if (USART_GetITStatus(USART2, USART_IT_RXNE) == SET)
    {
//    	green_led_toggle;
		usartData = USART_ReceiveData(USART2);
		if (((usartData == 'n') && (buff[usart_bit-1] == 0x5C))||((usartData == 'r') && (buff[usart_bit-1] == 0x5C)))
		{
			buff[usart_bit-1] = 0;
			flag = 1;
		}
		else
			if ((usartData == 0x0D) || (usartData == 0x0A))
			{
				flag = 1;
			}
			else
			{
				buff[usart_bit] = usartData;
				usart_bit++;
			}

		if (flag == 1)
		{
			command_splitter();
//			SEND_UART_STR(USART2,buff);
			clear_buff();
			flag = 0;
		}
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
    }
}

void clear_buff()
{
	for (int i=0; i<512; i++)
	{
		buff[i] = 0;
		command[i] = 0;
		argument[i] = 0;
	}
	usart_bit = 0;
}

void clear_meas()
{
	for (int i=0; i<buf_size; i++)
	{
		meas_res[i] = 0;
//		meas_res[i] = 0;
	}
}

void command_splitter()
{
	uint8_t d;
	int command_end_pos=0;
	for (int i=0; i<=usart_bit; i++)
	{
		if (buff[i] == ' ')
		{
			command_end_pos = i;
			d = 1;
		}
		d = 0;
	}

	if (d==1)
	{
		for (int i=0; i<command_end_pos; i++)
		{
			command[i] = buff[i];
		}

		for (int j=command_end_pos+1; j<=usart_bit; j++)
		{
			argument[j-command_end_pos-1] = buff[j];
		}
	}
	else
		for (int i=0; i<=usart_bit; i++)
		{
			command[i] = buff[i];
		}
	command_handler();
}

void command_handler()
{
	if(!(strcmp(command,"start")))
	{
		time = atoi(argument);
		TIM_SetAutoreload(TIM2, time+700);
//		p = itoa(TIM2->ARR,buffer,radix);
//		SEND_UART_STR(USART2, p);
//		DMA_Cmd(DMA1_Channel1, ENABLE);
		TIM_Cmd(TIM3, ENABLE);
		TIM_Cmd(TIM2, ENABLE);
		return;
	}
	if (!(strcmp(command,"set")))
	{
		if(!(strcmp(argument,"blue")))
			blue_led_set;
		if(!(strcmp(argument,"green")))
			green_led_set;
		return;
	}

	if (!(strcmp(command,"reset")))
	{
		if(!(strcmp(argument,"blue")))
			blue_led_reset;
		if(!(strcmp(argument,"green")))
			green_led_reset;
		return;
	}

	if (!(strcmp(command,"toggle")))
	{
		if(!(strcmp(argument,"blue")))
			blue_led_toggle;
		if(!(strcmp(argument,"green")))
			green_led_toggle;
		return;
	}

	if (!(strcmp(command,"setup")))
	{
		set_code(argument);
		return;
	}

	if (!(strcmp(command,"setexp")))
	{
		time = atoi(argument);
		TIM_SetAutoreload(TIM2, Exp_Tim_Conf(time));
		return;
	}

	if (!(strcmp(command,"setfreq")))
	{
		time = atoi(argument);
#ifdef DAC_
		TIM_SetAutoreload(TIM6, time);
#endif
#ifdef TIM_
		TIM_SetAutoreload(TIM10, time);
#endif
		return;
	}

	if (!(strcmp(command,"setadc")))
	{
		time = atoi(argument);
		TIM_SetAutoreload(TIM3, ADC_Tim_Conf(time));
		return;
	}
	if (!(strcmp(command,"getadc")))
	{
		SEND_UART_STR(USART2, "geting adc...");
		GetADC();
		return;
	}
}

void set_code(char* mass)
{
    int c=atoi(mass);
    int ch1 = c/100;
    int c1=c%100;
    int ch2 = c1/10;
    int ch3 = c1%10;

    dtb(ch1,"left");
    dtb(ch2,"right");

#ifdef L152
    PortC_pin_6 = ch3;

    PortA_pin_10 = pins[0];
    PortA_pin_9 = pins[1];
    PortA_pin_8 = pins[2];

    PortC_pin_9 = pins[3];
    PortC_pin_8 = pins[4];
    PortC_pin_7 = pins[5];
#endif

#ifdef L100
    PortB_pin_13 = ch3;

    PortC_pin_9 = pins[2];
    PortC_pin_8 = pins[1];
    PortC_pin_7 = pins[0];

    PortC_pin_6 = pins[5];
    PortB_pin_15 = pins[4];
    PortB_pin_14 = pins[3];
#endif
}

void dtb(int x, char* ch)
{
    x-=1;
    int C=(x&4)>>2;
    C=!C;
    int B=(x&2)>>1;
    B=!B;
    int A=(x&1);
    A=!A;

    if (!(strcmp(ch,"left")))
    {
    	pins[0]=C;
    	pins[1]=B;
    	pins[2]=A;
    }

    if (!(strcmp(ch,"right")))
    {
    	pins[3]=C;
    	pins[4]=B;
    	pins[5]=A;
    }
}

void TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {

    	{
//    	blue_led_toggle;
    	TIM_Cmd(TIM3, DISABLE);

    	meas_sender();
#ifdef DMA_
//    	DMA_Cmd(DMA1_Channel1, DISABLE);
//    	DMA_SetCurrDataCounter(DMA1_Channel1, 3000);
//    	DMA_Cmd(DMA1_Channel1, ENABLE);
#endif

    	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    	}

    }
}

//void TIM3_IRQHandler(void)
//{
//    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
//    {
//    	{
////    	green_led_toggle;
//        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
//    	}
//    }
//}

void TIM6_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)
    {
    	{
    	DAC_SetChannel1Data(DAC_Align_12b_R , sine[h]);
    	h++;
    	if (h==32)
    		h=0;
    	TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
    	}
    }
}

#ifndef DMA_
void ADC1_IRQHandler()
{
	if (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) != RESET)
	{
		{
			meas_res[q] = ADC_GetConversionValue(ADC1);
			q++;
			ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);
		}
	}
}
#endif

void meas_sender()
{

#ifdef DMA_

	while (meas_res[q]!=0)
	{
//		meas_res[q]=(meas_res[q]&0xFFF);
		p = itoa(meas_res[q],buffer,radix);
		SEND_UART_STR(USART2, p);
		q++;
	}
#endif

#ifndef DMA_
	for (int i=0; i<q;i++)
	{
//		meas_res[q]=(meas_res[q]&0xFFF);
		p = itoa(meas_res[i],buffer,radix);
		SEND_UART_STR(USART2, p);
	}
#endif
//	for (int i=0; i<q;i++)
//	{
//		p = itoa(meas_res[i][1],buffer,radix);
//		SEND_UART_STR(USART2, p);
//	}
//	p = itoa(q,buffer,radix);
//	SEND_UART_STR(USART2, p);
	q=0;
	SEND_UART_STR(USART2, "end");
	clear_meas();
	green_led_toggle;
}
#ifdef DMA_
void DMA1_Channel1_IRQHandler()
{
	if (DMA_GetFlagStatus(DMA1_FLAG_TC1) != RESET)
	{
			p = itoa(ADC_Result2,buffer,radix);
			SEND_UART_STR(USART2, p);

	    	blue_led_toggle;
			ADC_Result = ADC_GetConversionValue(ADC1);


			p = itoa(ADC_Result,buffer,radix);
			SEND_UART_STR(USART2, p);

			DMA_ClearITPendingBit(DMA1_IT_TC1);
	}

			DMA_ClearITPendingBit(DMA1_IT_GL1);
			DMA_ClearITPendingBit(DMA1_IT_HT1);
			DMA_ClearITPendingBit(DMA1_IT_TE1);
}
#endif

int ADC_Tim_Conf(int freq)
{
	float per1 = SystemCoreClock/(2*(TIM3->PSC+1)*freq*1000);
	int per = ceil(per1);
	p = itoa(per1,buffer,radix);
	SEND_UART_STR(USART2, p);
	p = itoa(per,buffer,radix);
	SEND_UART_STR(USART2, p);
//	p = itoa(TIM3->PSC,buffer,radix);
//	SEND_UART_STR(USART2, p);
	return per;
}
int Exp_Tim_Conf(int time)
{
	int per1 = SystemCoreClock*time/((TIM2->PSC+1)*100000);
	int per = ceil(per1);
	return per;
}

void GetADC()
{
	SEND_UART_STR(USART2, "geting adc...");
	int per = SystemCoreClock/(2*(TIM3->PSC+1)*TIM3->ARR)/1000;
	p = itoa(per,buffer,radix);
	SEND_UART_STR(USART2, p);
}
