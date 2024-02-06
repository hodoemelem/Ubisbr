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
#ifndef FILTER_H
#define FILTER_H
#include "sensor.h"
#include "ubi_def.h"
#include "timer.h"
#include "complementary_filter.h"

typedef struct filter_parameter
{
	float gain;
} filter_param_t;


typedef struct filter
{
	enc_t enc_data;
	imu_t imu_data;
	compf_t compf_data;
	filter_param_t filter_param;
} filter_t;

filter_t *const filter_create(filter_param_t filter_param);
void filter_destory(filter_t *self);
filter_t filter_output_data();
filter_t filter_process_data_ex();
#endif // FILTER_H
