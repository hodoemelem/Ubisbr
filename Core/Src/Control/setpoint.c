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
#include "arm_math.h" // ARM::CMSIS:DSP
#include "radio.h"
#include "setpoint.h"

#define CH_MAX 2000
#define CH_MID 1500
#define CH_MIN 1000

static float min_correction = 118.0f;
static float max_correction = 1379.0f;

static setpoint_t setpoint_data;

static float map_ch_ref(float ref_max, float ref_min, uint16_t ch_max, uint16_t ch_min, uint16_t ch_val);

static float map_ch_ref(float ref_max, float ref_min, uint16_t ch_max, uint16_t ch_min, uint16_t ch_val)
{
    return (ref_min + ((ch_val - ch_min) * (ref_max - ref_min)) / (ch_max - ch_min));
}

setpoint_t update_setpoints()
{
    uint16_t setpoint = channels[CH_THR];
    if (setpoint > CH_MAX)
    {
        setpoint = CH_MAX;
    }
    else if (setpoint < CH_MIN)
    {
        setpoint = CH_MIN;
    }

    setpoint_data.encoder_count = map_ch_ref(max_correction, min_correction, CH_MAX, CH_MIN, setpoint);

    return setpoint_data;
}