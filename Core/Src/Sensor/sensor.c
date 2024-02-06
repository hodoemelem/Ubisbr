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
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <stdbool.h>
#include "usart_comm.h"
#include "sensor.h"
#include "sensor_def.h"
#include "queue.h"
#include "radio.h"
#include "stm32l4xx_hal.h"


QueueHandle_t sensor_telemetry_q;
QueueHandle_t sensor_filter_q;
TaskHandle_t sensor_run_Handle;
BaseType_t sensor_run_return_Handle;
static bool create_once = true;
static void sensor_param_init(sensor_param_t sensor_param);
static sensor_t *self = NULL;

// constructor and destructor ============================================
sensor_t *const sensor_create(sensor_param_t sensor_param)
{
	if (create_once)
	{
		self = (sensor_t *)malloc(sizeof(sensor_t));
		sensor_param_init(sensor_param);
		create_once = false;
	}
	return self;
}
void sensor_destory(sensor_t *self)
{
	free(self);
}

// Private members =======================================================
static void sensor_param_init(sensor_param_t sensor_param)
{
	self->sensor_param.alpha =  sensor_param.alpha;
}

sensor_t sensor_process_data_ex()
{

	self->enc_data = enc_counts();
	self->imu_data = update_mpu_imu();
	
	// char msg[100];
	// sprintf(msg, "************************Sen enc , %0.2f ,  %0.2f \n", enc_data.encoder_count_s,   imu_data.pitch_x);
	// usart2_tx(msg);

	return (*self);
}

sensor_t sensor_ouput_data()
{
	return (*self);
}

//////////////////////////////////
