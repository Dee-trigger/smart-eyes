

unsigned int IoTI2cWrite(unsigned int id, unsigned short deviceAddr, const unsigned char *data, unsigned int dataLen);


unsigned int IoTI2cRead(unsigned int id, unsigned short deviceAddr, unsigned char *data, unsigned int dataLen);


unsigned int IoTI2cInit(unsigned int id, unsigned int baudrate);


unsigned int IoTI2cDeinit(unsigned int id);

unsigned int IoTI2cSetBaudrate(unsigned int id, unsigned int baudrate);//设置I2C设备的波特率

