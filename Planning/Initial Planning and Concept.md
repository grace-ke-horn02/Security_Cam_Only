The hardware I have on hand can be used to create a full system:

* STM32 Nucleo F446RE  
* RaspberryPi 4  
* PIRs   
* Accelerometer   
* Temperature/humidity sensor   
* USB camera  
* PCIe camera   
* Light Sensor 

Hardware that I can get in the future:

* IR camera   
* Screen 

Concept \- Security camera:

* Security camera, triggered by motion and vibration   
  * Detect object motion in field of view with PIRs  
  * Place accelerometer on a surface, and if surface moves want to capture video   
    * Ideas of where accelerometer would be place: door or window  
* Light sensor can be used for image processing   
  * In the future determine if IR camera or visual light camera should be used   
  * Could be used to automate lighting   
* Temperature/humidity sensor \- just for fun  
  * Have it, so why not use it 

Concept \- Alarm Clock:

* RTC on RaspberryPi or STM can be used to trigger alarms  
* Simple database of alarms   
* Calendar based alarms \- can choose things like every other friday   
* App in python  

STM32 

* Peripheral management   
* Cannot use cameras with this   
* Simple 

RaspberryPi 

* Cameras are compatible with RaspberryPi   
* Human interface will run on RaspberryPi  
  * Connect to a server, or a screen   
* Embedded Linux system eventually 

