/**
 ******************************************************************************
 *  @attention
 *
 *  All Rights Reserved
 *  Copyright (C) 2023  Henry Odoemelem <hodoemelem@gmail.com>
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *  THE SOFTWARE.
 *******************************************************************************
 */

#include "io.h"

GPIO_MODER_t GPIO_MODER[PORT_END] = {
	{.bytes = &GPIOA->MODER},
	{.bytes = &GPIOB->MODER},
	{.bytes = &GPIOC->MODER},
};

GPIO_BSRR_t GPIO_BSRR[PORT_END] = {
	{.bytes = &GPIOA->BSRR},
	{.bytes = &GPIOB->BSRR},
	{.bytes = &GPIOC->BSRR},
};
GPIO_OTYPER_t GPIO_OTYPER[PORT_END] = {
	{.bytes = &GPIOA->OTYPER},
	{.bytes = &GPIOB->OTYPER},
	{.bytes = &GPIOC->OTYPER},
};
GPIO_AFR_t GPIO_AFR[PORT_END * 2] = {
	{.bytes = &GPIOA->AFR[0]},
	{.bytes = &GPIOB->AFR[0]},
	{.bytes = &GPIOC->AFR[0]},
	{.bytes = &GPIOA->AFR[1]},
	{.bytes = &GPIOB->AFR[1]},
	{.bytes = &GPIOC->AFR[1]},
};

RCC_AHB2ENR_t RCC_AHB2ENR = {
	.bytes = &RCC->AHB2ENR,
};

RCC_APB1ENR1_t RCC_APB1ENR1 = {
	.bytes = &RCC->APB1ENR1,
};
RCC_APB2ENR_t RCC_APB2ENR = {
	.bytes = &RCC->APB2ENR};
RCC_AHB1ENR_t RCC_AHB1ENR = {
	.bytes = &RCC->AHB1ENR};
USART_BRR_t USART_BRR[PORT_END] = {
	{.bytes = &USART1->BRR},
	{.bytes = &USART2->BRR},
	{.bytes = &USART3->BRR},
};
USART_CR1_t USART_CR1[PORT_END] = {
	{.bytes = &USART1->CR1},
	{.bytes = &USART2->CR1},
	{.bytes = &USART3->CR1},
};

USART_ISR_t USART_ISR[PORT_END] = {
	{.bytes = &USART1->ISR},
	{.bytes = &USART2->ISR},
	{.bytes = &USART3->ISR},
};

USART_TDR_t USART_TDR[PORT_END] = {
	{.bytes = &USART1->TDR},
	{.bytes = &USART2->TDR},
	{.bytes = &USART3->TDR},
};

USART_RDR_t USART_RDR[PORT_END] = {
	{.bytes = &USART1->RDR},
	{.bytes = &USART2->RDR},
	{.bytes = &USART3->RDR},
};
I2C_TIMINGR_t I2C_TIMINGR[PORT_END] = {
	{.I_TIMINGR = &I2C1->TIMINGR},
	{.I_TIMINGR = &I2C2->TIMINGR},
};

I2C_TXDR_t I2C_TXDR[PORT_END] = {
	{.TXDATA = &I2C1->TXDR},
	{.TXDATA = &I2C2->TXDR},
};
I2C_RXDR_t I2C_RXDR[PORT_END] = {
	{.RXDATA = &I2C1->RXDR},
	{.RXDATA = &I2C2->RXDR},
};
I2C_CR1_t I2C_CR1[PORT_END] = {
	{.bytes = &I2C1->CR1},
	{.bytes = &I2C2->CR1},
};
I2C_CR2_t I2C_CR2[PORT_END] = {
	{.bytes = &I2C1->CR2},
	{.bytes = &I2C2->CR2},
};

I2C_ISR_t I2C_ISR[PORT_END] = {
	{.bytes = &I2C1->ISR},
	{.bytes = &I2C2->ISR},
};

DMA1_Channel_CCR_t DMA1_Channel_CCR[6] = {
	{.bytes = &DMA1_Channel1->CCR},
	{.bytes = &DMA1_Channel2->CCR},
	{.bytes = &DMA1_Channel3->CCR},
	{.bytes = &DMA1_Channel4->CCR},
	{.bytes = &DMA1_Channel5->CCR},
	{.bytes = &DMA1_Channel6->CCR},
};
USART_CR3_t USART_CR3[PORT_END] = {
	{.bytes = &USART1->CR3},
	{.bytes = &USART2->CR3},
	{.bytes = &USART3->CR3},
};
DMA1_Channel_CSELR_t DMA1_Channel_CSELR = {
	.bytes = &DMA1_CSELR->CSELR};
DMA1_Channel_CPAR_t DMA1_Channel_CPAR[6] = {
	{.bytes = &DMA1_Channel1->CPAR},
	{.bytes = &DMA1_Channel2->CPAR},
	{.bytes = &DMA1_Channel3->CPAR},
	{.bytes = &DMA1_Channel4->CPAR},
	{.bytes = &DMA1_Channel5->CPAR},
	{.bytes = &DMA1_Channel6->CPAR},
};
DMA1_Channel_CMAR_t DMA1_Channel_CMAR[6] = {
	{.bytes = &DMA1_Channel1->CMAR},
	{.bytes = &DMA1_Channel2->CMAR},
	{.bytes = &DMA1_Channel3->CMAR},
	{.bytes = &DMA1_Channel4->CMAR},
	{.bytes = &DMA1_Channel5->CMAR},
	{.bytes = &DMA1_Channel6->CMAR},
};
DMA1_Channel_CNDTR_t DMA1_Channel_CNDTR[6] = {
	{.bytes = &DMA1_Channel1->CNDTR},
	{.bytes = &DMA1_Channel2->CNDTR},
	{.bytes = &DMA1_Channel3->CNDTR},
	{.bytes = &DMA1_Channel4->CNDTR},
	{.bytes = &DMA1_Channel5->CNDTR},
	{.bytes = &DMA1_Channel6->CNDTR},
};

DMA_IFCR_t DMA_IFCR = {
	.bytes = &DMA1->IFCR};

DMA_ISR_t DMA_ISR = {
	.bytes = &DMA1->ISR};

TIM_CR1_t TIM_CR1[3] = {
	{.bytes = &TIM1->CR1},
	{.bytes = &TIM2->CR1},
	{.bytes = &TIM3->CR1},
};
TIM_CCR1_t TIM_CCR1[3] = {
	{.bytes = &TIM1->CCR1},
	{.bytes = &TIM2->CCR1},
	{.bytes = &TIM3->CCR1},
};
TIM_CCR2_t TIM_CCR2[3] = {
	{.bytes = &TIM1->CCR2},
	{.bytes = &TIM2->CCR2},
	{.bytes = &TIM3->CCR2},
};
TIM_EGR_t TIM_EGR[3] = {
	{.bytes = &TIM1->EGR},
	{.bytes = &TIM2->EGR},
	{.bytes = &TIM3->EGR},
};
TIM_PSC_t TIM_PSC[3] = {
	{.bytes = &TIM1->PSC},
	{.bytes = &TIM2->PSC},
	{.bytes = &TIM3->PSC},
};
TIM_ARR_t TIM_ARR[3] = {
	{.bytes = &TIM1->ARR},
	{.bytes = &TIM2->ARR},
	{.bytes = &TIM3->ARR},
};
TIM_CCER_t TIM_CCER[3] = {
	{.bytes = &TIM1->CCER},
	{.bytes = &TIM2->CCER},
	{.bytes = &TIM3->CCER},
};
TIM_BDTR_t TIM_BDTR[1] = {
	{.bytes = &TIM1->BDTR},
};
TIM_CCMR1_t TIM_CCMR1[3] = {
	{.bytes = &TIM1->CCMR1},
	{.bytes = &TIM2->CCMR1},
	{.bytes = &TIM3->CCMR1},
};
void TIM_CCMR1_w(uint8_t TIM_ON, uint8_t field, uint8_t set, uint8_t mode)
{
	if (mode)
	{
		switch (field)
		{
		case CC1S:
			TIM_CCMR1[TIM_ON].CCMR1->CC1S = set;
			break;
		case OC1FE:
			TIM_CCMR1[TIM_ON].CCMR1->OC1FE = set;
			break;
		case OC1PE:
			TIM_CCMR1[TIM_ON].CCMR1->OC1PE = set;
			break;
		case OC1M:
			TIM_CCMR1[TIM_ON].CCMR1->OC1M = set;
			break;
		case OC1CE:
			TIM_CCMR1[TIM_ON].CCMR1->OC1CE = set;
			break;
		case CC2S:
			TIM_CCMR1[TIM_ON].CCMR1->CC2S = set;
			break;
		case OC2FE:
			TIM_CCMR1[TIM_ON].CCMR1->OC2FE = set;
			break;
		case OC2PE:
			TIM_CCMR1[TIM_ON].CCMR1->OC2PE = set;
			break;
		case OC2M:
			TIM_CCMR1[TIM_ON].CCMR1->OC2M = set;
			break;
		case OC2CE:
			TIM_CCMR1[TIM_ON].CCMR1->OC2CE = set;
			break;
		case OC1M3:
			TIM_CCMR1[TIM_ON].CCMR1->OC1M3 = set;
			break;
		case OC2M3:
			TIM_CCMR1[TIM_ON].CCMR1->OC2M3 = set;
			break;
		}
	}
	else
	{

		switch (field)
		{
		case CC1S:
			TIM_CCMR1[TIM_ON].CCMR1->CC1S = set;
			break;
		case IC1F:
			// OC1M  same address as IC1F, but redo this properly
			TIM_CCMR1[TIM_ON].CCMR1->OC1M = set;
			break;
		case CC2S_in:
			TIM_CCMR1[TIM_ON].CCMR1->CC2S = set;
			break;
		case IC2F:
			// OC2M  same address as IC2F, but redo this properly
			TIM_CCMR1[TIM_ON].CCMR1->OC2M = set;
			break;
		}
	}
}
void TIM_BDTR_w(uint8_t TIM_ON, uint8_t field, uint16_t set)
{
	*TIM_BDTR[TIM_ON].bytes = (uint16_t)((*TIM_BDTR[TIM_ON].bytes & ~(1 << field)) | (set << field));
}
void TIM_CCER_w(uint8_t TIM_ON, uint8_t field, uint16_t set)
{
	*TIM_CCER[TIM_ON].bytes = (uint16_t)((*TIM_CCER[TIM_ON].bytes & ~(1 << field)) | (set << field));
}
void TIM_ARR_w(uint8_t TIM_ON, uint8_t field, uint32_t set)
{
	for (int i = field; i < 32; i++)
	{
		*TIM_ARR[TIM_ON].bytes = (uint16_t)((*TIM_ARR[TIM_ON].bytes & ~(1 << i)) | ((set << field) & (1 << i)));
	}
}
void TIM_PSC_w(uint8_t TIM_ON, uint8_t field, uint16_t set)
{
	for (int i = field; i < 16; i++)
	{
		*TIM_PSC[TIM_ON].bytes = (uint16_t)((*TIM_PSC[TIM_ON].bytes & ~(1 << i)) | ((set << field) & (1 << i)));
	}
}
void TIM_EGR_w(uint8_t TIM_ON, uint8_t field, uint16_t set)
{
	*TIM_EGR[TIM_ON].bytes = (uint16_t)((*TIM_EGR[TIM_ON].bytes & ~(1 << field)) | (set << field));
}
uint16_t TIM_CCR2_wr(uint8_t TIM_ON, uint8_t field, uint16_t set, bool wr)
{
	for (int i = field; i < 16; i++)
	{
		*TIM_CCR2[TIM_ON].bytes = (*TIM_CCR2[TIM_ON].bytes & ~(1 << i)) | ((set << field) & (1 << i));
	}
	return 0;
}
uint32_t TIM_CCR1_wr(uint8_t TIM_ON, uint8_t field, uint16_t set, bool wr)
{
	if (wr == 0)
	{ // read
		return *TIM_CCR1[TIM_ON].bytes;
	}

	for (int i = field; i < 16; i++)
	{
		*TIM_CCR1[TIM_ON].bytes = (*TIM_CCR1[TIM_ON].bytes & ~(1 << i)) | ((set << field) & (1 << i));
	}

	return 0;
}
void TIM_CR1_w(uint8_t TIM_ON, uint8_t field, uint32_t set)
{
	*TIM_CR1[TIM_ON].bytes = (*TIM_CR1[TIM_ON].bytes & ~(1 << field)) | (set << field);
}
uint32_t DMA_ISR_r(uint8_t field)
{
	return *DMA_ISR.bytes & (SETBIT << field);
}
uint32_t RCC_AHB1ENR_wr(uint8_t field, uint8_t set, bool wr)
{
	return wr ? *RCC_AHB1ENR.bytes = (*RCC_AHB1ENR.bytes & ~(1 << field)) | (set << field) : *RCC_AHB1ENR.bytes & (SETBIT << field);
}
uint32_t RCC_APB2ENR_wr(uint8_t field, uint8_t set, bool wr)
{
	return wr ? *RCC_APB2ENR.bytes = (*RCC_APB2ENR.bytes & ~(1 << field)) | (set << field) : *RCC_APB2ENR.bytes & (SETBIT << field);
}
void DMA_IFCR_w(uint8_t field, uint32_t set)
{
	*DMA_IFCR.bytes = (*DMA_IFCR.bytes & ~(1 << field)) | (set << field);
}
void DMA1_Channel_CNDTR_w(uint8_t DMA1_Channel_ON, uint32_t set, bool wr)
{
	*DMA1_Channel_CNDTR[DMA1_Channel_ON].bytes = set;
}
void DMA1_Channel_CPAR_w(uint8_t DMA1_Channel_ON, uint32_t set, bool wr)
{
	*DMA1_Channel_CPAR[DMA1_Channel_ON].bytes = set;
}
void DMA1_Channel_CMAR_w(uint8_t DMA1_Channel_ON, uint32_t set, bool wr)
{
	*DMA1_Channel_CMAR[DMA1_Channel_ON].bytes = set;
}
uint32_t DMA1_Channel_CSELR_wr(uint8_t field, uint32_t set, bool wr)
{
	return wr ? *DMA1_Channel_CSELR.bytes = (*DMA1_Channel_CSELR.bytes & ~(1 << field)) | (set << field) : *DMA1_Channel_CSELR.bytes & (SETBIT << field);
}
uint32_t USART_CR3_wr(uint8_t USART_ON, uint8_t field, uint8_t set, bool wr)
{
	return wr ? *USART_CR3[USART_ON].bytes = (*USART_CR3[USART_ON].bytes & ~(1 << field)) | (set << field) : *USART_CR3[USART_ON].bytes & (SETBIT << field);
}
uint32_t DMA1_Channel_CCR_wr(uint8_t DMA1_Channel_ON, uint8_t field, uint32_t set, bool wr)
{
	return wr ? *DMA1_Channel_CCR[DMA1_Channel_ON].bytes = (*DMA1_Channel_CCR[DMA1_Channel_ON].bytes & ~(1 << field)) | (set << field) : *DMA1_Channel_CCR[DMA1_Channel_ON].bytes & (SETBIT << field);
}
uint32_t GPIO_OTYPER_wr(uint8_t port, uint8_t field, uint8_t set, bool wr)
{
	return wr ? *GPIO_OTYPER[port].bytes = (*GPIO_OTYPER[port].bytes & ~(1 << field)) | (set << field) : *GPIO_OTYPER[port].bytes & (SETBIT << field);
}
uint32_t I2C_ISR_r(uint8_t I2C_ON, uint8_t field)
{
	return *I2C_ISR[I2C_ON].bytes & (SETBIT << field);
	// 	return I2C_ISR[I2C_ON].I_ISR->ADDCODE; // check this
}
uint32_t I2C_CR2_wr(uint8_t I2C_ON, uint8_t field, uint32_t set, bool wr)
{
	if ((field == SADD07) || (field == NBYTES))
	{
		for (int i = field; i < field + 8; i++)
		{
			*I2C_CR2[I2C_ON].bytes = (*I2C_CR2[I2C_ON].bytes & ~(1 << i)) | ((set << field) & (1 << i));
		}
		return 0;
		// TODO: read address
	}
	return wr ? *I2C_CR2[I2C_ON].bytes = (*I2C_CR2[I2C_ON].bytes & ~(1 << field)) | (set << field) : *I2C_CR2[I2C_ON].bytes & (SETBIT << field);
}
uint32_t I2C_CR1_wr(uint8_t I2C_ON, uint8_t field, uint8_t set, bool wr)
{
	return wr ? *I2C_CR1[I2C_ON].bytes = (*I2C_CR1[I2C_ON].bytes & ~(1 << field)) | (set << field) : *I2C_CR1[I2C_ON].bytes & (SETBIT << field);
	// check DNF
}
void I2C_TXDR_w(uint8_t I2C_ON, uint8_t data)
{
	*I2C_TXDR[I2C_ON].TXDATA = data;
}

uint32_t I2C_RXDR_r(uint8_t I2C_ON)
{
	return *I2C_RXDR[I2C_ON].RXDATA;
}

void I2C_TIMINGR_w(uint8_t I2C_ON, uint32_t data)
{
	*I2C_TIMINGR[I2C_ON].I_TIMINGR = data;
}
uint8_t USART_RDR_r(uint8_t USART_ON)
{
	return (char)USART_RDR[USART_ON].U_RDR->RDR;
}
void USART_TDR_w(uint8_t USART_ON, char data)
{
	USART_TDR[USART_ON].U_TDR->TDR = data;
}
uint8_t USART_ISR_r(uint8_t USART_ON, uint8_t field)
{
	return *USART_ISR[USART_ON].bytes & (SETBIT << field);
}

uint32_t USART_CR1_wr(uint8_t USART_ON, uint8_t field, uint8_t set, bool wr)
{
	return wr ? *USART_CR1[USART_ON].bytes = (*USART_CR1[USART_ON].bytes & ~(1 << field)) | (set << field) : *USART_CR1[USART_ON].bytes & (SETBIT << field);
	// TODO
	// case DEDT:
	// 	USART_CR1[USART_ON].U_CR1->DEDT = set;
	// 	break;
	// case DEAT:
	// 	USART_CR1[USART_ON].U_CR1->DEAT = set;
}
void USART_BRR_w(uint8_t USART_ON, uint16_t baud_rate)
{
	*USART_BRR[USART_ON].bytes = baud_rate;
}
uint32_t RCC_APB1ENR1_wr(uint8_t field, uint8_t set, bool wr)
{
	return wr ? *RCC_APB1ENR1.bytes = (*RCC_APB1ENR1.bytes & ~(1 << field)) | (set << field) : *RCC_APB1ENR1.bytes & (SETBIT << field);
}
uint32_t RCC_AHB2ENR_wr(uint8_t field, uint8_t set, bool wr)
{
	return wr ? *RCC_AHB2ENR.bytes = (*RCC_AHB2ENR.bytes & ~(1 << field)) | (set << field) : *RCC_AHB2ENR.bytes & (SETBIT << field);
}
void GPIO_AFR_w(uint8_t port, uint8_t field, uint32_t AF, bool is_high)
{
	if (is_high)
		port += PORT_END;

	for (int i = field; i < field + 4; i++)
	{
		*GPIO_AFR[port].bytes = (*GPIO_AFR[port].bytes & ~(1 << i)) | ((AF << field) & (1 << i));
	}
}
void GPIO_BSRR_w(uint8_t port, uint8_t field, uint8_t set)
{
	*GPIO_BSRR[port].bytes = (*GPIO_BSRR[port].bytes & ~(1 << field)) | (set << field);
}

void GPIO_MODER_w(uint8_t port, uint8_t field, uint8_t mode)
{
	switch (field)
	{
	case MODE0:
		GPIO_MODER[port].MODE->MODE0 = mode;
		break;
	case MODE1:
		GPIO_MODER[port].MODE->MODE1 = mode;
		break;
	case MODE2:
		GPIO_MODER[port].MODE->MODE2 = mode;
		break;
	case MODE3:
		GPIO_MODER[port].MODE->MODE3 = mode;
		break;
	case MODE4:
		GPIO_MODER[port].MODE->MODE4 = mode;
		break;
	case MODE5:
		GPIO_MODER[port].MODE->MODE5 = mode;
		break;
	case MODE6:
		GPIO_MODER[port].MODE->MODE6 = mode;
		break;
	case MODE7:
		GPIO_MODER[port].MODE->MODE7 = mode;
		break;
	case MODE8:
		GPIO_MODER[port].MODE->MODE8 = mode;
		break;
	case MODE9:
		GPIO_MODER[port].MODE->MODE9 = mode;
		break;
	case MODE10:
		GPIO_MODER[port].MODE->MODE10 = mode;
		break;
	case MODE11:
		GPIO_MODER[port].MODE->MODE11 = mode;
		break;
	case MODE12:
		GPIO_MODER[port].MODE->MODE12 = mode;
		break;
	case MODE13:
		GPIO_MODER[port].MODE->MODE13 = mode;
		break;
	case MODE14:
		GPIO_MODER[port].MODE->MODE14 = mode;
		break;
	case MODE15:
		GPIO_MODER[port].MODE->MODE15 = mode;
		break;
	}
}