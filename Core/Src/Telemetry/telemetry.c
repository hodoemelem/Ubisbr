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
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "telemetry.h"
#include "telemetry_def.h"
#include "queue.h"
#include "usart_comm.h"
#include "radio.h"
#include "ubi_def.h"
#include "setpoint.h"

static bool lunch_once = true;
static void telemetry_run(void *const tel_ptr);
static bool telemetry_update_input_data(telemetry_t *const tel, const data_type_t input_type);
static void telemetry_process_data(const tx_t output[], const size_t output_len);
static void send(telemetry_t *const tel, const data_type_t input_type, const tx_t output[], size_t output_len);

// constructor and destructor ============================================

TaskHandle_t telemetry_run_Handle;
BaseType_t telemetry_run_return_Handle;

// Public members ========================================================

BaseType_t telemetry_lunch_thread()
{
    if (lunch_once)
    {
        telemetry_run_return_Handle = xTaskCreate(telemetry_run, "Telemetry Activity Task",
                                                  STACK_SIZE,
                                                  (void *)&tel, TELEMETRY_PRIORITY, &telemetry_run_Handle);
        lunch_once = false;
    }
    return telemetry_run_return_Handle;
}

// Private members =======================================================
static void telemetry_run(void *const tel_ptr)
{
    TickType_t xLastWakeTime;
    // Initialize the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount();
    int tick_time = 100; // 10 hz

    telemetry_t *const tel = (telemetry_t *)tel_ptr;
    while (true)
    {
        send(tel, SENSOR, output_sensor, output_sensor_n);
        send(tel, FILTER, output_filter, output_filter_n);
        send(tel, CONTROLLER, output_ctrl, output_ctrl_n);
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(tick_time));
    }
    free(tel);
}

static void send(telemetry_t *const tel, const data_type_t input_type, const tx_t output[], const size_t output_len)
{
    if (telemetry_update_input_data(tel, input_type))
        telemetry_process_data(output, output_len);
}

static void telemetry_process_data(const tx_t output[], const size_t output_len)
{

    int i;
    for (i = 0; i < output_len; i++)
    {
        char msg[50] = {'\0'};
        sprintf(msg, "%s:%0.2f\n", output[i].id, *(output[i].data));
        usart2_tx(msg); // direct visualization
        usart3_tx(msg); // direct visualization
    }
    usart2_tx("\n"); // direct visualization
    usart3_tx("\n");
}

static bool telemetry_update_input_data(telemetry_t *const tel, const data_type_t input_type)
{
    switch (input_type)
    {
    case CONTROLLER:
        xQueueReceive(controller_telemetry_q, &(tel->ctrl), (TickType_t)0);
        return true;
        break;
    case FILTER:
        tel->filter = filter_output_data();
        return true;
        break;
    case SENSOR:
        tel->sensor = sensor_ouput_data();
        return true;
        break;
    default:
        break;
    }
    return false;
}
