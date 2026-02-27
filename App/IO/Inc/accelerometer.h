#ifndef __ACCELEROMETER_H
#define __ACCELEROMETER_H

/*includes */


/* Global variables */
typedef struct {
	int x_data;
} accelData_s;


/* Global Functions */
void accelerometerInitialization(void);
accelData_s getAccelerometerData(void); //	Need to figure out what kind of data structure I want for this


#endif __ACCELEROMETER_H

