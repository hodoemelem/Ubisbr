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
#include "usart_comm.h"
void usart2_tx(char *data)
{
    while (*data)
    {
        while (!USART_ISR_r(USART_2, TXE))
            ; // wait for TX buffer(BIT 7) to be empty
        USART_TDR_w(USART_2, *(data++));

        // while (!USART_ISR_r(USART_2, TXE))
        //     ; // wait for TX buffer(BIT 7) to be empty

        // char d = *(data++);
        // if (d == '\0')
        // {
        //     return;
        // }
        // USART_TDR_w(USART_2, d);

        // while (!USART_ISR_r(USART_2, TC))
        //     ;
    }
}

void usart3_tx(char *data)
{
    while (*data)
    {

        while (!USART_ISR_r(USART_3, TXE))
            ; // wait for TX buffer(BIT 7) to be empty
        USART_TDR_w(USART_3, *(data++));

        // while (!USART_ISR_r(USART_3, TXE))
        //     ; // wait for TX buffer(BIT 7) to be empty

        // char d = *(data++);
        // if (d == '\0')
        // {
        //     return;
        // }
        // USART_TDR_w(USART_3, d);

        // while (!USART_ISR_r(USART_3, TC))
        //     ;
    }
}

char usart2_rx(void)
{
    // while (!USART_ISR_r(USART_2, RXNE))
    //     ; // wait for data to be available on RX buffer
    // return USART_RDR_r(USART_2);

    if (USART_ISR_r(USART_2, RXNE))
    { // wait for data to be available on RX buffer
        return USART_RDR_r(USART_2);
    }
    else
    {
        return '0';
    }
}

char usart3_rx(void)
{
    // while (!USART_ISR_r(USART_2, RXNE))
    //     ; // wait for data to be available on RX buffer
    // return USART_RDR_r(USART_2);

    if (USART_ISR_r(USART_3, RXNE))
    { // wait for data to be available on RX buffer
        return USART_RDR_r(USART_3);
    }
    else
    {
        return '0';
    }
}