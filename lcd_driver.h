
//this is .h file for LCD driver
//THIS VERSION ONLY WRITES TO LCD
unsigned char BIT_MODE = 4, init_call=1;
unsigned char numbers[]={0,0,0}, i;

#define SET 1
#define CLEAR 0

#define PORT_LCD PORTB
#define TRIS_LCD TRISB
#define PORT_4B_PREPARE (PORT_LCD.B7=CLEAR,PORT_LCD.B6=CLEAR,PORT_LCD.B5=CLEAR,PORT_LCD.B4=CLEAR)

#define  E  PORT_LCD.B2
#define  RW PORT_LCD.B1
#define  RS PORT_LCD.B0

#define LEFT 0    //for shift to left
#define RIGHT 1    //for shift to right

#define CURSOR 0    //for cursor shift
#define DISPLAY 1    //for display sifht

//INIT DISPLAY 8 BIT MODE OR 4 BIT MODE (WRITE 4 OR 8)
void lcd_init(char BIT_MODE); 

//ENABLE LCD INPUT
void enable_lcd();        

//SET BIT MODE (THIS IS ONLY ACCESSED BY INIT FUNCTION, NO ACCESS IN OTHER MOMENT TAKES EFFECT)
void mode_set_lcd();         

//FOR SENDING INFORMATION TO LCD (ALMOST ALL OTHER FUNCTIONS USES IT, BUT CAN BE ACCESSED SEPARATELY IF NEEDED)
void send_data(unsigned char datos);

//CLEAR THE WHOLE DISPPLAY
void clear_display(); 

//PRINT IN SCREEN, THIS NEEDS AN END CHARACTER, DEFAULT END CHARACTER IS '/'
void prints(const unsigned char *string); //FOR STRINGS
void printc(unsigned char character); //FOR SINGLE CHARACTERS
void printn(unsigned char number); //FOR NUMBERS

//CHOOSE IN WHAT PART OF DISPLAY START WRITING
//THE FIRST ROW GOES FROM 0x00 TO 0x27 AND THE SECOND GOES FROM 0x40 TO 0x67
void choose_display_position(unsigned char choose);

//SETS THE CURSOR TO HOME (ADDRESS 0)
void home(); 

//SHIFTS CURSOR TO LEFT OR RIGHT (USE TIMES FOR THE NUMBER O SHIFTS TO BE DONE)
void shift(unsigned L_R, unsigned which, unsigned char times);

#include "lcd_driver.c"