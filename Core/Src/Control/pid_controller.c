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

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"
#include "pid_controller.h"
#include "math.h"
#include "stdlib.h"
#include <stdbool.h>
#include "usart_comm.h"
#include "filter.h"
#include "radio.h"


typedef struct pid
{
    float integral;
    bool is_saturated;
    bool is_same_sign;
    float correction_limit; // max counts at max pwm
    float error;
    float correction;
    float correction_temp;
    float p_gain;
    float i_gain;
    float d_gain;
    float dt;

    float pwm_output;
    float angle_setpoint;

} pid_param_t;

pid_param_t pid_angle_param;
pwm_t pwm_data;


float max_correction_angle = 5000.0f;
filter_t filter_data_a;
float turn_speed = 1000.0f;
float pitch_off_limit = 45.0f;

static float calc_integral(bool is_saturated, bool is_same_sign, float error, float integral, float dt);
static bool check_saturation(float correction, float correction_temp);
static bool check_sign(float correction, float error);
static float limit_correction_angle(float correction, float limit);
static float pid_controller_angle(const filter_t filter_data);
void motion_direction(enum motion_states motion_state);

void pid_controller_init(const float dt)
{

    //////////////////////////Angle
    pid_angle_param.integral = 0.0f;
    pid_angle_param.is_saturated = false;
    pid_angle_param.is_same_sign = false;
    pid_angle_param.correction_limit = max_correction_angle;
    pid_angle_param.dt = dt;

    // pid_angle_param.p_gain = 250.0;
    // pid_angle_param.i_gain = 3500;
    // pid_angle_param.d_gain = 20;

    pid_angle_param.p_gain = 750.0;
    pid_angle_param.i_gain = 9000.0;
    pid_angle_param.d_gain = 40.0;

    pid_angle_param.angle_setpoint = 0;
}

pwm_t pid_controller(const setpoint_t setpoint, const filter_t filter_data, enum motion_states motion_state)
{

    filter_data_a = filter_data;
    float speed_setpoint = pid_controller_angle(filter_data);

    pid_angle_param.pwm_output = pid_angle_param.correction_temp > 0 ? speed_setpoint : -1 * speed_setpoint;

    pwm_data.pwm1 = pid_angle_param.pwm_output;
    pwm_data.pwm2 = pid_angle_param.pwm_output;

    motion_direction(motion_state);

    return pwm_data;
}

void motion_direction(enum motion_states motion_state)
{
    static float limit = 0.0f;
    switch (motion_state)
    {

    case forward_mode1:
        limit = -0.8f;
        break;
    case backward_mode1:
        limit = 1.5f;
        break;

    case forward_mode2:
        limit = -0.8f;
        break;
    case backward_mode2:
        limit = 1.5f;
        break;

    case forward_mode3:
        limit = -2.5f;
        break;
    case backward_mode3:
        limit = 2.5f;
        break;

    case turn_left:
        pid_angle_param.angle_setpoint = 0;
        pwm_data.pwm1 -= turn_speed;
        pwm_data.pwm2 += turn_speed;
        break;

    case turn_right:
        pid_angle_param.angle_setpoint = 0;
        pwm_data.pwm1 += turn_speed;
        pwm_data.pwm2 -= turn_speed;
        break;

    case stand_still:
        if (fabs(pid_angle_param.angle_setpoint) <= 0.3)
        {
            pid_angle_param.angle_setpoint = 0;
        }
        else
        {
            pid_angle_param.angle_setpoint -= 0.25 * pid_angle_param.angle_setpoint;
        }
        break;

    default:
        break;
    }

    static enum motion_states last_state = stand_still;
    if (motion_state <= backward_mode3)
    {
        if (last_state != motion_state)
        {
            pid_angle_param.angle_setpoint = 0;
        }
        last_state = motion_state;

        if (fabs(pid_angle_param.angle_setpoint) < fabs(limit))
        {
            pid_angle_param.angle_setpoint += 0.25 * limit;
        }
        else
        {
            pid_angle_param.angle_setpoint = limit;
        }
    }

    if (fabs(filter_data_a.compf_data.pitch) >= pitch_off_limit)
    { // restart controller
        pwm_data.pwm1 = 0;
        pwm_data.pwm2 = 0;
        pid_controller_init(0.003);
    }
}

static float pid_controller_angle(const filter_t filter_data)
{
    static float angle;
    angle = (-1 * filter_data.compf_data.pitch);

    static float last = 0;
    float now;
    now = HAL_GetTick();
    float dt = (now - last) * 0.001;
    last = now;
    static bool first_entry = true;
    if (!first_entry)
    {
        pid_angle_param.dt = dt;
    }

    first_entry = false;

    pid_angle_param.error = pid_angle_param.angle_setpoint - angle;

    pid_angle_param.integral = calc_integral(pid_angle_param.is_saturated, pid_angle_param.is_same_sign, pid_angle_param.error, pid_angle_param.integral, pid_angle_param.dt);
    pid_angle_param.correction = pid_angle_param.p_gain * pid_angle_param.error + pid_angle_param.i_gain * pid_angle_param.integral + pid_angle_param.d_gain * (filter_data.imu_data.gyroXn);

    pid_angle_param.correction_temp = pid_angle_param.correction;
    pid_angle_param.correction = limit_correction_angle(fabs(pid_angle_param.correction), pid_angle_param.correction_limit);

    pid_angle_param.is_saturated = check_saturation(fabs(pid_angle_param.correction), fabs(pid_angle_param.correction_temp));
    pid_angle_param.is_same_sign = check_sign(pid_angle_param.correction_temp, pid_angle_param.error);

    return pid_angle_param.correction;
}

static float limit_correction_angle(float correction, float correction_limit)
{
    if (correction > correction_limit)
    {
        correction = correction_limit;
    }
    return correction;
}

static float calc_integral(bool is_saturated, bool is_same_sign, float error, float integral, float dt)
{
    return (is_saturated && is_same_sign) ? integral : (integral + (error * dt));
}

static bool check_saturation(float correction, float correction_temp)
{
    return !(correction == correction_temp) ? true : false;
}

static bool check_sign(float correction, float error)
{
    return (correction * error) > 0 ? true : false;
}
