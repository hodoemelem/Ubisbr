/* Copyright (C) 2012 Kristian Lauszus, TKJ Electronics. All rights reserved.

 This software may be distributed and modified under the terms of the GNU
 General Public License version 2 (GPL2) as published by the Free Software
 Foundation and appearing in the file GPL2.TXT included in the packaging of
 this file. Please note that GPL2 Section 2[b] requires that all works based
 on this software must also be made publicly available under the terms of
 the GPL2 ("Copyleft").

 Contact information
 -------------------

 Kristian Lauszus, TKJ Electronics
 Web      :  http://www.tkjelectronics.com
 e-mail   :  kristianl@tkjelectronics.com
 */

#ifndef _Kalman_h
#define _Kalman_h

    extern float noise;


    extern float kalAngleZ;
    extern float kalAngleY;
    extern float kalAngleX;

    // float Q_angle[3];			// Process noise variance for the accelerometer
    // float Q_gyroBias[3]; 			// Process noise variance for the gyro bias
    extern float R_measure[3]; 	// Measurement noise variance - this is actually the variance of the measurement noise

    extern float angle[3]; 		// The angle calculated by the Kalman filter - part of the 2x1 state vector
    // float bias[3]; 				// The gyro bias calculated by the Kalman filter - part of the 2x1 state vector
    // float rate[3]; 				// Unbiased rate calculated from the rate and the calculated bias - you have to call getAngle to update the rate

    // float P_R[2][2]; 			// Error covariance matrix - This is a 2x2 matrix
    // float P_P[2][2]; 			// Error covariance matrix - This is a 2x2 matrix
    // float P_Y[2][2]; 			// Error covariance matrix - This is a 2x2 matrix
    // float K_R[2]; 				// Kalman gain - This is a 2x1 vector
    extern float K_P[2]; 		// Kalman gain - This is a 2x1 vector
    extern float K_Y[2]; 		// Kalman gain - This is a 2x1 vector
    // float y[3]; 				// Angle difference
    // float S[3]; 				// Estimate error

    void init_Kalman(float roll_init, float pitch_init, float yaw_init);

    int getAngle(float newAngle[3], float newRate[3], float dt);

    void setAngle(float newAngle_R, float newAngle_P, float newAngle_Y);

    void getAngle_R(float newAngle_R, float newRate_R, float dt, float *rpy_new_R);

    void getAngle_P(float newAngle_P, float newRate_P, float dt, float *rpy_new_P);

    void getAngle_Y(float newAngle_Y, float newRate_Y, float dt, float *rpy_new_Y);


#endif
//=====================================================================================================
// End of file
//=====================================================================================================
