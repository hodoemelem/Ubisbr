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
#include <stdbool.h>
#include "filter.h"
#include "filter_def.h"
#include "queue.h"
#include "usart_comm.h"
#include "complementary_filter.h"

static void filter_param_init(filter_param_t filter_param);
static bool create_once = true;
static filter_t *self = NULL;

// constructor and destructor ============================================
filter_t *const filter_create(filter_param_t filter_param)
{
    if (create_once)
    {
        self = (filter_t *)malloc(sizeof(filter_t));
        filter_param_init(filter_param);
        create_once = false;
    }
    return self;
}

void filter_destory(filter_t *self)
{
    free(self);
}

// Private members =======================================================

static void filter_param_init(filter_param_t filter_param)
{
    self->filter_param.gain =  filter_param.gain;
}

filter_t filter_process_data_ex()
{

    float new_angle[1];

    sensor_process_data_ex();
    self->enc_data = sensor_ouput_data().enc_data;
    self->imu_data = sensor_ouput_data().imu_data;
    comp_filter_angle(self->imu_data,new_angle,1);
    self->compf_data.pitch = new_angle[0];

    return (*self);
}

filter_t filter_output_data()
{
	return (*self);
}
