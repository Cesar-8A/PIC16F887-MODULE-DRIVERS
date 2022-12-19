//this is .h file for keypad driver
unsigned int input_value = 0;
char column = 0, row = 0, button=0;
#define SET 1
#define CLEAR 0
#define TRUE 1
#define FALSE 0

#define PORT_keypad (PORTA.B0,PORTA.B1,PORTA.B2,PORTA.B3,PORTA.B5,PORTE.B5,PORTE.B6,PORTE.B7) //this uses PORTA and PORTE
#define TRIS_keypad (TRISA.B0,TRISA.B1,TRISA.B2,TRISA.B3,TRISA.B5,TRISE.B5,TRISE.B6,TRISE.B7)
#define RESET_TMR1 (TMR1H=0, TMR1L=0)
#define ADC_ON (ADCON0.ADON= SET) //ADC ENABLE
#define ADC_OFF (ADCON0.ADON= CLEAR) //ADC OFF
#define ADC_BUSY ADCON0.GO_DONE
#define TRM_EN  T1CON.TMR1ON //ENABLES TMR1

 //Defines for changing channels
    #define ADC_CH0 (ADCON0 = 0b01000000)
    #define ADC_CH1 (ADCON0 = 0b01000100)
    #define ADC_CH2 (ADCON0 = 0b01001000)
    #define ADC_CH3 (ADCON0 = 0b01001100)
    #define ADC_CH4 (ADCON0 = 0b01010000)
    #define ADC_CH5 (ADCON0 = 0b01010100)
    #define ADC_CH6 (ADCON0 = 0b01011000)
    #define ADC_CH7 (ADCON0 = 0b01011100)



//void interrupt();     //if other interrupts are needed, set the content of this function inside the general interrupt function
void keypad_init();
char evaluate_keypad();

#include "keypad_driver.c"
