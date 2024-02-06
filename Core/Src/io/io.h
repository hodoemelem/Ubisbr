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
#ifndef IO_H
#define IO_H
#include "io_def.h"
#include <stdbool.h>

void GPIO_BSRR_w(uint8_t port, uint8_t field, uint8_t set);
void GPIO_MODER_w(uint8_t port, uint8_t field, uint8_t mode);
uint32_t RCC_AHB2ENR_wr(uint8_t field, uint8_t set, bool wr);
void GPIO_AFR_w(uint8_t port, uint8_t field, uint32_t AF, bool is_high);
uint32_t RCC_APB1ENR1_wr(uint8_t field, uint8_t set, bool wr);
void USART_BRR_w(uint8_t USART_ON, uint16_t baud_rate);
uint32_t USART_CR1_wr(uint8_t USART_ON, uint8_t field, uint8_t set, bool wr);
uint8_t USART_ISR_r(uint8_t USART_ON, uint8_t field);
void USART_TDR_w(uint8_t USART_ON, char data);
uint8_t USART_RDR_r(uint8_t USART_ON);
void I2C_TIMINGR_w(uint8_t I2C_ON, uint32_t data);
void I2C_TXDR_w(uint8_t I2C_ON, uint8_t data);
uint32_t I2C_RXDR_r(uint8_t I2C_ON);
uint32_t I2C_CR1_wr(uint8_t I2C_ON, uint8_t field, uint8_t set, bool wr);
uint32_t I2C_CR2_wr(uint8_t I2C_ON, uint8_t field, uint32_t set, bool wr);
uint32_t I2C_ISR_r(uint8_t I2C_ON, uint8_t field);
uint32_t GPIO_OTYPER_wr(uint8_t port, uint8_t field, uint8_t set, bool wr);
uint32_t DMA1_Channel_CCR_wr(uint8_t DMA1_Channel_ON, uint8_t field, uint32_t set, bool wr);
uint32_t USART_CR3_wr(uint8_t USART_ON, uint8_t field, uint8_t set, bool wr);
uint32_t DMA1_Channel_CSELR_wr(uint8_t field, uint32_t set, bool wr);
void DMA1_Channel_CPAR_w(uint8_t DMA1_Channel_ON, uint32_t set, bool wr);
void DMA1_Channel_CMAR_w(uint8_t DMA1_Channel_ON, uint32_t set, bool wr);
void DMA1_Channel_CNDTR_w(uint8_t DMA1_Channel_ON, uint32_t set, bool wr);
void DMA_IFCR_w(uint8_t field, uint32_t set);
uint32_t RCC_APB2ENR_wr(uint8_t field, uint8_t set, bool wr);
uint32_t RCC_AHB1ENR_wr(uint8_t field, uint8_t set, bool wr);
uint32_t DMA_ISR_r(uint8_t field);
void TIM_CR1_w(uint8_t TIM_ON, uint8_t field, uint32_t set);
uint32_t TIM_CCR1_wr(uint8_t TIM_ON, uint8_t field, uint16_t set, bool wr);
uint16_t TIM_CCR2_wr(uint8_t TIM_ON, uint8_t field, uint16_t set, bool wr);
void TIM_EGR_w(uint8_t TIM_ON, uint8_t field, uint16_t set);
void TIM_PSC_w(uint8_t TIM_ON, uint8_t field, uint16_t set);
void TIM_ARR_w(uint8_t TIM_ON, uint8_t field, uint32_t set);
void TIM_CCER_w(uint8_t TIM_ON, uint8_t field, uint16_t set);
void TIM_BDTR_w(uint8_t TIM_ON, uint8_t field, uint16_t set);
void TIM_CCMR1_w(uint8_t TIM_ON, uint8_t field, uint8_t set,  uint8_t mode);
#endif
