#include "accelerometer.h"
#include "stm32f4xx_hal.h"
#include "bit_manipulation.h"
#include "status.h"
#include <stdbool.h>
#include <math.h>

/* Local type Definitions */



/* External Variables */
extern I2C_HandleTypeDef hi2c1;

/* Local Variable Declaration */
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


#define ACCEL_ADDRESS		0x68 //0b1101000
#define MPU6050_ADDR 0xD0
// Other Definitions
#define BUFFER_SIZE			1024U //FIFO buffer max size is 1024 bytes

/* Local type Definitions */


// FIFO buffer data
typedef struct {
    //bool overflow;
    uint16_t length; //FIFO Count H and L registers define current size of buffer
    uint8_t data[BUFFER_SIZE]; // Fixed-size byte buffer
} FifoBuffer_t;

// Data struct for accelerometer axis
typedef struct {
	float basis; // This is the mean determined during initialization
	float stdDeviation; // This is the standard deviation determined during initialization
	float movingAverage; // May want a moving average as read in data
	float lastFifoBufferAverage;
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
static accelAxisBasisInfo_t xAxisData = {0.0f, 0.0f, 0.0f, 0.0f};
static accelAxisBasisInfo_t yAxisData = {0.0f, 0.0f, 0.0f, 0.0f};
static accelAxisBasisInfo_t zAxisData = {0.0f, 0.0f, 0.0f, 0.0f};

static accelAxisBasisInfo_t * p_xAxisData = &xAxisData;
static accelAxisBasisInfo_t * p_yAxisData = &yAxisData;
static accelAxisBasisInfo_t * p_zAxisData = &zAxisData;

static accelConfiguration_t accelerometerConfig = {
	.config = 6U, // 0000 0110
	.accelConfig= 0U, // 0000 0000
	.fifoEnable= 8U, //0000 1000. FIFO is accelerometer data
	.interruptPin= 48U, // 0011 0000 Int active high, push-pull, latched, clear on any read, no fsynch or bypass
	.interruptEnable= 0U, // FIFO overflow interrupt is bit 4. To enable - 17U
	.userCtrl= 0U, // 0100 0000 enable fifo, not master mode, i2c, fifo reset bit, i2c reset bit. 64u AFTER INIT
	.pwrMgmtOne= 0U, //0000 0000 clk source is internal. Initial configuration is fully on, not in cycle mode
	.pwrMgmtTwo= 199U//199U, //1100 0111 LP wake ctrl is 3, all gyro in standby mode
};
/* Local Function Declaration */
// read FIFO buffer
static void readFifoBuffer(void);
static int8_t CompareAccelConfigStructs(accelConfiguration_t * setStruct, accelConfiguration_t * responseStruct);
static void GetAccelBasis(void);

// Global Function

statusDefinition_enum accelerometerInitialization(void) {
	uint8_t initReturnData;
	HAL_StatusTypeDef returnStatus;
	statusDefinition_enum accelStatus = 0U;

	// First make sure that accelerometer is even on - if not return -1
	returnStatus =  HAL_I2C_Mem_Read(&hi2c1, (ACCEL_ADDRESS << 1), WHO_AM_I, I2C_MEMADD_SIZE_8BIT, &initReturnData, 1, 100);

	if (returnStatus != HAL_OK){
		accelStatus = 0U;
		return accelStatus; // Get out of this function
	}

	//Write to Config register
	returnStatus =  HAL_I2C_Mem_Write(&hi2c1, (ACCEL_ADDRESS << 1), CONFIG, I2C_MEMADD_SIZE_8BIT, &accelerometerConfig.config, 1, 100);
	//Write to Accel Config register
	returnStatus =  HAL_I2C_Mem_Write(&hi2c1, (ACCEL_ADDRESS << 1), ACCEL_CONFIG, I2C_MEMADD_SIZE_8BIT, &accelerometerConfig.accelConfig, 1, 100);
	//Write to FIFO Enable register
	returnStatus =  HAL_I2C_Mem_Write(&hi2c1, (ACCEL_ADDRESS << 1), FIFO_EN, I2C_MEMADD_SIZE_8BIT, &accelerometerConfig.fifoEnable, 1, 100);
	//Write to Interrupt Pin Configuration register
	returnStatus =  HAL_I2C_Mem_Write(&hi2c1, (ACCEL_ADDRESS << 1), INT_PIN_CFG, I2C_MEMADD_SIZE_8BIT, &accelerometerConfig.interruptPin, 1, 100);
	//Write to Interrupt Enable register
	returnStatus =  HAL_I2C_Mem_Write(&hi2c1, (ACCEL_ADDRESS << 1), INT_ENABLE, I2C_MEMADD_SIZE_8BIT, &accelerometerConfig.interruptEnable, 1, 100);
	//Write to User Control Enable register
	returnStatus =  HAL_I2C_Mem_Write(&hi2c1, (ACCEL_ADDRESS << 1), USER_CTRL, I2C_MEMADD_SIZE_8BIT, &accelerometerConfig.userCtrl, 1, 100);
	//Write to Power Management 1 Enable register
	returnStatus =  HAL_I2C_Mem_Write(&hi2c1, (ACCEL_ADDRESS << 1), PWR_MGMT_1, I2C_MEMADD_SIZE_8BIT, &accelerometerConfig.pwrMgmtOne, 1, 100);
	//Write to Power Management 2 Enable register
	returnStatus =  HAL_I2C_Mem_Write(&hi2c1, (ACCEL_ADDRESS << 1), PWR_MGMT_2, I2C_MEMADD_SIZE_8BIT, &accelerometerConfig.pwrMgmtOne, 1, 100);

	if (returnStatus != HAL_OK){
		accelStatus = 0U;
		return accelStatus; // Get out of this function
	}

	// Now read from all of these registers to confirm that they were set up
	accelConfiguration_t accelConfigurationResponse;
	returnStatus =  HAL_I2C_Mem_Read(&hi2c1, (ACCEL_ADDRESS << 1), CONFIG, I2C_MEMADD_SIZE_8BIT, &accelConfigurationResponse.config, 1, 100);
	returnStatus =  HAL_I2C_Mem_Read(&hi2c1, (ACCEL_ADDRESS << 1), ACCEL_CONFIG, I2C_MEMADD_SIZE_8BIT, &accelConfigurationResponse.accelConfig, 1, 100);
	returnStatus =  HAL_I2C_Mem_Read(&hi2c1, (ACCEL_ADDRESS << 1), FIFO_EN, I2C_MEMADD_SIZE_8BIT, &accelConfigurationResponse.fifoEnable, 1, 100);
	returnStatus =  HAL_I2C_Mem_Read(&hi2c1, (ACCEL_ADDRESS << 1), INT_PIN_CFG, I2C_MEMADD_SIZE_8BIT, &accelConfigurationResponse.interruptPin, 1, 100);
	returnStatus =  HAL_I2C_Mem_Read(&hi2c1, (ACCEL_ADDRESS << 1), INT_ENABLE, I2C_MEMADD_SIZE_8BIT, &accelConfigurationResponse.interruptEnable, 1, 100);
	returnStatus =  HAL_I2C_Mem_Read(&hi2c1, (ACCEL_ADDRESS << 1), USER_CTRL, I2C_MEMADD_SIZE_8BIT, &accelConfigurationResponse.userCtrl, 1, 100);
	returnStatus =  HAL_I2C_Mem_Read(&hi2c1, (ACCEL_ADDRESS << 1), PWR_MGMT_1, I2C_MEMADD_SIZE_8BIT, &accelConfigurationResponse.pwrMgmtOne, 1, 100);
	returnStatus =  HAL_I2C_Mem_Read(&hi2c1, (ACCEL_ADDRESS << 1), PWR_MGMT_2, I2C_MEMADD_SIZE_8BIT, &accelConfigurationResponse.pwrMgmtOne, 1, 100);

	int8_t accelConfigGoood = CompareAccelConfigStructs(&accelerometerConfig, &accelConfigurationResponse);

	if (accelConfigGoood < 0U) {
		accelStatus = INITIALIZATION_FAILED;
		return accelStatus; // Get out of this function
	}

	if (returnStatus != HAL_OK){
		accelStatus = 0U;
		return accelStatus; // Get out of this function
	}



	// Get the Basis
	GetAccelBasis();

	// error check - if values are zero is >4 there is an error
	if ((p_xAxisData->basis ==0.0) || (p_xAxisData->basis > 4.0) || (p_xAxisData->basis < -4.0))
	{
		accelStatus = INITIALIZATION_FAILED;
	}
	if ((p_yAxisData->basis ==0.0) || (p_yAxisData->basis > 4.0) || (p_yAxisData->basis < -4.0))
	{
		accelStatus = INITIALIZATION_FAILED;
	}
	if ((p_zAxisData->basis ==0.0) || (p_zAxisData->basis > 4.0) || (p_zAxisData->basis < -4.0))
	{
		accelStatus = INITIALIZATION_FAILED;
	}

	// Got basis, now reset enable FIFO buffer, reset it, and enable accel
	accelConfigurationResponse.interruptEnable = 17U;
	accelConfigurationResponse.userCtrl= 64U;

	returnStatus =  HAL_I2C_Mem_Read(&hi2c1, (ACCEL_ADDRESS << 1), INT_ENABLE, I2C_MEMADD_SIZE_8BIT, &accelConfigurationResponse.interruptEnable, 1, 100);
	returnStatus =  HAL_I2C_Mem_Read(&hi2c1, (ACCEL_ADDRESS << 1), INT_ENABLE, I2C_MEMADD_SIZE_8BIT, &accelConfigurationResponse.userCtrl, 1, 100);

	// now configure power management
	accelConfigurationResponse.pwrMgmtOne = 0x28U; // 0010 1000 Put in cycle mode - sleep 0, cycle 1, temp sensor off

	uint8_t fifoReset = 0x04 | accelerometerConfig.userCtrl;
	//reset FIFO
	returnStatus =  HAL_I2C_Mem_Write(&hi2c1, (ACCEL_ADDRESS << 1), USER_CTRL, I2C_MEMADD_SIZE_8BIT, &fifoReset, 1, 100);

	return accelStatus;

}

accelData_s getAccelerometerData(void)
{
	readFifoBuffer();
	accelData_s accelData = {p_xAxisData->lastFifoBufferAverage, p_yAxisData->lastFifoBufferAverage, p_zAxisData->lastFifoBufferAverage};
	return accelData;
}

/* Local Function Definitions */



static int8_t CompareAccelConfigStructs(accelConfiguration_t * setStruct, accelConfiguration_t * responseStruct)
{
	if (setStruct->config != responseStruct->config) {
		return -1;
	}

	if (setStruct->accelConfig != responseStruct->accelConfig) {
		return -1;
	}
	if (setStruct->fifoEnable != responseStruct->fifoEnable) {
		return -1;
	}
	if (setStruct->interruptPin != responseStruct->interruptPin) {
		return -1;
	}
	if (setStruct->interruptEnable != responseStruct->interruptEnable) {
		return -1;
	}
	if (setStruct->userCtrl != responseStruct->userCtrl) {
		return -1;
	}
	if (setStruct->pwrMgmtOne != responseStruct->pwrMgmtOne) {
		return -1;
	}
	if (setStruct->pwrMgmtTwo != responseStruct->pwrMgmtTwo) {
		return -1;
	}

	return 0;
}

/**
  * @brief  Read the accelerometer information for x seconds and computes average and standard deviation
  * @param  None. Uses a static global variable
  * @retval None
  */
static void GetAccelBasis(void)
{
	uint8_t fifoCount[2] = {0};
	HAL_I2C_Mem_Read (&hi2c1, (ACCEL_ADDRESS << 1), FIFO_COUNTH, 1, fifoCount, 2, 1000);
	uint16_t fifoSize = (fifoCount[0] << 8) | fifoCount[1];

	HAL_StatusTypeDef returnStatus;
	//Want to read for 5 seconds - how many times do I need to read then?
	// num_samples = 10sec/sample_period = 10,000 samples
	// sample_period - The accelerometer output rate is 1kHz (1/1000 = 1ms)
	int buffer_size = 10;

	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
	DWT->CYCCNT = 0; // Reset counter
	DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk; // Enable counter

	uint32_t start = DWT->CYCCNT;
	//16 bits each (8 in high and low register each)
//	uint8_t x_buffer[2] = {0};
//	uint8_t y_buffer[2] = {0};
//	uint8_t z_buffer[2] = {0};

	uint8_t size = 12;
	uint8_t Rec_Data[size];

	const uint8_t numAccelDataPoints = 0xffU;

	// Read 6 BYTES of data starting from ACCEL_XOUT_H (0x3B) register
	HAL_I2C_Mem_Read (&hi2c1, (ACCEL_ADDRESS << 1), 0x3B, 1, Rec_Data, size, 1000);
//
//	float AxSum = 0.0;
//	float AySum = 0.0;
//	float AzSum = 0.0;

	float AxMean = 0.0;
	float AyMean = 0.0;
	float AzMean = 0.0;

	float AxStdDev = 0.0;
	float AyStdDev = 0.0;
	float AzStdDev = 0.0;

	float previousMeanAx = 0.0;
	float previousMeanAy = 0.0;
	float previousMeanAz = 0.0;

	float previousStdDevAx = 0.0;
	float previousStdDevAy = 0.0;
	float previousStdDevAz = 0.0;

	for (uint16_t i=1; i <= numAccelDataPoints; i++) // Need to start at 1, divide by 0 is not allowed
	{




		// Read 6 BYTES of data starting from ACCEL_XOUT_H (0x3B) register
		HAL_I2C_Mem_Read (&hi2c1, (ACCEL_ADDRESS << 1), 0x3B, 1, Rec_Data, size, 1000);

		float x_val = (float)((Rec_Data[0] << 8) | Rec_Data[1])/16384.0;
		float y_val = (float)((Rec_Data[2] << 8) | Rec_Data[3])/16384.0;
		float z_val = (float)((Rec_Data[4] << 8) | Rec_Data[5])/16384.0;

//		AxSum += x_val;
//		AySum += y_val;
//		AzSum += z_val;

		AxMean = previousMeanAx + (x_val - previousMeanAx)/(float)i;
		AyMean = previousMeanAy + (y_val - previousMeanAy)/(float)i;
		AzMean = previousMeanAz + (z_val - previousMeanAz)/(float)i;

		AxStdDev = sqrtf((previousStdDevAx + (x_val - previousMeanAx)*(x_val - AxMean))/(float)i);
		AyStdDev = sqrtf((previousStdDevAy + (y_val - previousMeanAy)*(y_val - AyMean))/(float)i);
		AzStdDev = sqrtf((previousStdDevAz + (z_val - previousMeanAz)*(z_val - AzMean))/(float)i);

		previousMeanAx = AxMean;
		previousMeanAy = AyMean;
		previousMeanAz = AzMean;

		previousStdDevAx = AxStdDev;
		previousStdDevAy = AyStdDev;
		previousStdDevAz = AzStdDev;

		HAL_Delay (10);


	}


	p_xAxisData->basis = AxMean; // AxSum/(float)numAccelDataPoints;
	p_yAxisData->basis = AyMean; // AySum/(float)numAccelDataPoints;
	p_zAxisData->basis = AzMean; // AzSum/(float)numAccelDataPoints;

	p_xAxisData->stdDeviation = AxStdDev;
	p_yAxisData->stdDeviation = AyStdDev;
	p_zAxisData->stdDeviation = AzStdDev;

//	float Xmeans = AxSum/(float)numAccelDataPoints;
//    float Ymeans = AySum/(float)numAccelDataPoints;
//    float Zmeans = AzSum/(float)numAccelDataPoints;

	uint32_t stop = DWT->CYCCNT;
	uint32_t delta = stop - start;
	float execution_time_us = (float)delta / (float)SystemCoreClock;
}


static void readFifoBuffer(void){
	HAL_StatusTypeDef returnStatus;
	uint8_t Rec_Data[6] = {0};


	uint8_t fifoCount[2] = {0};
	HAL_I2C_Mem_Read (&hi2c1, (ACCEL_ADDRESS << 1), FIFO_COUNTH, 1, fifoCount, 2, 1000);
	uint16_t fifoSize = (fifoCount[0] << 8) | fifoCount[1];

	uint8_t size_dataPoints = fifoSize/6; // 6 data points for every update

	float Ax[size_dataPoints];// = (float)x_val/16384.0;
	float Ay[size_dataPoints];// = (float)y_val/16384.0;
	float Az[size_dataPoints];// = (float)z_val/16384.0;

	int16_t x_val = 0;
	int16_t y_val = 0;
	int16_t z_val = 0;

	float AxSum = 0.0;
	float AySum = 0.0;
	float AzSum = 0.0;

	for (uint8_t i=0; i < size_dataPoints; i++)
	{
		returnStatus =  HAL_I2C_Mem_Read(&hi2c1, (ACCEL_ADDRESS << 1), FIFO_R_W, I2C_MEMADD_SIZE_8BIT, &Rec_Data[0], 1, 100);
		returnStatus =  HAL_I2C_Mem_Read(&hi2c1, (ACCEL_ADDRESS << 1), FIFO_R_W, I2C_MEMADD_SIZE_8BIT, &Rec_Data[1], 1, 100);
		returnStatus =  HAL_I2C_Mem_Read(&hi2c1, (ACCEL_ADDRESS << 1), FIFO_R_W, I2C_MEMADD_SIZE_8BIT, &Rec_Data[2], 1, 100);
		returnStatus =  HAL_I2C_Mem_Read(&hi2c1, (ACCEL_ADDRESS << 1), FIFO_R_W, I2C_MEMADD_SIZE_8BIT, &Rec_Data[3], 1, 100);
		returnStatus =  HAL_I2C_Mem_Read(&hi2c1, (ACCEL_ADDRESS << 1), FIFO_R_W, I2C_MEMADD_SIZE_8BIT, &Rec_Data[4], 1, 100);
		returnStatus =  HAL_I2C_Mem_Read(&hi2c1, (ACCEL_ADDRESS << 1), FIFO_R_W, I2C_MEMADD_SIZE_8BIT, &Rec_Data[5], 1, 100);

		x_val = (Rec_Data[0] << 8) | Rec_Data[1];
		y_val = (Rec_Data[2] << 8) | Rec_Data[3];
		z_val = (Rec_Data[4] << 8) | Rec_Data[5];

		Ax[i] =(float)x_val/16384.0;
		Ay[i] =(float)y_val/16384.0;
		Az[i] =(float)z_val/16384.0;

		AxSum += Ax[i];
		AySum += Ay[i];
		AzSum += Az[i];
	}


//	for (uint8_t i=0; i < size_dataPoints; i++)
//	{
//
//		int16_t x_val = (Rec_Data[0+i*6] << 8) | Rec_Data[1+i*6];
//		int16_t y_val = (Rec_Data[2+i*6] << 8) | Rec_Data[3+i*6];
//		int16_t z_val = (Rec_Data[4+i*6] << 8) | Rec_Data[5+i*6];
//
//		Ax[i] = (float)x_val/16384.0;
//		Ay[i] = (float)y_val/16384.0;
//		Az[i] = (float)z_val/16384.0;
//
//		AxSum += Ax[i];
//		AySum += Ay[i];
//		AzSum += Az[i];
//	}

	// Now average everything
	p_xAxisData->lastFifoBufferAverage = AxSum/(float)size_dataPoints;
	p_yAxisData->lastFifoBufferAverage = AySum/(float)size_dataPoints;
	p_zAxisData->lastFifoBufferAverage = AzSum/(float)size_dataPoints;

	uint8_t fifoReset = 0x04 | accelerometerConfig.userCtrl;
	//reset FIFO
	returnStatus =  HAL_I2C_Mem_Write(&hi2c1, (ACCEL_ADDRESS << 1), USER_CTRL, I2C_MEMADD_SIZE_8BIT, &fifoReset, 1, 100);

}

//static void monitorFifo(void){
//	uint8_t config_r;
//	uint8_t fifoEn;
//	uint8_t i2cstatus;
//	uint8_t intstatus;
//	uint8_t userctrl;
//
//	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
//	DWT->CYCCNT = 0; // Reset counter
//	DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk; // Enable counter
//
//	uint32_t start = DWT->CYCCNT;
//
//	HAL_StatusTypeDef returnStatus;
//	uint8_t fifoCount[2] = {0};
//	HAL_I2C_Mem_Read (&hi2c1, (ACCEL_ADDRESS << 1), FIFO_COUNTH, 1, fifoCount, 2, 1000);
//	uint16_t fifoSize = (fifoCount[0] << 8) | fifoCount[1];
//	returnStatus =  HAL_I2C_Mem_Read(&hi2c1, (ACCEL_ADDRESS << 1), CONFIG, I2C_MEMADD_SIZE_8BIT, &config_r, 1, 100);
//	returnStatus =  HAL_I2C_Mem_Read(&hi2c1, (ACCEL_ADDRESS << 1), FIFO_EN, I2C_MEMADD_SIZE_8BIT, &fifoEn, 1, 100);
//	returnStatus =  HAL_I2C_Mem_Read(&hi2c1, (ACCEL_ADDRESS << 1), I2C_MST_STATUS, I2C_MEMADD_SIZE_8BIT, &i2cstatus , 1, 100);
//	returnStatus =  HAL_I2C_Mem_Read(&hi2c1, (ACCEL_ADDRESS << 1), INT_STATUS, I2C_MEMADD_SIZE_8BIT, &intstatus , 1, 100);
//	returnStatus =  HAL_I2C_Mem_Read(&hi2c1, (ACCEL_ADDRESS << 1), USER_CTRL, I2C_MEMADD_SIZE_8BIT, &userctrl , 1, 100);
//
//
//	int count = 0;
//	float fifomean = 0.0;
//
//	while (((intstatus >> 4) & 1) == 0U)
//	{
//		returnStatus =  HAL_I2C_Mem_Read(&hi2c1, (ACCEL_ADDRESS << 1), INT_STATUS, I2C_MEMADD_SIZE_8BIT, &intstatus , 1, 100);
//		HAL_I2C_Mem_Read (&hi2c1, (ACCEL_ADDRESS << 1), FIFO_COUNTH, 1, fifoCount, 2, 1000);
//		fifoSize = (fifoCount[0] << 8) | fifoCount[1];
//		count ++;
//		fifomean = (fifomean*(count-1)+fifoSize)/count;
//	}
//
//	uint32_t stop = DWT->CYCCNT;
//	uint32_t delta = stop - start;
//	float execution_time_us = (float)delta / (float)SystemCoreClock;
//	HAL_TickFreqTypeDef ticks = HAL_GetTickFreq ();
//	return;
//}

//static void measureTime(void)
//{
//	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
//	DWT->CYCCNT = 0; // Reset counter
//	DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk; // Enable counter
//
//	uint32_t start = DWT->CYCCNT;
//
//	/* do things */
//
//	uint32_t stop = DWT->CYCCNT;
//	uint32_t delta = stop - start;
//	float execution_time_us = (float)delta / (float)SystemCoreClock;
//	HAL_TickFreqTypeDef ticks = HAL_GetTickFreq ();
//
//	return;
//}
//
//
//static void readStatus(void)
//{
//	uint8_t config_r;
//	uint8_t fifoEn;
//	uint8_t i2cstatus;
//	uint8_t intstatus;
//	uint8_t userctrl;
//
//	HAL_StatusTypeDef returnStatus;
//	uint8_t fifoCount[2] = {0};
//	HAL_I2C_Mem_Read (&hi2c1, (ACCEL_ADDRESS << 1), FIFO_COUNTH, 1, fifoCount, 2, 1000);
//	fifoSize = (fifoCount[0] << 8) | fifoCount[1];
//	returnStatus =  HAL_I2C_Mem_Read(&hi2c1, (ACCEL_ADDRESS << 1), CONFIG, I2C_MEMADD_SIZE_8BIT, &config_r, 1, 100);
//	returnStatus =  HAL_I2C_Mem_Read(&hi2c1, (ACCEL_ADDRESS << 1), FIFO_EN, I2C_MEMADD_SIZE_8BIT, &fifoEn, 1, 100);
//	returnStatus =  HAL_I2C_Mem_Read(&hi2c1, (ACCEL_ADDRESS << 1), I2C_MST_STATUS, I2C_MEMADD_SIZE_8BIT, &i2cstatus , 1, 100);
//	returnStatus =  HAL_I2C_Mem_Read(&hi2c1, (ACCEL_ADDRESS << 1), INT_STATUS, I2C_MEMADD_SIZE_8BIT, &intstatus , 1, 100);
//	returnStatus =  HAL_I2C_Mem_Read(&hi2c1, (ACCEL_ADDRESS << 1), USER_CTRL, I2C_MEMADD_SIZE_8BIT, &userctrl , 1, 100);
//
//	return;
//}
