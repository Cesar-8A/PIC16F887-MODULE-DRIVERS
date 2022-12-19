
//this is .h file for eusart driver BY DEFAULT IT IS SET TO 2400 BAUD
#define SET 1
#define CLEAR 0
#define END '/' //USE THIS CHARACTER FOR SET THE LAST CHARACTER OF A STRING
#define DUMMY 0x00

unsigned char received_data=0;
unsigned char numb[]={0,0,0};

//void interrupt(); // if you are using more interrupts, put this inside the general interrupt function
void eusart_init(char SYNC_MODE, char H_SPEED);
void eusart_send(unsigned char *package);
void eusart_sendn(unsigned char number);
void eusart_sendc(unsigned char c);
void eusart_receiver(unsigned char choose);

#include "eusart_driver.c"