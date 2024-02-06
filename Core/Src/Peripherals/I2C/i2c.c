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
#include "i2c.h"
#include "peri_clock.h"
#include "usart_comm.h"
#define r_mode 1
#define w_mode 0

#define TIMEOUT 100
#define TIMINGR_VAL 0x00610611 // for mpu

uint8_t check_i2c_isr(uint8_t flag, uint8_t state);
uint8_t check_i2c_cr2(uint8_t flag, uint8_t state);
uint8_t i2c1_start_ret(uint8_t saddr, uint8_t rwmode, uint8_t data_len);
uint8_t i2c1_stop_ret();
uint8_t send_data(uint8_t saddr, uint8_t maddr, uint8_t data_len, uint8_t *buffer);
uint8_t read_data(uint8_t saddr, uint8_t maddr, uint8_t data_len, uint8_t *buffer);
void i2c1_reset(void);

void i2c_init()
{
    // PB8 scl, PB9 sda for i2c
    GPIO_MODER_w(PORTB, MODE8, ALT);
    GPIO_AFR_w(PORTB, AFSEL0_8, I2C, true);
    GPIO_MODER_w(PORTB, MODE9, ALT);
    GPIO_AFR_w(PORTB, AFSEL1_9, I2C, true);
}

void i2c1_init(void)
{ ///////////12c1 for IMU////////////////////////////////////////////////////////////////////////////////////////
    //   pb8,9 open drain rm pg306
    GPIO_OTYPER_wr(PORTB, OT8, SETBIT, WRITE);
    GPIO_OTYPER_wr(PORTB, OT9, SETBIT, WRITE);
    i2c1_reset();
}

void i2c1_reset(void)
{
    I2C_CR1_wr(I2C_1, PE, !SETBIT, WRITE);
    I2C_CR1_wr(I2C_1, PE, !SETBIT, READ);
    I2C_TIMINGR_w(I2C_1, TIMINGR_VAL);
    I2C_CR1_wr(I2C_1, PE, SETBIT, WRITE);
}

void config_12c1_node(uint8_t saddr, uint8_t mem_addr, uint8_t data, uint8_t data_len)
{
    send_data(saddr, mem_addr, data_len, &data);
}

uint8_t i2c1_start_ret(uint8_t saddr, uint8_t rwmode, uint8_t data_len)
{
    I2C_CR2_wr(I2C_1, SADD07, saddr << 1, WRITE); // slave address,sw end mode, write mode(0) on reset
    I2C_CR2_wr(I2C_1, RD_WRN, rwmode, WRITE);     // change to read mode or write mode
    I2C_CR2_wr(I2C_1, NBYTES, data_len, WRITE);   // read/write n number of registers(byte)
    I2C_CR2_wr(I2C_1, RELOAD, !SETBIT, WRITE);    // no reload
    I2C_CR2_wr(I2C_1, AUTOEND, SETBIT, WRITE);    // for auto stop in read mode only
    I2C_CR2_wr(I2C_1, START, SETBIT, WRITE);      // start condition rm pg1327

    if (!check_i2c_cr2(START, !SETBIT))
    { // check if START is reset, that is address is sent
        i2c1_stop_ret();
        return 0;
    }

    return 1;
}

uint8_t i2c1_stop_ret()
{
    I2C_CR2_wr(I2C_1, STOP, SETBIT, WRITE); // stop condition rm pg1327

    if (!check_i2c_cr2(STOP, !SETBIT))
    { // check if STOP flag is Reset
        return 0;
    }

    I2C1->CR2 = 0; // clear CR2 reg

    return 1;
}

uint8_t check_i2c_cr2(uint8_t flag, uint8_t state)
{ // Use for single bit blocks of cr2 only
    uint16_t time_out = 0;
    uint32_t reg_val = 1;

    while (reg_val)
    {
        reg_val = state ? !I2C_CR2_wr(I2C_1, flag, READ, READ) : I2C_CR2_wr(I2C_1, flag, READ, READ);

        time_out++;
        if (time_out >= TIMEOUT)
        {
            // char msg[500];
            // sprintf(msg, "************************Time out check_i2c_cr2 Flag: %d \n", flag);
            // usart2_tx(msg);

            if (flag == STOP)
            {
                i2c1_reset();
                /// clear CR2 reg
                I2C1->CR2 = 0;
            }

            // sprintf(msg, "************************Time out check_i2c_cr2 Flag: %d \n", flag);
            // usart2_tx(msg);

            return 0;
        }
    }
    return 1;
}

uint8_t check_i2c_isr(uint8_t flag, uint8_t state)
{
    uint16_t time_out = 0;
    uint32_t reg_val = 1;

    while (reg_val)
    {
        reg_val = state ? !I2C_ISR_r(I2C_1, flag) : I2C_ISR_r(I2C_1, flag);

        time_out++;
        if (time_out >= TIMEOUT)
        {
            if (flag == TXIS)
            {
                if (I2C_ISR_r(I2C_1, NACKF))
                {
                    // usart2_tx("************************Time out check_i2c_isr Flag: NACKF \n");
                    i2c1_stop_ret();
                    // usart2_tx("************************END Time out check_i2c_isr Flag: NACKF \n");
                    return 0;
                }
            }

            // char msg[500];
            // sprintf(msg, "************************Time out check_i2c_isr Flag: %d\n", flag);
            // usart2_tx(msg);

            i2c1_stop_ret();

            // sprintf(msg, "************************END Time out check_i2c_isr Flag: %d\n", flag);
            // usart2_tx(msg);

            return 0;
        }
    }

    return 1;
}

uint8_t send_data(uint8_t saddr, uint8_t maddr, uint8_t data_len, uint8_t *buffer)
{
    // 2.
    //*************************** Transmit/send data to slave device
    if (!i2c1_start_ret(saddr, w_mode, 1 + data_len)) // call i2c start in write mode
    {
        return 0;
    }
    else
    { // start bit transmit was successfull, now write the reg address
        if (!check_i2c_isr((uint8_t)TXIS, SETBIT))
        { // check if TXIS is set
            return 0;
        }

        I2C_TXDR_w(I2C_1, maddr); // transmit register address
    }

    uint8_t i = 0;
    for (i = 0; i < data_len; i++)
    { // do only if nRegs is > 0
        if (!check_i2c_isr((uint8_t)TXIS, SETBIT))
        { // check if TXIS is set
            return 0;
        }

        I2C_TXDR_w(I2C_1, buffer[i]); // transmit register data
    }

    if (!check_i2c_isr((uint8_t)STOPF, SETBIT))
    { // check if STOPF is set
        return 0;
    }
    I2C1->ICR |= (1 << 5); // clear stop flag
    //*************************** END Transmit/send data to slave device

    return 1;
}

uint8_t read_data(uint8_t saddr, uint8_t maddr, uint8_t data_len, uint8_t *buffer)
{
    //********************* Read from slave
    if (!i2c1_start_ret(saddr, r_mode, data_len)) // call i2c start in read mode
    {
        return 0;
    }

    uint8_t i = 0;
    for (i = 0; i < data_len; i++)
    {
        if (!check_i2c_isr((uint8_t)RXNE_I, SETBIT))
        { // check if RXNE_I is set
            return 0;
        }
        buffer[i] = (uint8_t)I2C_RXDR_r(I2C_1); // rx byte data
    }

    if (!check_i2c_isr((uint8_t)STOPF, SETBIT))
    { // check if STOPF is set
        return 0;
    }
    I2C1->ICR |= (1 << 5); // clear stop flag
    //********************* END Read from slave

    return 1;
}
uint8_t i2c1_read(uint8_t saddr, uint8_t maddr, uint8_t data_len, uint8_t *buffer)
{
    // 1.
    //********************** check if i2c is busy
    if (!check_i2c_isr(BUSY_I, !SETBIT))
    { // check for reset
        return 0;
    }
    //********************** END check if i2c is busy

    // 2.
    //*************************** Transmit/send data to slave device
    if (!send_data(saddr, maddr, 0, NULL))
    {
        return 0;
    }
    //*************************** END Transmit/send data to slave device

    // 3.
    //********************* Read from slave
    if (!read_data(saddr, maddr, data_len, buffer))
    {
        return 0;
    }
    //********************* END Read from slave

    // 4.
    I2C1->CR2 = 0; // clear CR2 reg

    return 1;
}
