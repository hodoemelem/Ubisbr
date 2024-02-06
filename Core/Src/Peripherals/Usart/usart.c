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
#include "usart.h"
#include "peri_clock.h"
#include <string.h>
#include <stdio.h>
#include "radio.h"

const uint16_t radio_baud_rate = 0x271;
const uint16_t tel_baud_rate = 0xEA6;//0x27;//921600
// for tel_baud_rate only
//0xea6 for 9600
//0x139 115200 *
//0x753 19200*
//0x271 57600*
//0x3AA 38400*
void usart1_radio_init();
void usart2_display_init();

void usart_init()
{
    usart2_display_init();
    usart1_radio_init();
}

void usart2_display_init()
{
    // PA2 TX and PA3 RX, for  usart2, telemetry
    GPIO_MODER_w(PORTA, MODE2, ALT);
    GPIO_AFR_w(PORTA, AFSEL2_10, USART, false);
    GPIO_MODER_w(PORTA, MODE3, ALT);
    GPIO_AFR_w(PORTA, AFSEL3_11, USART, false);

    // usart2 direct display
    USART_BRR_w(USART_2, tel_baud_rate);
    USART_CR1_wr(USART_2, UE, SETBIT, WRITE); // enable USART UE BIT 0 (do after all USART config.), b4 RE and TE
    USART_CR1_wr(USART_2, RE, SETBIT, WRITE); // enable RX mode of USART RE (BIT 2)
    USART_CR1_wr(USART_2, TE, SETBIT, WRITE); // enable TX mode of USART TE (BIT 3)

    //BT
        // PC10 TX and PC11 RX, for  usart3, telemetry
    GPIO_MODER_w(PORTC, MODE10, ALT);
    GPIO_AFR_w(PORTC, AFSEL2_10, USART, true);
    GPIO_MODER_w(PORTC, MODE11, ALT);
    GPIO_AFR_w(PORTC, AFSEL3_11, USART, true);

    // usart2 direct display
    USART_BRR_w(USART_3, tel_baud_rate);
    USART_CR1_wr(USART_3, UE, SETBIT, WRITE); // enable USART UE BIT 0 (do after all USART config.), b4 RE and TE
    USART_CR1_wr(USART_3, RE, SETBIT, WRITE); // enable RX mode of USART RE (BIT 2)
    USART_CR1_wr(USART_3, TE, SETBIT, WRITE); // enable TX mode of USART TE (BIT 3)
}

// for radio,at 115200 baud rate
void usart1_radio_init()
{
    // PA10 for  usart1, radio
    GPIO_MODER_w(PORTA, MODE10, ALT);
    GPIO_AFR_w(PORTA, AFSEL2_10, USART, true);

    // // PA10 Rx
    DMA1_Channel_CSELR_wr(C5S + 1, SETBIT, WRITE);

    USART_CR3_wr(USART_1, DMAR, SETBIT, WRITE);

    DMA1_Channel_CPAR_w(DMA1_Ch5, (uint32_t)&USART1->RDR, WRITE);
    DMA1_Channel_CMAR_w(DMA1_Ch5, (uint32_t)ibus, WRITE);

    DMA1_Channel_CNDTR_w(DMA1_Ch5, radio_buffer, WRITE); // number of byte to rx

    DMA1_Channel_CCR_wr(DMA1_Ch5, MINC_DMA, SETBIT, WRITE);
    DMA1_Channel_CCR_wr(DMA1_Ch5, PL, SETBIT, WRITE);//medium piriority

    USART_BRR_w(USART_1, radio_baud_rate);    // 72MHz/115200 = 271 hex,  pg 1356/1395 of refernce manual, OVER8 = 0
    USART_CR1_wr(USART_1, UE, SETBIT, WRITE); // enable USART UE BIT 0 (do after all USART config.), b4 RE and TE
    USART_CR1_wr(USART_1, RE, SETBIT, WRITE); // enable RX mode of USART RE (BIT 2)
    USART_CR1_wr(USART_1, TE, SETBIT, WRITE); // enable TX mode of USART TE (BIT 3)

    DMA1_Channel_CCR_wr(DMA1_Ch5, EN_DMA, SETBIT, WRITE);


   ///////////////////////////
   

}

void usart1_radio_dma_restart()
{
    DMA_IFCR_w(CTCIF5, SETBIT);
    DMA1_Channel_CCR_wr(DMA1_Ch5, EN_DMA, !SETBIT, WRITE); // clear config reg before disabling the uart
    USART_CR3_wr(USART_1, DMAR, !SETBIT, WRITE);           // DMAR diasble , b4 uart disable
    USART_CR1_wr(USART_1, TE, !SETBIT, WRITE);             // enable TX mode of USART TE (BIT 3)
    while (!USART_ISR_r(USART_2, TC))
        ;                                                           // wait for TC to be set automatically after TE is disabled
    USART_CR1_wr(USART_1, UE, !SETBIT, WRITE);                      // disable USART
    DMA1_Channel_CNDTR_w(DMA1_Ch5, radio_buffer, WRITE); // number of byte to rx
    DMA1_Channel_CCR_wr(DMA1_Ch5, EN_DMA, SETBIT, WRITE);           // enable

    USART_CR3_wr(USART_1, DMAR, SETBIT, WRITE);
    USART_CR1_wr(USART_1, UE, SETBIT, WRITE); // enable USART UE BIT 0 (do after all USART config.), b4 RE and TE
}
