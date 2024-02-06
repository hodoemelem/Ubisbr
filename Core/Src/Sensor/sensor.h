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
#ifndef SENSOR_H
#define SENSOR_H
#include "ubi_def.h"
#include "imu.h"
#include "timer.h"

typedef struct sensor_parameter
{
	float alpha;
} sensor_param_t;

typedef struct sensor
{
	enc_t enc_data;
	imu_t imu_data;
	sensor_param_t sensor_param;
} sensor_t;


sensor_t * const sensor_create(sensor_param_t sensor_param);
void sensor_destory(sensor_t *self);
sensor_t sensor_process_data_ex(void);
sensor_t sensor_ouput_data();


#endif // SENSOR_H
