# Language

* C

# Architecture:

* Need to decide \- Round-Robin with Interrupts or Function-Queue Scheduling   
  * Function queue \- can assign function calls by priority. Higher priority tasks have better response time. Lower priority tasks will have worse response time   
* Interrupts will be useful   
* Not enough going on that need to do RTOS   
* Assign priorities to interrupts 

# External Hardware Being Used:

* Accelerometer   
  * 2 available   
  * Shillehtek MPU6050 IMU  
  * Has a temp sensor on it as well  
  * [https://howtomechatronics.com/tutorials/arduino/arduino-and-mpu6050-accelerometer-and-gyroscope-tutorial/](https://howtomechatronics.com/tutorials/arduino/arduino-and-mpu6050-accelerometer-and-gyroscope-tutorial/)  
  * Has an interrupt pin on it   
  * Data sheet: [https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Register-Map1.pdf](https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Register-Map1.pdf)  
* Camera   
  * USB or PCI  
* PIR Sensors   
  * 3 available   
  * HiLetgo HC-SR501  
  * [https://lastminuteengineers.com/pir-sensor-arduino-tutorial/](https://lastminuteengineers.com/pir-sensor-arduino-tutorial/)  
  * Two modes (choose with a jumper)   
    * Single trigger mode \- sensor only triggers once   
    * Multiple trigger mode \- continuous movement causes triggers no matter what   
  * Has adjustable sensitivity (this is a potentiometer)  
  * Time delay control \- control how long sensor’s output stays high after motion detection (this is a potentiometer)  
  * Digital output \- High or low   
  * Pins:  
    * Vcc \- 5V to 12V  
    * Output \- 3.3V TTL   
    * GND  
  * This sensor has a lockout time \- for 2 seconds after transition from High to Low, will not respond to any new movement   
* Temp and humidity sensor   
  * BME280  
* Digital Light Sensor   
  * Shillehtek BH1750  
  * I2C  
  * [https://shillehtek.com/blogs/news/how-to-connect-bh1750-with-arduino-measure-ambient-light?srsltid=AfmBOooh20TCbH7BnZrqt-IVrOK1Ei1dVeL41ZzIzKbGrAHWp-6mYx5V](https://shillehtek.com/blogs/news/how-to-connect-bh1750-with-arduino-measure-ambient-light?srsltid=AfmBOooh20TCbH7BnZrqt-IVrOK1Ei1dVeL41ZzIzKbGrAHWp-6mYx5V)  
  * Allows for fast mode (400kHz)

# Interrupts

* PIR will be on an interrupt   
  * ISR \- place in queue a high and time of motion detection   
  * If have multiple PIRs maybe include which one   
* Accelerometer interrupt   
* UART 

# Ideas for Camera 

* Low light processing   
* Need to be able to tell Raspberry pi or whatever is taking video what the light condition is 

# Connecting STM32 to Raspberry Pi

* Connect over UART 

# Configuration Data 

* What devices are on   
  * PIR1, PIR2, PIR3, Humidity/temp, 

# Things on STM32 to Consider

* 32-bit multi-AHB bus matrix interconnects all the masters (CPU, DMAs, USB HS) and the slaves Flash memory, RAM, QuadSPI, FMC, AHB and APB peripherals and ensures a seamless and efficient operation even when several high-speed peripherals work simultaneous  
* DMA controller \- two general-purpose dual-port DMAs  
  *  FIFOs for APB/AHB peripherals, support burst transfer and are designed to provide the maximum peripheral bandwidth (AHB/APB)  
  * Support circular buffer management   
  * Double buffering feature \- automate use and switching of two memory buffers   
  * Can be used with peripherals \- I2C, SPI, DAC, timers, ADC, etc.  
* Flexible memory controller \- FMC  
  * even Chip Select outputs supporting the following  
  * modes: SDRAM/LPSDR SDRAM, SRAM, PSRAM, NOR Flash and NAND Flash. With the possibility to remap FMC bank 1 (NOR/PSRAM 1 and 2\) and FMC SDRAM bank 1/2 in the Cortex-M4 code area  
  * Good to use with graphic LCD controllers \- supports the Intel 8080 and Motorola 6800 modes  
* NVIC \- nested vector interrupt controller   
  * 16 priority levels   
  * 91 maskable interrupt channels   
  * 16 interrupt lines of Cortex M4 with FPU core 

