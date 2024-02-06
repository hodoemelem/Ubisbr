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
#include "timer.h"
#include "peri_clock.h"
#include "usart_comm.h"
#include "stm32l4xx_hal.h"

#define PSC 1800            // set  72MHz clk / 40khz counter = 1800
#define COUNT_FREQ 40000.0f // 40kHz
#define PERIOD 1.0 / COUNT_FREQ
#define dma_buffer_size 4
uint32_t enc_r[dma_buffer_size] = {0, 0, 0, 0};
uint32_t enc_l[dma_buffer_size] = {0, 0, 0, 0};

void restart_timer_dma();
void right_motor_cw();

void timer_init()
{
    //  PA0 and PA1 for timer/pwm/motor
    // PA0 TIM2 CH1, PWMA LEFT
    // PA1 TIM2 CH2, PWMB RIGHT

    GPIO_MODER_w(PORTA, MODE0, ALT);
    GPIO_AFR_w(PORTA, AFSEL0_8, AF1_TIMER, false);

    GPIO_MODER_w(PORTA, MODE1, ALT);
    GPIO_AFR_w(PORTA, AFSEL1_9, AF1_TIMER, false);

    // // input timer for right motor encoder, PB4
    GPIO_MODER_w(PORTB, MODE4, ALT);
    GPIO_AFR_w(PORTB, AFSEL4_12, AF2_TIMER, false); // attach TIM3 ch1 to PB4

    // PB0 input timer for left motor encoder
    GPIO_MODER_w(PORTB, MODE0, ALT);
    GPIO_AFR_w(PORTB, AFSEL0_8, AF2_TIMER, false); // attach TIM3 ch3 to PB0

    motor_init();
    encoder_init();
}

void motor_init(void)
{
    // TIM2***********************************************************************
    TIM_PSC_w(TIM_2, PSC015, 36 - 1);   // set 2MHz clk
    TIM_ARR_w(TIM_2, ARR015, 5000 - 1); // 400Hz, 2.5ms total period

    // Enable Pwm mode 1,preload enable
    TIM_CCMR1_w(TIM_2, OC1PE, SETBIT, OUTPUT);
    TIM_CCMR1_w(TIM_2, OC1M, 0b110, OUTPUT);
    TIM_CCMR1_w(TIM_2, OC2PE, SETBIT, OUTPUT);
    TIM_CCMR1_w(TIM_2, OC2M, 0b110, OUTPUT);

    TIM_CR1_w(TIM_2, ARPE, SETBIT); // Auto-reload preload enable
    TIM_EGR_w(TIM_2, UG, SETBIT);   // Re-initialize the counter and generates an update of the registers

    // enable channels
    TIM_CCER_w(TIM_2, CC1E, SETBIT);
    TIM_CCER_w(TIM_2, CC2E, SETBIT);

    TIM_CCR1_wr(TIM_2, CCR1_015, 0, WRITE); // about 0% rpm
    TIM_CCR2_wr(TIM_2, CCR2_015, 0, WRITE); // about 0% rpm

    // TIM_CR1_w(TIM_1, CEN, SETBIT); // Counter enable
    TIM_CR1_w(TIM_2, CEN, SETBIT); // Counter enable
}

void encoder_init()
{

    // DMA1_Channel_CCR_wr(DMA1_Ch6, EN_DMA, !SETBIT, WRITE);
    // TIM_CR1_w(TIM_3, CEN, !SETBIT);   // Counter enable
    // TIM_CCER_w(TIM_3, CC1E, !SETBIT); // caputre enabled

    // /////////////////////////////////////////
    // TIM_EGR_w(TIM_3, UG, SETBIT);             // Re-initialize the counter and generates an update of the registers
    // TIM_PSC_w(TIM_3, PSC015, PSC - 1);        // set 40khz clk
    // TIM_ARR_w(TIM_3, ARR015, COUNT_FREQ - 1); // 1 sec
    // TIM_CR1_w(TIM_3, ARPE, SETBIT);           // Auto-reload preload enable

    // // Input mode config
    // TIM_CCMR1_w(TIM_3, CC1S, 0b01, INPUT);   // make input
    // TIM_CCMR1_w(TIM_3, IC1F, 0b0011, INPUT); // input filter
    // // Capture Input on rising edge(default): CC1P and CC1NP bits to 000 in the TIMx_CCER register (rising edge in this case).

    // TIM3->DIER |= (1 << 9); // 1: CC1 DMA request enabled.
    // TIM3->EGR |= (1 << 1);  //  DMA request is sent on capture event
    //                         // CR2 reg, default 0: CCx DMA request sent when CCx event occurs

    // ////dma timer
    // DMA1_CSELR->CSELR |= ((1 << 20) | (1 << 22)); // dma ch6 select
    // DMA1_Channel_CPAR_w(DMA1_Ch6, (uint32_t)&TIM3->CCR1, WRITE);
    // DMA1_Channel_CMAR_w(DMA1_Ch6, (uint32_t)enc, WRITE);
    // DMA1_Channel_CNDTR_w(DMA1_Ch6, dma_buffer_size, WRITE); // number of data to rx
    // DMA1_Channel_CCR_wr(DMA1_Ch6, PL + 1, SETBIT, WRITE);   // pirority high
    // // DIR, default 0: read from peripheral
    // DMA1_Channel_CCR_wr(DMA1_Ch6, MINC_DMA, SETBIT, WRITE); // peri to peri

    // DMA1_Channel6->CCR |= (1 << 11); // 32 bits transfers, mem, destination
    // DMA1_Channel6->CCR |= (1 << 9);  // 32 bits transfers, periph, source
    // ////end dma timer

    // TIM_CCER_w(TIM_3, CC1E, SETBIT); // caputre enabled
    // TIM_CR1_w(TIM_3, CEN, SETBIT);   // Counter enable
    // DMA1_Channel_CCR_wr(DMA1_Ch6, EN_DMA, SETBIT, WRITE);

    //**********************************************************************
    DMA1_Channel_CCR_wr(DMA1_Ch6, EN_DMA, !SETBIT, WRITE);
    DMA1_Channel_CCR_wr(DMA1_Ch2, EN_DMA, !SETBIT, WRITE);
    TIM_CR1_w(TIM_3, CEN, !SETBIT);   // Counter disable
    TIM_CCER_w(TIM_3, CC1E, !SETBIT); // caputre disenabled ch1
    TIM_CCER_w(TIM_3, CC3E, !SETBIT); // caputre disenabled ch3

    /////////////////////////////////////////
    TIM_EGR_w(TIM_3, UG, SETBIT);             // Re-initialize the counter and generates an update of the registers
    TIM_PSC_w(TIM_3, PSC015, PSC - 1);        // set 40khz clk
    TIM_ARR_w(TIM_3, ARR015, COUNT_FREQ - 1); // 1 sec
    TIM_CR1_w(TIM_3, ARPE, SETBIT);           // Auto-reload preload enable

    // Input mode config
    TIM_CCMR1_w(TIM_3, CC1S, 0b01, INPUT);   // make input ch1
    TIM3->CCMR2 |= (1 << 0);                 // make input ch3
    TIM_CCMR1_w(TIM_3, IC1F, 0b0011, INPUT); // input filter ch1
    TIM3->CCMR2 |= (1 << 4) | (1 << 5);      // input filter ch3
    // Capture Input on rising edge(default): CC1P and CC1NP bits to 000 in the TIMx_CCER register (rising edge in this case).

    TIM3->DIER |= (1 << 9);  // 1: CC1 DMA request enabled.
    TIM3->DIER |= (1 << 11); // 1: CC3 DMA request enabled.
    TIM3->EGR |= (1 << 1);   //  DMA request is sent on capture event on cc1
    TIM3->EGR |= (1 << 3);   //  DMA request is sent on capture event on cc3
                             // CR2 reg, default 0: CCx DMA request sent when CCx event occurs

    ///////////////
    DMA1_CSELR->CSELR |= ((1 << 4) | (1 << 6)) | ((1 << 20) | (1 << 22)); // dma1 ch2 for tim3 ch3,  dma1 ch6 select for tim3 ch1

    ////dma timer for tim3 ch1, RIGHT ENC
    DMA1_Channel_CPAR_w(DMA1_Ch6, (uint32_t)&TIM3->CCR1, WRITE);
    DMA1_Channel_CMAR_w(DMA1_Ch6, (uint32_t)enc_r, WRITE);
    DMA1_Channel_CNDTR_w(DMA1_Ch6, dma_buffer_size, WRITE); // number of data to rx
    DMA1_Channel_CCR_wr(DMA1_Ch6, PL + 1, SETBIT, WRITE);   // pirority high
    // DIR, default 0: read from peripheral
    DMA1_Channel_CCR_wr(DMA1_Ch6, MINC_DMA, SETBIT, WRITE); // peri to peri

    DMA1_Channel6->CCR |= (1 << 11); // 32 bits transfers, mem, destination
    DMA1_Channel6->CCR |= (1 << 9);  // 32 bits transfers, periph, source
    ////end dma timer

    ////////// LEFT ENC
    DMA1_Channel_CPAR_w(DMA1_Ch2, (uint32_t)&TIM3->CCR3, WRITE);
    DMA1_Channel_CMAR_w(DMA1_Ch2, (uint32_t)enc_l, WRITE);
    DMA1_Channel_CNDTR_w(DMA1_Ch2, dma_buffer_size, WRITE); // number of data to rx
    DMA1_Channel_CCR_wr(DMA1_Ch2, PL + 1, SETBIT, WRITE);   // pirority high
    // DIR, default 0: read from peripheral
    DMA1_Channel_CCR_wr(DMA1_Ch2, MINC_DMA, SETBIT, WRITE); // peri to peri

    DMA1_Channel2->CCR |= (1 << 11); // 32 bits transfers, mem, destination
    DMA1_Channel2->CCR |= (1 << 9);  // 32 bits transfers, periph, source
    ////////

    TIM_CCER_w(TIM_3, CC1E, SETBIT); // caputre enabled ch1
    TIM_CCER_w(TIM_3, CC3E, SETBIT); // caputre enabled ch3
    TIM_CR1_w(TIM_3, CEN, SETBIT);   // Counter enable
    DMA1_Channel_CCR_wr(DMA1_Ch6, EN_DMA, SETBIT, WRITE);
    DMA1_Channel_CCR_wr(DMA1_Ch2, EN_DMA, SETBIT, WRITE);
}

enc_t enc_counts()
{
    static float enc_count_r = 0;
    static float enc_count_l = 0;
    static enc_t enc_data;
    static uint8_t not_moving_counter_l = 0;
    static uint8_t not_moving_counter_r = 0;

    if (DMA_ISR_r(TEIF6))
    {
        DMA_IFCR_w(CTEIF6, SETBIT); // clear complete flag
    }
    else if (DMA_ISR_r(TCIF6))
    {

        int16_t count = (enc_r[2] - enc_r[1]);
        int16_t count_2 = (enc_r[3] - enc_r[2]);

        if (abs(count - count_2) < 5) // make sure the array entries are uniformly spaced
        {

            if ((count >= 25) 
            && // pwm 5000(100%) gives 29(0.75ms) counter counts.
                (count <= 500)   // min counts for min pwm, 500 count -> 80 enc -> 200 pwm
            )
            {
                enc_count_r = (1.0 / (float)(count * PERIOD)); // number of encoder counts per sec
            }
        }

        not_moving_counter_r = 0;
        // char msg[100];
        // sprintf(msg, "*********: %lu,%lu ,%lu,%lu ,%d,%d ,%f   \n", enc[0], enc[1], enc[2], enc[3], count, count_2, enc_count);
        // usart2_tx(msg);
    }

    // left encoder
    if (DMA_ISR_r(TEIF2))
    {
        DMA_IFCR_w(CTEIF2, SETBIT); // clear complete flag
    }
    else if (DMA_ISR_r(TCIF2))
    {

        int16_t count = (enc_l[2] - enc_l[1]);
        int16_t count_2 = (enc_l[3] - enc_l[2]);

        if (abs(count - count_2) < 5) // make sure the array entries are uniformly spaced
        {

            if ((count >= 25) 
            && // pwm 5000(100%) gives 29(0.75ms) counter counts.
                (count <= 500)   // min counts for min pwm
            )
            {
                enc_count_l = (1.0 / (float)(count * PERIOD)); // number of encoder counts per sec
            }
        }
        not_moving_counter_l = 0;
        // char msg[100];
        // sprintf(msg, "*********: %lu,%lu ,%lu,%lu ,%d,%d ,%f   \n", enc[0], enc[1], enc[2], enc[3], count, count_2, enc_count);
        // usart2_tx(msg);
    }

    not_moving_counter_l++;
    not_moving_counter_r++;

    if (not_moving_counter_l > 100)
    {
        not_moving_counter_l = 100;
    }
    if (not_moving_counter_r > 100)
    {
        not_moving_counter_r = 100;
    }
    
    // if (not_moving_counter_l >= 100)
    // {
    //     enc_count_l = 0;
    // }
    // if (not_moving_counter_r >= 100)
    // {
    //     enc_count_r = 0;
    // }

    if (DMA_ISR_r(TCIF6) || DMA_ISR_r(TCIF2))
    {
        restart_timer_dma();
    }

    enc_data.encoder_count_r = enc_count_r;
    enc_data.encoder_count_l = enc_count_l;

    return enc_data;
}

void restart_timer_dma()
{
    // DMA_IFCR_w(CTCIF6, SETBIT); // clear complete flag

    // DMA1_Channel_CCR_wr(DMA1_Ch6, EN_DMA, !SETBIT, WRITE);
    // TIM3->DIER &= ~(1 << 9);                                // 1: CC1 DMA request disabled
    // TIM3->EGR &= ~(1 << 1);                                 //  DMA request is sent on capture event
    // TIM_CR1_w(TIM_3, CEN, !SETBIT);                         // Counter disabled
    // TIM_CCER_w(TIM_3, CC1E, !SETBIT);                       // caputre enabled
    // TIM_EGR_w(TIM_3, UG, SETBIT);                           // Re-initialize the counter and generates an update of the registers
    // DMA1_Channel_CNDTR_w(DMA1_Ch6, dma_buffer_size, WRITE); // number of data to rx(important to refill CNDTR if circular mode is not used)

    // TIM3->DIER |= (1 << 9);          // 1: CC1 DMA request enabled.
    // TIM3->EGR |= (1 << 1);           //  DMA request is sent on capture event
    //                                  // CR2 reg, default 0: CCx DMA request sent when CCx event occurs
    // TIM_CCER_w(TIM_3, CC1E, SETBIT); // caputre enabled
    // TIM_CR1_w(TIM_3, CEN, SETBIT);   // Counter disabled
    // DMA1_Channel_CCR_wr(DMA1_Ch6, EN_DMA, SETBIT, WRITE);

    DMA_IFCR_w(CTCIF6, SETBIT); // clear complete flag
    DMA_IFCR_w(CTCIF2, SETBIT); // clear complete flag

    DMA1_Channel_CCR_wr(DMA1_Ch6, EN_DMA, !SETBIT, WRITE);
    DMA1_Channel_CCR_wr(DMA1_Ch2, EN_DMA, !SETBIT, WRITE);
    TIM3->DIER &= ~(1 << 9);                                // 1: CC1 DMA request disabled
    TIM3->EGR &= ~(1 << 1);                                 //  DMA request is sent on capture event
    TIM3->DIER &= ~(1 << 11);                               // 1: CC3 DMA request disabled
    TIM3->EGR &= ~(1 << 3);                                 //  DMA request is sent on capture event
    TIM_CR1_w(TIM_3, CEN, !SETBIT);                         // Counter disabled
    TIM_CCER_w(TIM_3, CC1E, !SETBIT);                       // caputre disabled ch1
    TIM_CCER_w(TIM_3, CC3E, !SETBIT);                       // caputre disenabled ch3
    TIM_EGR_w(TIM_3, UG, SETBIT);                           // Re-initialize the counter and generates an update of the registers
    DMA1_Channel_CNDTR_w(DMA1_Ch6, dma_buffer_size, WRITE); // number of data to rx(important to refill CNDTR if circular mode is not used)
    DMA1_Channel_CNDTR_w(DMA1_Ch2, dma_buffer_size, WRITE); // number of data to rx(important to refill CNDTR if circular mode is not used)

    TIM3->DIER |= (1 << 9);          // 1: CC1 DMA request enabled.
    TIM3->EGR |= (1 << 1);           //  DMA request is sent on capture event
    TIM3->DIER |= (1 << 11);         // 1: CC3 DMA request enabled.
    TIM3->EGR |= (1 << 3);           //  DMA request is sent on capture event
                                     // CR2 reg, default 0: CCx DMA request sent when CCx event occurs
    TIM_CCER_w(TIM_3, CC1E, SETBIT); // caputre enabled
    TIM_CCER_w(TIM_3, CC3E, SETBIT); // caputre enabled ch3
    TIM_CR1_w(TIM_3, CEN, SETBIT);   // Counter enabled
    DMA1_Channel_CCR_wr(DMA1_Ch6, EN_DMA, SETBIT, WRITE);
    DMA1_Channel_CCR_wr(DMA1_Ch2, EN_DMA, SETBIT, WRITE);
}

void sbr_gpio_init()
{
    GPIO_MODER_w(PORTB, MODE1, OUTPUT); // PB1 STBY_PIN
    GPIO_MODER_w(PORTB, MODE2, OUTPUT); // PB2 Right motor direction control PIN, AIN1
    GPIO_MODER_w(PORTB, MODE3, OUTPUT); // PB3 Left motor direction control PIN, BIN1
    timer_init();
    right_motor_cw();

    // //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // // input timer for right motor encoder, PB4, for use with enc_t enc_val()
    // GPIO_MODER_w(PORTB, MODE4, INPUT);
    // // PB0 input timer for left motor encoder
    // GPIO_MODER_w(PORTB, MODE0, INPUT);
}

void right_motor_cw()
{
    GPIO_BSRR_w(PORTB, BS1, SETBIT); // STBY_PIN HIGH

    ////Backwrard
    // // //  A left
    // GPIO_BSRR_w(PORTB, BS2, SETBIT);        // left motor direction control PIN, AIN1, ccw
    // TIM_CCR1_wr(TIM_2, CCR1_015, 1000, WRITE); // PA0 TIM2 CH1, PWMA LEFT

    // //  B right
    // GPIO_BSRR_w(PORTB, BS3, SETBIT);              // Right motor direction control PIN, bIN1, cw
    // TIM_CCR2_wr(TIM_2, CCR2_015,1000, WRITE); // PA1 TIM2 CH2, PWMB RIGHT

    //////////// Forward
    //   A left
    GPIO_BSRR_w(PORTB, BR2, SETBIT);          // left motor direction control PIN, AIN1, ccw
    TIM_CCR1_wr(TIM_2, CCR1_015, 200, WRITE); // PA0 TIM2 CH1, PWMA LEFT

    // //  B right
    GPIO_BSRR_w(PORTB, BR3, SETBIT);          // Right motor direction control PIN, bIN1, cw
    TIM_CCR2_wr(TIM_2, CCR2_015, 200, WRITE); // PA1 TIM2 CH2, PWMB RIGHT
}

pwm_t turn_motors_off(void)
{
    pwm_t pwm;

    pwm.pwm1 = 0; // M1
    pwm.pwm2 = 0; // M2

    TIM_CCR2_wr(TIM_2, CCR2_015, pwm.pwm1, WRITE); // PA1 TIM2 CH2, PWMB RIGHT
    TIM_CCR1_wr(TIM_2, CCR1_015, pwm.pwm2, WRITE); // PA0 TIM2 CH1, PWMA LEFT

    return pwm;
}

void set_motors_pwm(pwm_t pwm)
{
    // forward;  R 0cw, L 0ccw
    // backward; R 1ccw, L 1cw

    // let +ve pwm move sbr forward, as +ve angle means lean forward

    if (pwm.pwm1 > 0)
    {
        GPIO_BSRR_w(PORTB, BR3, SETBIT); // Right motor direction control PIN, bIN1, cw
    }
    else
    {
        GPIO_BSRR_w(PORTB, BS3, SETBIT); // Right motor direction control PIN, bIN1, ccw
    }

    if (pwm.pwm2 > 0)
    {
        GPIO_BSRR_w(PORTB, BR2, SETBIT); // left motor direction control PIN, AIN1, ccw
    }
    else
    {
        GPIO_BSRR_w(PORTB, BS2, SETBIT); // left motor direction control PIN, AIN1, cw
    }

    TIM_CCR2_wr(TIM_2, CCR2_015, fabs(pwm.pwm1), WRITE); // PA1 TIM2 CH2, PWMB RIGHT
    TIM_CCR1_wr(TIM_2, CCR1_015, fabs(pwm.pwm2), WRITE); // PA0 TIM2 CH1, PWMA LEFT
}

enc_t enc_val()
{
    static enc_t enc_data;
    static float last = 0;
    float now;
    static bool first_entry = true;
    static uint16_t enc_val_r = 0;
    static uint16_t enc_val_l = 0;
    static uint8_t next_r = 1;
    static uint8_t next_l = 1;

    if (first_entry)
    {
        first_entry = false;
        last = HAL_GetTick();
    }

    now = HAL_GetTick();
    float dt = (now - last); // ms

    if (dt <= 20)
    {
        // right
        if ((GPIOB->IDR & (1 << 4)) && (next_r == 1))
        {
            enc_val_r++;
            next_r = 0;
        }
        if ((!(GPIOB->IDR & (1 << 4))) && (next_r == 0))
        {
            enc_val_r++;
            next_r = 1;
        }

        // left
        if ((GPIOB->IDR & (1 << 0)) && (next_l == 1))
        {
            enc_val_l++;
            next_l = 0;
        }
        if ((!(GPIOB->IDR & (1 << 0))) && (next_l == 0))
        {
            enc_val_l++;
            next_l = 1;
        }
    }
    else
    {
        enc_data.encoder_count_r = (float)(enc_val_r * 0.5) / (float)(dt * 0.001); // c per sec
        enc_data.encoder_count_l = (float)(enc_val_l * 0.5) / (float)(dt * 0.001);
        enc_val_r = 0;
        enc_val_l = 0;
        last = HAL_GetTick();
    }

    return enc_data;
}