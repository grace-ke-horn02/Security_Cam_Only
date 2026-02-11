UART interaction b/w raspberry pi and stm32   
Communication will be done over UART. 

* Baud rate \- 115200  
* 8 data bits   
* 8 data bits \- 127 possible commands, 1 stop message value 

Read and write requests 

* Specific message for read   
* Specific message for write   
* Need a stop message   
* Send an acknowledge back  
* ASCII characters are 7 bits 

Specific communication:

* Request info command  
  * Can request specific information like sensor readings, configuration data, etc.   
* Send info \- respond to PI request  
* Write configuration info  
* STM message after sending interrupts to PI   
* Error message

Structure of message:

* Start byte \- 0xFF  
* Message length byte   
* Command byte   
* Payload  
  * Specific header for each type of data   
  * Data   
* CRC could be implemented eventually   
* End Byte \- 0x00

