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
#ifndef IMU_H
#define IMU_H
#include <stdbool.h>
#define PWR_MGMT_1 0x6B		  // Power Management. Typical values:0x00(run mode)
#define ADDRESS_AD0_LOW 0x68  // address pin low (GND), default for InvenSense evaluation board
#define ADDRESS_AD0_HIGH 0x69 // address pin high (VCC)
#define DEFAULT_ADDRESS GYRO_ADDRESS
#define WHO_AM_I_VAL 0x68	  //  identity of MPU6050
//#define WHO_AM_I_VAL 0x71	 //  identity of MPU9255 is 0x73 , cMPU9250 is 0x71
#define WHO_AM_I_VAL_MAG 0x48 //  MPU9255 or MPU9250
#define WHO_AM_I 0x75		  // identity of the device
#define ACCEL_XOUT_H 0x3B
#define ACCEL_XOUT_L 0x3C
#define ACCEL_YOUT_H 0x3D
#define ACCEL_YOUT_L 0x3E
#define ACCEL_ZOUT_H 0x3F
#define ACCEL_ZOUT_L 0x40

#define GYRO_XOUT_H 0x43
#define GYRO_XOUT_L 0x44
#define GYRO_YOUT_H 0x45
#define GYRO_YOUT_L 0x46
#define GYRO_ZOUT_H 0x47
#define GYRO_ZOUT_L 0x48

#define SMPLRT_DIV 0x19	  // Sample Rate Divider. Typical values:0x07(125Hz) 1KHz internal sample rate
#define CONFIG 0x1A		  // Low Pass Filter.Typical values:0x06(5Hz)
#define GYRO_CONFIG 0x1B  // Gyro Full Scale Select. Typical values:0x10(1000dps)
#define ACCEL_CONFIG 0x1C // Accel Full Scale Select. Typical values:0x01(2g)

// MAG:AK8963
#define AK8963_ADDRESS 0x0C // Address of magnetometer
#define WHO_AM_I_MAG 0x00	// (AKA WIA) should return 0x48
#define INFO 0x01
#define MAG_ST1 0x02 // data ready status bit 0
#define MAG_XOUT_L 0x03
#define MAG_XOUT_H 0x04
#define MAG_YOUT_L 0x05
#define MAG_YOUT_H 0x06
#define MAG_ZOUT_L 0x07
#define MAG_ZOUT_H 0x08

#define MAG_ST2 0x09					// Data overflow bit 3 and data read error status bit 2
#define MAG_CNTL 0x0A					// Power down (0000), single-measurement (0001), self-test (1000) and Fuse ROM (1111) modes on bits 3:0
#define MAG_ASTC 0x0C					// Self test control
#define MAG_I2CDIS 0x0F					// I2C disable
#define MAG_ASAX 0x10					// Fuse ROM x-axis sensitivity adjustment value
#define MAG_ASAY 0x11					// Fuse ROM y-axis sensitivity adjustment value
#define MAG_ASAZ 0x12					// Fuse ROM z-axis sensitivity adjustment value
#define mRes 10.0f * 4912.0f / 32760.0f // 16-bit magnetometer resolution |  16-bit (0.15 µT/LSB)


typedef struct imu
{
    float accXn;
    float accYn;
    float accZn;
    float gyroXn;
    float gyroYn;
    float gyroZn;
    float magXn;
    float magYn;
    float magZn;
} imu_t;

void init_mpu(void);
imu_t update_mpu_imu();
#endif 