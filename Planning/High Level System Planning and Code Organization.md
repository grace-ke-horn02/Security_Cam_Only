Code Organization

* In Core is where main and application files are   
* Core/Src \- main  
* Core/App \- all personally developed modules  
* Core/App/CmdProcessing \- this will actually process UART commands  
* Core/App/Hal \- hardware abstraction. STM provided HAL   
* Core/App/IO \-  modules for peripherals      
* Core/App/Utilities \- helper functions 

Modules needed:

* Accelerometer   
* PIR sensors   
* Temp/Humidity sensor   
* Light Sensor   
* RTC   
* UART \- Raspberry Pi

