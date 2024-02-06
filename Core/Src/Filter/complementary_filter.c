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

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "usart_comm.h"
#include "complementary_filter.h"
#include <math.h>
#include "stm32l4xx_hal.h"
#include "Kalman.h"

#define M_PI 3.14159265358979323846 /* pi */

void comp_filter_angle(imu_t imu_data, float *new_angle, uint8_t len)
{
    // static float angle_pitch_acc = 0;
    // static float angle_pitch = 0;
    // static float alpha = 0.95;
    // static bool first_entry = true;
    // static double to_deg = ((double)180.0 / M_PI);
    // double resultant = 0;
    // static float last = 0;
    // float now;

    // resultant = sqrt((imu_data.accXn * imu_data.accXn) + (imu_data.accYn * imu_data.accYn) + (imu_data.accZn * imu_data.accZn)); // should be approx. 1.0

    // if (resultant < 1.5f)
    // {
    //     angle_pitch_acc = atan2(imu_data.accYn, imu_data.accZn) * to_deg;

    //     if (first_entry)
    //     {
    //         angle_pitch = angle_pitch_acc;
    //         first_entry = false;
    //         last = HAL_GetTick();
    //     }
    //     else
    //     {
    //         now = HAL_GetTick();
    //         float dt = (now - last) * 0.001;
    //         last = now;
    //         angle_pitch = ((angle_pitch + (imu_data.gyroXn * dt)) * alpha + angle_pitch_acc * (1.0 - alpha));
    //     }
    // }

    // new_angle[0] = angle_pitch;

    static float angle_pitch_acc = 0;
    static float angle_pitch = 0;
    static float alpha = 0.95;
    static bool first_entry = true;
    static double to_deg = ((double)180.0 / M_PI);
    double resultant = 0;
    static float last = 0;
    float now;

    resultant = sqrt((imu_data.accXn * imu_data.accXn) + (imu_data.accYn * imu_data.accYn) + (imu_data.accZn * imu_data.accZn)); // should be approx. 1.0

    if (resultant < 1.5f)
    {
        angle_pitch_acc = atan2(imu_data.accYn, imu_data.accZn) * to_deg;

        if (first_entry)
        {
            setAngle(angle_pitch_acc,0, 0);
            init_Kalman(angle_pitch_acc, 0, 0);
            angle_pitch = angle_pitch_acc;
            first_entry = false;
            last = HAL_GetTick();

        }
        else
        {
            now = HAL_GetTick();
            float dt = (now - last) * 0.001;
            last = now;
            angle_pitch = ((angle_pitch + (imu_data.gyroXn * dt)) * alpha + angle_pitch_acc * (1.0 - alpha));
            //getAngle_R(angle_pitch_acc, imu_data.gyroXn , dt, &angle_pitch);

        }
    }

    new_angle[0] = angle_pitch;
}