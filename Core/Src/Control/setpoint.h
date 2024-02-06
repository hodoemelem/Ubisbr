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
#ifndef SETPOINT_H
#define SETPOINT_H

#define CH_ROL (0)
#define CH_PIT (1)
#define CH_THR (2)
#define CH_YAW (3)
#define CH_SWA (4)
#define CH_SWB (5)
#define CH_SWC (6)
#define CH_SWD (7)
#define CH_VRA (8)
#define CH_VRB (9) 



typedef struct setpoint
{
    float encoder_count;
} setpoint_t;

setpoint_t update_setpoints();
#endif