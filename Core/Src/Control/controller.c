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
#include "pid_controller.h"
#include "controller.h"
#include "controller_def.h"
#include "queue.h"
#include "radio.h"
#include "status_monitor.h"
#include "usart_comm.h"
#include "imu.h"
#include "stm32l4xx_hal.h"

static enum control_states ctrl_state = controller_disabled;


static void controller_run(void *const self_);
static void controller_update_output_data(controller_t *const self);
static void controller_process_data();
static int8_t motion();

QueueHandle_t controller_telemetry_q;
TaskHandle_t controller_run_Handle;
BaseType_t controller_run_return_Handle;
static bool create_once = true;
static bool lunch_once = true;
static uint8_t tick_time = 3;
static controller_t *self = NULL;

// constructor and destructor ============================================
controller_t *const controller_create()
{
    if (create_once)
    {
        self = (controller_t *)malloc(sizeof(controller_t));
    }
    return self;
}

void controller_destory(controller_t *self)
{
    free(self);
}

// Public members ========================================================
BaseType_t controller_lunch_thread(controller_t *const self)
{
    if (lunch_once)
    {
        controller_telemetry_q = xQueueCreate(QUEUE_LENGTH, sizeof(controller_t));
        controller_run_return_Handle = xTaskCreate(controller_run, "Controller Activity Task",
                                                   STACK_SIZE,
                                                   (void *)self, CONTROLLER_PRIORITY, &controller_run_Handle);
        lunch_once = false;
    }
    return controller_run_return_Handle;
}

// Private members =======================================================

static void controller_run(void *const self_)
{
    TickType_t xLastWakeTime;
    // Initialize the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount();

    while (true)
    {
        controller_process_data();
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(tick_time));
    }
}

static void controller_process_data()
{
    uint16_t CH_MID = 1500;

    update_channels();
    self->setpoint_data = update_setpoints();
    self->filter_data = filter_process_data_ex();


    switch (ctrl_state)
    {
    case first_start_stage:
        if (channels[CH_SWA] > CH_MID) // radio SWD  to activate  system
        {
            pid_controller_init(tick_time * 0.001);
            self->pwm_data = turn_motors_off();
            ctrl_state = controller_enabled;
        }
        break;
    case controller_enabled:
        if ((channels[CH_SWA] < CH_MID))
        {
            ctrl_state = controller_disabled;
            break;
        }

        self->pwm_data = pid_controller(self->setpoint_data, self->filter_data, motion());
        set_motors_pwm(self->pwm_data);
        break;
    case controller_disabled:
        self->pwm_data = turn_motors_off();
        pid_controller_init(tick_time * 0.001);
        ctrl_state = first_start_stage;
        break;
    default:
        break;
    }

    controller_update_output_data(self);
    monitor_status(ctrl_state);
}

static int8_t motion()
{
    int16_t pitch_ch = channels[CH_PIT];
    int16_t yaw_ch = channels[CH_YAW];

    if (yaw_ch >= 1600)
    {
        return turn_left;
    }
    else if (yaw_ch <= 1400)
    {
        return turn_right;
    }

    if ((pitch_ch >= 1550) && (pitch_ch <= 1650))
    {
        return forward_mode1;
    }
    else if ((pitch_ch > 1650) && (pitch_ch <= 1850))
    {
        return forward_mode2;
    }
    else if (pitch_ch > 1850)
    {
        return forward_mode3;
    }
    else if ((pitch_ch >= 1350) && (pitch_ch <= 1450))
    {
        return backward_mode1;
    }
    else if ((pitch_ch >= 1150) && (pitch_ch < 1350))
    {
        return backward_mode2;
    }
    else if (pitch_ch < 1150)
    {
        return backward_mode3;
    }
    else if ((pitch_ch > 1450) && (pitch_ch < 1550))
    {
        return stand_still;
    }

    return stand_still;
}
controller_t ctrl_output_data()
{
    return (*self);
}

static void controller_update_output_data(controller_t *const self)
{
    xQueueSend(controller_telemetry_q, (void *)self, (TickType_t)0);
}
