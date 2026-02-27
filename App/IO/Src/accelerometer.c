#include "accelerometer.h"
#include "stm32f4xx_hal.h"
#include "bit_manipulation.h"

/* Register Definitions */
#define CONIG				0X26U
#define GYRO_CONFIG			0X27U
#define	ACCEL_CONFIG		0X28U
#define FIFO_EN				0X35U
#define I2C_MST_CTRL		0X36U
#define I2C_MST_STATUS		0X54U
#define INT_PIN_CFG			0X55U
#define INT_ENABLE			0X56U
#define INT_STATUS 			0X58U
#define ACCEL_XOUT_H		0X59U
#define ACCEL_XOUT_L		0X60U
#define ACCEL_YOUT_H		0X61U
#define ACCEL_YOUT_L		0X62U
#define ACCEL_ZOUT_H		0X63U
#define ACCEL_ZOUT_L		0X64U
#define I2C_MST_DELAY_CTRL	0X103U
#define SIGNAL_PATH_RESET	0X104U
#define USER_CTRL			0X106U
#define PWR_MGMT_1			0X107U
#define PWR_MGMT_2			0X108U
#define FIFO_COUNTH			0X114U
#define FIFO_COUNTL			0X115U
#define FIFO_R_W			0X116U
#define WHO_AM_I			0X117U

// Bit Definitions

/* Local type Definitions */
// current buffer data



/* Local Variable Declaration */

/* Local Function Definitions */
// read FIFO buffer



