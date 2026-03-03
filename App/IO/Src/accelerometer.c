#include "accelerometer.h"
#include "stm32f4xx_hal.h"
#include "bit_manipulation.h"
#include "status.h"
#include <stdbool.h>

/* Accelerometer Address */
#define ACCEL_ADDRESS		0X68U // For STM I2C functions this needs to be shifted left 1, so will be 0xD0

/* Register Definitions */
#define CONFIG				26U
#define GYRO_CONFIG			27U
#define	ACCEL_CONFIG		28U
#define FIFO_EN				35U
#define I2C_MST_CTRL		36U
#define I2C_MST_STATUS		54U
#define INT_PIN_CFG			55U
#define INT_ENABLE			56U
#define INT_STATUS 			58U
#define ACCEL_XOUT_H		59U
#define ACCEL_XOUT_L		60U
#define ACCEL_YOUT_H		61U
#define ACCEL_YOUT_L		62U
#define ACCEL_ZOUT_H		63U
#define ACCEL_ZOUT_L		64U
#define I2C_MST_DELAY_CTRL	103U
#define SIGNAL_PATH_RESET	104U
#define USER_CTRL			106U
#define PWR_MGMT_1			107U
#define PWR_MGMT_2			108U
#define FIFO_COUNTH			114U
#define FIFO_COUNTL			115U
#define FIFO_R_W			116U
#define WHO_AM_I			117U

// Bit Definitions

// Other Definitions
#define BUFFER_SIZE			1024U //FIFO buffer max size is 1024 bytes

/* Local type Definitions */

// FIFO buffer data
typedef struct {
    bool overflow;
    uint16_t length; //FIFO Count H and L registers define current size of buffer
    uint8_t data[BUFFER_SIZE]; // Fixed-size byte buffer
} FifoBuffer_t;

// Data struct for accelerometer axis
typedef struct {
	int16_t basis; // This is the mean determined during initialization
	int16_t stdDeviation; // This is the standard deviation determined during initialization
	int16_t movingAverage; // May want a moving average as read in data
	int16_t lastFifoBufferAverage;
} accelAxisBasisInfo_t;

// Data structure for accelerometer configuration
typedef struct {
	uint8_t config;
	uint8_t accelConfig;
	uint8_t fifoEnable;
	uint8_t interruptPin;
	uint8_t interruptEnable;
	uint8_t userCtrl;
	uint8_t pwrMgmtOne;
	uint8_t pwrMgmtTwo;
} accelConfiguration_t;

/* Local Variable Declaration */
static accelAxisBasisInfo_t * const xAxisData;
static accelAxisBasisInfo_t * const yAxisData;
static accelAxisBasisInfo_t * const zAxisData;

static accelConfiguration_t accelConfig = {
	.config = 6U, // 0000 0110
	.accelConfig= 0U, // 0000 0000
	.fifoEnable= 8U, //0000 1000. FIFO is accelerometer data
	.interruptPin= 48U, // 0011 0000 Int active high, push-pull, latched, clear on any read, no fsynch or bypass
	.interruptEnable= 16U, // FIFO overflow interrupt is bit 4
	.userCtrl= 64U, // 0100 0000 enable fifo, not master mode, i2c, fifo reset bit, i2c reset bit,
	.pwrMgmtOne= 0U, //0000 0000 clk source is internal. Initial configuration is fully on, not in cycle mode
	.pwrMgmtTwo= 199U, //1100 0111 LP wake ctrl is 3, all gyro in standby mode
};

/* Local Function Declaration */
// read FIFO buffer
static void readFifoBuffer(void);


/* Local Function Definitions */


/* Global Function Definitions */
int accelerometerInitialization(void) {
	uint8_t initReturnData;
	HAL_StatusTypeDef returnStatus;
	statusDefinition_enum accelStatus;

	// First make sure that accelerometer is even on - if not return -1
	returnStatus =  HAL_I2C_Mem_Read(&hi2c1, (ACCEL_ADDRESS << 1), WHO_AM_I, I2C_MEMADD_SIZE_8BIT, &initReturnData, 1, 100);

	if (returnStatus != HAL_OK){
		accelStatus = 0U;
		return accelStatus; // Get out of this function
	}

	returnStatus =  HAL_I2C_Mem_Write(&hi2c1, (ACCEL_ADDRESS << 1), CONFIG, I2C_MEMADD_SIZE_8BIT, &initReturnData, 1, 100);



}

