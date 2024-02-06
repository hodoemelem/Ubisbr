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
#include "arm_math.h" // ARM::CMSIS:DSP
#include "radio.h"
#include "usart.h"
#include "usart_comm.h"
#include <stdio.h>

uint8_t ibus[radio_buffer] = {0};
uint16_t channels[channel_on]; // 10
static uint16_t calc_checksum(const uint8_t ch_data[]);
const uint16_t header = 32;
void process_ibus(void)
{
    uint8_t empty_buffer[radio_buffer] = {0};
    // 32 Max iBus packet size (2 byte header, 14 channels x 2 bytes, 2 byte checksum)
    //  TX only has 10 channels
    uint8_t ch_data[radio_buffer] = {0};

    if ((ibus[0] == header) && (ibus[1] == header * 2)) // check the header
    {
        memcpy(ch_data, ibus, sizeof(ch_data));
        if (calc_checksum(ch_data) == (ch_data[30] | (ch_data[31] << 8)))
        {
            // process iBus buffer into channels
            for (uint8_t i = 2, ch = 0; ch < channel_on; i = i + 2, ch++)
            {
                channels[ch] = ch_data[i] | (ch_data[i + 1] << 8);
            }

        }
        // reset buffer values
        memcpy(ibus, empty_buffer, sizeof(ibus));
        memcpy(ch_data, empty_buffer, sizeof(ch_data));
    }
}
static uint16_t calc_checksum(const uint8_t ch_data[])
{
    uint16_t checksum = 65535;
    for (uint8_t i = 0; i <= 29; i++)
    {
        checksum -= ch_data[i];
    }
    return checksum;
}
uint8_t update_channels(void)
{
    if (DMA_ISR_r(TCIF5))
    {
        // process inbus buffer into channels
        process_ibus();
        // restart dma
        usart1_radio_dma_restart();
        return 1;
    }
    return 0;
}
