
#include "sys_setup.h"
#include "stm32f4xx.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_dac.h"
#include "stm32f4xx_adc.h"
#include "stm32f4xx_spi.h"


void setup_gpio(){
#if isUsingDevBoard







		/* Enable GPIO clock */
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);

		/* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */

		GPIO_InitTypeDef  GPIO_InitStructure;

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_Init(GPIOH, &GPIO_InitStructure);

		/* Connect PXx to USARTx_Tx*/
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_UART4);

		/* Connect PXx to USARTx_Rx*/
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_UART4);

		/* Configure USART Tx as alternate function  */
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);

		/* Configure USART Rx as alternate function  */
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
		GPIO_Init(GPIOA, &GPIO_InitStructure);


		//Configure DAC
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5; 	//DAC Channel 1, A4
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_Init(GPIOA, &GPIO_InitStructure);

		//Configure ADC
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_Init(GPIOC, &GPIO_InitStructure);

		//configure SPI for LCD

		GPIO_PinAFConfig(GPIOI, GPIO_PinSource1, GPIO_AF_SPI2);
		GPIO_PinAFConfig(GPIOI, GPIO_PinSource3, GPIO_AF_SPI2);

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_3;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;


		GPIO_Init(GPIOI, &GPIO_InitStructure);


		//configure other pins for LCD

		//Set the parallel/serial pin

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOF, &GPIO_InitStructure);

		GPIO_ResetBits(GPIOF, GPIO_Pin_15);	//Sets LCD screen to operate in serial

		//set CS1 pin
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;

		GPIO_Init(GPIOG, &GPIO_InitStructure);

		GPIO_SetBits(GPIOG, GPIO_Pin_1);

		//Set A0

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;

		GPIO_Init(GPIOF, &GPIO_InitStructure);

		//Set Reset

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;

		GPIO_Init(GPIOG, &GPIO_InitStructure);

		GPIO_SetBits(GPIOG, GPIO_Pin_0);






#else

#endif

}

void setup_uart(){

#if isUsingDevBoard

		USART_InitTypeDef USART_InitStructure;
		/* Enable UART clock */
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);

		USART_InitStructure.USART_BaudRate = 9600;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

		/* USART configuration */
		USART_Init(UART4, &USART_InitStructure);

		/* Enable USART */
		USART_Cmd(UART4, ENABLE);

#else

#endif


}

void setup_dac(){

#if isUsingDevBoard

	//Setup GPIO
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);

	DAC_InitTypeDef DAC_InitStructure;

	/* DAC channel1 Configuration */
	DAC_InitStructure.DAC_Trigger = DAC_Trigger_None;
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bits10_0;
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
	DAC_Init(DAC_Channel_1, &DAC_InitStructure);
	DAC_Init(DAC_Channel_2, &DAC_InitStructure);

	/* Enable DAC Channel1 */
	DAC_Cmd(DAC_Channel_1, ENABLE);
	DAC_Cmd(DAC_Channel_2, ENABLE);

	/* Set DAC Channel1 DHR12L register */
	DAC_SetChannel1Data(DAC_Align_8b_R, 0x0000);
	DAC_SetChannel2Data(DAC_Align_8b_R, 0x0000);



#else

#endif

}

void setup_adc(){
#if isUsingDevBoard

	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);

	  ADC_InitTypeDef       ADC_InitStructure;
	  ADC_CommonInitTypeDef ADC_CommonInitStructure;

	  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div8;
	  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;

	  ADC_CommonInit(&ADC_CommonInitStructure);

	  ADC_InitStructure.ADC_Resolution = ADC_Resolution_8b;
	  ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
	  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	  ADC_InitStructure.ADC_NbrOfConversion = 1;
	  ADC_Init(ADC2, &ADC_InitStructure);


	  ADC_RegularChannelConfig(ADC2, ADC_Channel_14, 1, ADC_SampleTime_3Cycles);

	  ADC_Cmd(ADC2, ENABLE);





#else

#endif



}

void setup_SPI(){

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

	SPI_I2S_DeInit(SPI2);

	SPI_InitTypeDef  SPI_InitStructure;


	  SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;	//Two serial lines only
	  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;			//8 bit transfers
	  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;				//Idle high clock
	  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;				//rising edge transfer
	  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;					//Software SS
	  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;	//Use 10.5 MHz clock
	  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;		//MSB first
	  SPI_InitStructure.SPI_CRCPolynomial = 7;					//Some value?
	  /* Initializes the SPI communication */
	  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;				//master mode
	  SPI_Init(SPI2, &SPI_InitStructure);						//init

	  SPI_Cmd(SPI2, ENABLE);


}


