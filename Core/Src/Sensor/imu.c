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
#include "imu.h"
#include <stdio.h>
#include "stm32l476xx.h"
#include <stdlib.h>
#include "arm_math.h" // ARM::CMSIS:DSP
#include "i2c.h"
#include "peri_clock.h"
#include "usart_comm.h"
#include <math.h>
#include "Kalman.h"
#include "MedianFilter.h"

#define M_PI 3.14159265358979323846 /* pi */

#define ACCEL_4g 0x08        // +-4g
#define GYRO_500dps 0x08     //+-500dps
#define RUN_MODE 0x00        // run mode
#define CUTOFF_HZ 0x06       // DLPF cutoff freq of %5Hz cutoff
#define UPDATE_HZ 0x02       // update sensor reg. at 500Hz
#define MAG_PWR_DOWN 0x00    //// Power down magnetometer
#define ROM_ACCESS_MODE 0x0F ////Enter Fuse ROM access mode
#define MAG_RES 0x16         // Set magnetometer data resolution to 16bits and mode to continuous mode 2
#define BYPASS_REG 0x37
#define BYPASS_EN 0x02

double gx_offset = 0;
double gy_offset = 0;
double gz_offset = 0;

static imu_t imu_data;

static char msg[100];
static void gyro_calib(void);
static void init();
static uint8_t read_accelerometer();
static uint8_t read_gyro();
static void init_acc_gyro();

static void init_acc_gyro()
{
    sprintf(msg, "MPU starting\n");
    usart2_tx(msg);
    // this piece of code keeps initializing i2c until it is successful
    int who_i_be = 0;
    do
    {
        i2c1_init();
        uint8_t read_buffer[1];
        if (i2c1_read(ADDRESS_AD0_LOW, WHO_AM_I, 1, read_buffer))
        {
            who_i_be = read_buffer[0];
        }
    } while (who_i_be != WHO_AM_I_VAL);

    sprintf(msg, "MPU ID %d,MPU i2c1 OK\n", who_i_be);
    usart2_tx(msg);

    config_12c1_node(ADDRESS_AD0_LOW, ACCEL_CONFIG, ACCEL_4g, 1);   // +-4g
    config_12c1_node(ADDRESS_AD0_LOW, GYRO_CONFIG, GYRO_500dps, 1); //+-500dps
    config_12c1_node(ADDRESS_AD0_LOW, PWR_MGMT_1, RUN_MODE, 1);     // run mode
    config_12c1_node(ADDRESS_AD0_LOW, CONFIG, CUTOFF_HZ, 1);        // DLPF cutoff freq of %5Hz cutoff
    config_12c1_node(ADDRESS_AD0_LOW, SMPLRT_DIV, UPDATE_HZ, 1);    // update sensor reg. at 500Hz
}

static void init()
{
    init_acc_gyro();
    gyro_calib();
}

void init_mpu(void)
{
    init();
    bool first_entry = true;
    int count_to_reset = 0;
    float resultant = 0;
    int reset_limit = 100;
    while (first_entry)
    {
        read_accelerometer();
        resultant = sqrt((imu_data.accXn * imu_data.accXn) + (imu_data.accYn * imu_data.accYn) + (imu_data.accZn * imu_data.accZn)); // should be approx. 1.0

        count_to_reset++;
        if (count_to_reset >= reset_limit) // reset mpu imu until accelerometer value is correct
        {
            if ((resultant > 1.5f))
            {
                init();
            }
            else
            {
                first_entry = false;
                sprintf(msg, "\nMPU init. done\n");
                usart2_tx(msg);
            }
            count_to_reset = 0;
        }
    }
}
static void gyro_calib(void)
{
    // Gyro Offset calibration
    int counter = 0;
    float counter_limit = 1000.0f;
    int16_t gyroXD, gyroYD, gyroZD;
    uint8_t read_buffer[6];

    while (counter < counter_limit)
    {
        if (i2c1_read(ADDRESS_AD0_LOW, GYRO_XOUT_H, 6, read_buffer))
        {
            gyroXD = read_buffer[0] << 8 | read_buffer[1];
            gyroYD = read_buffer[2] << 8 | read_buffer[3];
            gyroZD = read_buffer[4] << 8 | read_buffer[5];

            gx_offset += gyroXD;
            gy_offset += gyroYD;
            gz_offset += gyroZD;
            counter++;
        }
    }
    gx_offset = gx_offset / counter_limit;
    gy_offset = gy_offset / counter_limit;
    gz_offset = gz_offset / counter_limit;
}

static uint8_t read_accelerometer()
{
    int16_t accXD, accYD, accZD;
    float sensitivity_4g = 8192.0f;
    uint8_t read_buffer[6];

    if (i2c1_read(ADDRESS_AD0_LOW, ACCEL_XOUT_H, 6, read_buffer))
    {
        accXD = read_buffer[0] << 8 | read_buffer[1];
        accYD = read_buffer[2] << 8 | read_buffer[3];
        accZD = read_buffer[4] << 8 | read_buffer[5];

        // // converting MAV frame to NED frame:  acc. axis is +1g when pointing down
        // //  convert to g,-+4g -> 8192LSB/g
        imu_data.accYn = (double)(((accYD) / sensitivity_4g));
        imu_data.accXn = (double)(((accXD) / sensitivity_4g));
        imu_data.accZn = (double)(((accZD) / sensitivity_4g));
        return 1;
    }
    return 0;
}

static uint8_t read_gyro()
{

    int16_t gyroXD, gyroYD, gyroZD;
    float sensitivity_500dps = 65.5f;
    uint8_t read_buffer[6];
    if (i2c1_read(ADDRESS_AD0_LOW, GYRO_XOUT_H, 6, read_buffer))
    {
        gyroXD = read_buffer[0] << 8 | read_buffer[1];
        gyroYD = read_buffer[2] << 8 | read_buffer[3];
        gyroZD = read_buffer[4] << 8 | read_buffer[5];

        // convert of deg/s, +- 500dps -> 65.5
        // and converting MAV frame to NED frame
        imu_data.gyroYn = ((double)(gyroYD) / sensitivity_500dps);
        imu_data.gyroXn = ((double)(gyroXD ) / sensitivity_500dps);
        imu_data.gyroZn = ((double)(gyroZD) / sensitivity_500dps);
        return 1;
    }
    return 0;
}

imu_t update_mpu_imu()
{
    read_accelerometer();
    read_gyro();
    return imu_data;
}