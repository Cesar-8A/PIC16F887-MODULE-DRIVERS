//this is .h file for i2c driver

#define SET_I2C_BITS (TRISC.B4=1, TRISC.B3=1)
#define CLEAR_I2C_BITS (TRISC.B4=0, TRISC.B3=0)
#define START_COM SSPCON2.SEN=1
#define STOP_COM  SSPCON2.PEN=1
#define I2C_RECEIVE SSPCON2.RCEN=1
#define REPEATED_START SSPCON2.RSEN=1
#define I2C_MODE SSPCON.SSPEN
#define MASTER 1
#define SLAVE 0
#define SET   1
#define CLEAR 0
#define READ  1
#define WRITE 0

#define RTC 0b1101000                                      //THIS IS DS1307 ADDRESS

void i2c_init();                                           //FOR NOW THIS SETS MASTER MODE AUTOMATICALLY
void i2c_start(unsigned char ADDRESS, unsigned char DO);   //START COMMUNICATION WITH ADDRESSED DEVICE
void i2c_rstart(unsigned char ADDRESS, unsigned char DO);  //DO A REPEATED START
char i2c_send(unsigned char DATA);                         //SEND DATA
char i2c_receive();                                        //RECEIVE DATA
void i2c_stop();                                           //STOP COMMUNICATION

#include "i2c_driver.c"