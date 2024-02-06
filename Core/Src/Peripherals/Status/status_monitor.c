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
#include "io.h"
#include "peri_clock.h"
#include "status_monitor.h"
#include "usart.h"

TaskHandle_t Status_indicator_Handle;
BaseType_t Status_indicator_return_Handle;

TickType_t xLastWakeTime;
static int tick_time = 1000; // ticks 1 tick -> 1ms, 3ticks -> 3ms -> 333Hz  loop freq
static bool lunch_once = true;
bool is_status_task_resumed = false;

void status_led();
void status_monitor(void *pvParameters);

void status_monitor_init()
{
	GPIO_MODER_w(PORTA, MODE5, OUTPUT);
}
void status_monitor_lunch()
{
	if (lunch_once)
	{
		Status_indicator_return_Handle = xTaskCreate(status_monitor, "Status indicator Activity Task",
													 128 * 4,
													 NULL, MONITOR_PRIORITY, &Status_indicator_Handle);
		lunch_once = false;
	}
}
void status_led()
{
	GPIO_BSRR_w(PORTA, BS5, SETBIT);						   // LED ON
	vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(tick_time)); // 100 tick -> 100 ms -> 10Hz
	GPIO_BSRR_w(PORTA, BR5, SETBIT);						   // LED OFF
	vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(tick_time));
}
void status_monitor(void *pvParameters)
{
	// Initialize the xLastWakeTime variable with the current time.
	xLastWakeTime = xTaskGetTickCount();
	while (1)
	{
		status_led();
	}
}

void monitor_status(enum control_states ctrl_state)
{
	if ((ctrl_state == controller_enabled))
	{
		if (is_status_task_resumed == true)
		{
			is_status_task_resumed = false;
			vTaskSuspend(Status_indicator_Handle);
			GPIO_BSRR_w(PORTA, BS5, SETBIT); // LED ON
		}
	}
	else
	{
		if (is_status_task_resumed == false)
		{
			is_status_task_resumed = true;
			vTaskResume(Status_indicator_Handle);
		}
	}
}