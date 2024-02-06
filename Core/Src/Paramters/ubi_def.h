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
#ifndef UBI_DEF_H
#define UBI_DEF_H
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#define CONTROLLER_PRIORITY 3
#define FILTER_PRIORITY 3
#define SENSOR_PRIORITY 3
#define TELEMETRY_PRIORITY 2
#define MONITOR_PRIORITY 1

#define STACK_SIZE 128 * 4
#define QUEUE_LENGTH 5

extern QueueHandle_t sensor_telemetry_q;
extern QueueHandle_t filter_telemetry_q;
extern QueueHandle_t controller_telemetry_q;

extern QueueHandle_t sensor_filter_q;
extern QueueHandle_t filter_controller_q;

extern TaskHandle_t Status_indicator_Handle;
extern TaskHandle_t controller_run_Handle;
extern TaskHandle_t telemetry_run_Handle;

enum control_states
{
    first_start_stage,
    second_start_stage,
    controller_enabled,
    controller_disabled,
    end_control
};

enum motion_states
{
    forward_mode1,
    forward_mode2,
    forward_mode3,
    backward_mode1,
    backward_mode2,
    backward_mode3,
    stand_still,
    turn_left,
    turn_right,
    end_motion
};
#endif // UBI_DEF_H