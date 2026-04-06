#ifndef __ACCELEROMETER_H
#define __ACCELEROMETER_H

/*includes */


/* Global variables */
typedef struct {
	float x_data;
	float y_data;
	float z_data;
} accelData_s;


/* Global Functions */
int accelerometerInitialization(void);
accelData_s getAccelerometerData(void); //	Need to figure out what kind of data structure I want for this


#endif __ACCELEROMETER_H
