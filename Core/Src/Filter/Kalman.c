/*
 * Kalman.c
 *
 *  Created on: Apr 12, 2018
 *      Author: Robin
 */

#include "Kalman.h"
#include "math.h"
#include "stdint.h"

float Q_angle[3];    // Process noise variance for the accelerometer
float Q_gyroBias[3]; // Process noise variance for the gyro bias

float bias[3]; // The gyro bias calculated by the Kalman filter - part of the 2x1 state vector
float rate[3]; // Unbiased rate calculated from the rate and the calculated bias - you have to call getAngle to update the rate

float P_R[2][2]; // Error covariance matrix - This is a 2x2 matrix
float P_P[2][2]; // Error covariance matrix - This is a 2x2 matrix
float P_Y[2][2]; // Error covariance matrix - This is a 2x2 matrix
float K_R[2];    // Kalman gain - This is a 2x1 vector

float y[3]; // Angle difference
float S[3]; // Estimate error


////////////////////////////////////////
float angle[3];
float R_measure[3];

float K_P[2]; // Kalman gain - This is a 2x1 vector
float K_Y[2]; // Kalman gain - This is a 2x1 vector

float kalAngleZ = 0;
float kalAngleY = 0;
float kalAngleX = 0;

float kalAngleY_last = 0;
float kalAngleX_last = 0;

float angle_r_avg = 0;
float comp_r_avg = 0;

float angle_p_avg = 0;
float comp_p_avg = 0;

uint8_t x_time = 0;
uint8_t y_time = 0;

void init_Kalman(float roll_init, float pitch_init, float yaw_init)
{
    // We will set the variables like so, these can also be tuned by the user

    // Q_angle[0] = 0.001;
    // Q_gyroBias[0] = 0.0;
    // R_measure[0] = 1;

       Q_angle[0] = 0.001;
       Q_gyroBias[0] = 0.003;
       R_measure[0] = 0.03;

    angle[0] = roll_init; // Reset the angle
    bias[0] = 0;          // Reset bias

    // Since we assume that the bias is 0 and we know the starting angle (use setAngle), the error covariance matrix is set like so
    P_R[0][0] = 0;
    P_R[0][1] = 0;
    P_R[1][0] = 0;
    P_R[1][1] = 0;

    // Q_angle[1] = 0.001;
    // Q_gyroBias[1] = 0.0;
    // R_measure[1] = 1;

       Q_angle[1] = 0.001;
       Q_gyroBias[1] = 0.003;
       R_measure[1] = 0.03;

    angle[1] = pitch_init; // Reset the angle
    bias[1] = 0;           // Reset bias

    // Since we assume that the bias is 0 and we know the starting angle (use setAngle), the error covariance matrix is set like so
    P_P[0][0] = 0;
    P_P[0][1] = 0;
    P_P[1][0] = 0;
    P_P[1][1] = 0;

    // Q_angle[2] = 0.001;
    // Q_gyroBias[2] = 0.003;
    // //    R_measure[2] = 0.1;
    // R_measure[2] = 100;

       Q_angle[2] = 0.001;
       Q_gyroBias[2] = 0.003;
       R_measure[2] = 0.03;

    angle[2] = yaw_init; // Reset the angle
    bias[2] = 0;         // Reset bias

    P_Y[0][0] = 0; // Since we assume that the bias is 0 and we know the starting angle (use setAngle), the error covariance matrix is set like so
    P_Y[0][1] = 0;
    P_Y[1][0] = 0;
    P_Y[1][1] = 0;
}

// KasBot V2  -  Kalman filter module - http://www.x-firm.com/?page_id=145
// Modified by Kristian Lauszus
// See my blog post for more information: http://blog.tkjelectronics.dk/2012/09/a-practical-approach-to-kalman-filter-and-how-to-implement-it
// The angle should be in degrees and the rate should be in degrees per second and the delta time in seconds

// int getAngle(float newAngle[3], float newRate[3], float dt, float rpy_new[3])
int getAngle(float newAngle[3], float newRate[3], float dt)
{
    // Discrete Kalman filter time update equations - Time Update ("Predict")
    // Update xhat - Project the state ahead
    /* Step 1 */
    rate[0] = newRate[0] - bias[0];
    angle[0] += dt * rate[0];
    //
    rate[1] = newRate[1] - bias[1];
    angle[1] += dt * rate[1];
    //
    rate[2] = newRate[2] - bias[2];
    angle[2] += dt * rate[2];

    // Update estimation error covariance - Project the error covariance ahead
    /* Step 2 */
    P_R[0][0] += dt * (dt * P_R[1][1] - P_R[0][1] - P_R[1][0] + Q_angle[0]);
    P_R[0][1] -= dt * P_R[0][1];
    P_R[1][0] -= dt * P_R[1][1];
    P_R[1][1] += Q_gyroBias[0] * dt;
    //
    P_P[0][0] += dt * (dt * P_P[1][1] - P_P[0][1] - P_P[1][0] + Q_angle[1]);
    P_P[0][1] -= dt * P_P[0][1];
    P_P[1][0] -= dt * P_P[1][1];
    P_P[1][1] += Q_gyroBias[1] * dt;

    P_Y[0][0] += dt * (dt * P_Y[1][1] - P_Y[0][1] - P_Y[1][0] + Q_angle[2]);
    P_Y[0][1] -= dt * P_Y[0][1];
    P_Y[1][0] -= dt * P_Y[1][1];
    P_Y[1][1] += Q_gyroBias[2] * dt;

    // Calculate angle and bias - Update estimate with measurement zk (newAngle)
    /* Step 3 */
    y[0] = newAngle[0] - angle[0];
    y[1] = newAngle[1] - angle[1];
    y[2] = newAngle[2] - angle[2];

    // Discrete Kalman filter measurement update equations - Measurement Update ("Correct")
    // Calculate Kalman gain - Compute the Kalman gain
    /* Step 4 */

    S[0] = P_R[0][0] + R_measure[0];
    S[1] = P_P[0][0] + R_measure[1];
    S[2] = P_Y[0][0] + R_measure[2];

    /* Step 5 */
    K_R[0] = P_R[0][0] / S[0];
    K_R[1] = P_R[1][0] / S[0];
    //
    K_P[0] = P_P[0][0] / S[1];
    K_P[1] = P_P[1][0] / S[1];
    //
    K_Y[0] = P_Y[0][0] / S[2];
    K_Y[1] = P_Y[1][0] / S[2];

    /* Step 6 */
    angle[0] += K_R[0] * y[0];
    bias[0] += K_R[1] * y[0];
    //
    angle[1] += K_P[0] * y[1];
    bias[1] += K_P[1] * y[1];
    //
    angle[2] += K_Y[0] * y[2];
    bias[2] += K_Y[1] * y[2];

    // Calculate estimation error covariance - Update the error covariance
    /* Step 7 */
    P_R[0][0] -= K_R[0] * P_R[0][0];
    P_R[0][1] -= K_R[0] * P_R[0][1];
    P_R[1][0] -= K_R[1] * P_R[0][0];
    P_R[1][1] -= K_R[1] * P_R[0][1];
    //
    P_P[0][0] -= K_P[0] * P_P[0][0];
    P_P[0][1] -= K_P[0] * P_P[0][1];
    P_P[1][0] -= K_P[1] * P_P[0][0];
    P_P[1][1] -= K_P[1] * P_P[0][1];
    //
    P_Y[0][0] -= K_Y[0] * P_Y[0][0];
    P_Y[0][1] -= K_Y[0] * P_Y[0][1];
    P_Y[1][0] -= K_Y[1] * P_Y[0][0];
    P_Y[1][1] -= K_Y[1] * P_Y[0][1];

    return 0;
}

void getAngle_R(float newAngle_R, float newRate_R, float dt, float *rpy_new_R)
{

    if (x_time == 0)
    {
        kalAngleX = angle[0];
    }

    rate[0] = newRate_R - bias[0];
    angle[0] += dt * rate[0];

    x_time++;

    kalAngleX = kalAngleX + newRate_R * dt; // ROLL

    P_R[0][0] += dt * (dt * P_R[1][1] - P_R[0][1] - P_R[1][0] + Q_angle[0]);
    P_R[0][1] -= dt * P_R[1][1];
    P_R[1][0] -= dt * P_R[1][1];
    P_R[1][1] += Q_gyroBias[0] * dt;

    S[0] = P_R[0][0] + R_measure[0];

    if (S[0] != 0)
    {
        K_R[0] = P_R[0][0] / S[0];
        K_R[1] = P_R[1][0] / S[0];
    }

    y[0] = newAngle_R - angle[0];

    angle[0] += K_R[0] * y[0];
    bias[0] += K_R[1] * y[0];

    angle_r_avg = angle_r_avg + angle[0];
    comp_r_avg = comp_r_avg + kalAngleX;

    if (x_time >= 70)
    {
        angle_r_avg = angle_r_avg / 70;
        comp_r_avg = comp_r_avg / 70;
        x_time = 0;
        angle_r_avg = 0;
        comp_r_avg = 0;
    }

    P_R[0][0] -= K_R[0] * P_R[0][0];
    P_R[0][1] -= K_R[0] * P_R[0][1];
    P_R[1][0] -= K_R[1] * P_R[0][0];
    P_R[1][1] -= K_R[1] * P_R[0][1];

    *rpy_new_R = angle[0];
}

void getAngle_P(float newAngle_P, float newRate_P, float dt, float *rpy_new_P)
{

    if (y_time == 0)
    {
        kalAngleY = angle[1];
    }

    y_time++;

    kalAngleY = kalAngleY + newRate_P * dt; // ROLL

    rate[1] = newRate_P - bias[1];
    angle[1] += dt * rate[1];

    P_P[0][0] += dt * (dt * P_P[1][1] - P_P[0][1] - P_P[1][0] + Q_angle[1]);
    P_P[0][1] -= dt * P_P[1][1];
    P_P[1][0] -= dt * P_P[1][1];
    P_P[1][1] += Q_gyroBias[1] * dt;

    S[1] = P_P[0][0] + R_measure[1];

    if (S[1] != 0)
    {
        K_P[0] = P_P[0][0] / S[1];
        K_P[1] = P_P[1][0] / S[1];
    }

    y[1] = newAngle_P - angle[1];

    angle[1] += K_P[0] * y[1];
    bias[1] += K_P[1] * y[1];

    angle_p_avg = angle_p_avg + angle[1];
    comp_p_avg = comp_p_avg + kalAngleY;

    if (y_time >= 70)
    {
        angle_p_avg = angle_p_avg / 70;
        comp_p_avg = comp_p_avg / 70;

        y_time = 0;
        angle_p_avg = 0;
        comp_p_avg = 0;
    }

    P_P[0][0] -= K_P[0] * P_P[0][0];
    P_P[0][1] -= K_P[0] * P_P[0][1];
    P_P[1][0] -= K_P[1] * P_P[0][0];
    P_P[1][1] -= K_P[1] * P_P[0][1];

    *rpy_new_P = angle[1];
}

void getAngle_Y(float newAngle_Y, float newRate_Y, float dt, float *rpy_new_Y)
{

    rate[2] = newRate_Y - bias[2];
    angle[2] += dt * rate[2];

    P_Y[0][0] += dt * (dt * P_Y[1][1] - P_Y[0][1] - P_Y[1][0] + Q_angle[2]);
    P_Y[0][1] -= dt * P_Y[1][1];
    P_Y[1][0] -= dt * P_Y[1][1];
    P_Y[1][1] += Q_gyroBias[2] * dt;

    S[2] = P_Y[0][0] + R_measure[2];

    if (S[2] != 0)
    {
        K_Y[0] = P_Y[0][0] / S[2];
        K_Y[1] = P_Y[1][0] / S[2];
    }

    y[2] = newAngle_Y - angle[2];
    y[2] = 0;

    angle[2] += K_Y[0] * y[2];
    bias[2] += K_Y[1] * y[2];
    P_Y[0][0] -= K_Y[0] * P_Y[0][0];
    P_Y[0][1] -= K_Y[0] * P_Y[0][1];
    P_Y[1][0] -= K_Y[1] * P_Y[0][0];
    P_Y[1][1] -= K_Y[1] * P_Y[0][1];

    *rpy_new_Y = angle[2];
}

void setAngle(float newAngle_R, float newAngle_P, float newAngle_Y)
{
    angle[0] = newAngle_R;
    angle[1] = newAngle_P;
    angle[2] = newAngle_Y;
} // Used to set angle, this should be set as the starting angle
