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
#ifndef CONTROLLER_H
#define CONTROLLER_H

/* ------- Project Specific includes ------- */
#include "filter.h"
#include "ubi_def.h"
#include "timer.h"
#include "setpoint.h"


typedef struct controller
{
    pwm_t pwm_data;
    setpoint_t setpoint_data;
    filter_t filter_data;
} controller_t;

/** @brief 
 *
 * 
 *  @param 
 *  @return 
 */
controller_t *const controller_create();

/** @brief 
 *
 * 
 *  @param 
 *  @return 
 */
void controller_destory(controller_t *self);

/** @brief 
 *
 * 
 *  @param 
 *  @return 
 */
controller_t ctrl_output_data();

/** @brief 
 *
 * 
 *  @param 
 *  @return 
 */
BaseType_t controller_lunch_thread(controller_t *const self);

#endif // CONTROLLER_H