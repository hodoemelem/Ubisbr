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
#ifndef TIMER_H
#define TIMER_H
#include <stdlib.h>
#include <math.h>


typedef struct pwm
{
	float pwm1;
	float pwm2;
    float pwm3;
    float pwm4;
} pwm_t;

typedef struct enc
{
    float encoder_count_r;
    float encoder_count_l;
} enc_t;

void motor_init(void);
void encoder_init();
pwm_t turn_motors_off(void);
void set_motors_pwm(pwm_t pwm);
enc_t enc_counts();
enc_t enc_val();
void  timer_init();
void sbr_gpio_init();
#endif