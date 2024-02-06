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
#ifndef TELEMETRY_DEF_H
#define TELEMETRY_DEF_H

#include "telemetry.h"

typedef enum data_type
{
  CONTROLLER = 0,
  FILTER,
  SENSOR
} data_type_t;
typedef struct telemetry
{
  // inputs
  sensor_t sensor;
  filter_t filter;
  controller_t ctrl;
} telemetry_t;
telemetry_t tel;

typedef struct tx
{
  const float *const data;
  const char *id;
} tx_t;



const tx_t output_sensor[] = {
    // Sensor
    {&tel.sensor.enc_data.encoder_count_r, "s_encoder_count_r"},
    {&tel.sensor.enc_data.encoder_count_l, "s_encoder_count_l"},
};

const size_t output_sensor_n = sizeof(output_sensor) / sizeof(output_sensor[0]);

const tx_t output_filter[] = {
    // Filter
    {&tel.filter.enc_data.encoder_count_r, "f_encoder_count_r"},
    {&tel.filter.enc_data.encoder_count_l, "f_encoder_count_l"},
    {&tel.filter.compf_data.pitch, "f_pitch_x"},
};
const size_t output_filter_n = sizeof(output_filter) / sizeof(output_filter[0]);

const tx_t output_ctrl[] = {
    // Controller
    {&tel.ctrl.pwm_data.pwm1, "c_pwm1"},
    {&tel.ctrl.pwm_data.pwm2, "c_pwm2"},
    {&tel.ctrl.setpoint_data.encoder_count, "c_encoder_count_ref"},
    {&tel.ctrl.filter_data.enc_data.encoder_count_r, "c_encoder_count_r"},
    {&tel.ctrl.filter_data.enc_data.encoder_count_l, "c_encoder_count_l"},
};

const size_t output_ctrl_n = sizeof(output_ctrl) / sizeof(output_ctrl[0]);
#endif // TELEMETRY_DEF_H
