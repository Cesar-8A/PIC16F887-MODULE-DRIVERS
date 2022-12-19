//this is .c file for keypad driver

/*
void interrupt(){
 if(PIR1.ADIF){ //CHECKING ADC FLAG
  ADC_OFF;
  input_value = (ADRESH << 8); // READING THE CONVERSION REGISTER (THE RIGHT PART)
  input_value = input_value | ADRESL; // READING THE CONVERSION REGISTER (THE RIGHT PART)
  input_value = input_value & 0x03FF; //MAKING SURE THAT INPUT_VALU ONLY STORES THE CONVERSION REGISTER VALUE
  PIR1.ADIF = CLEAR; //SETTING DOWN THE ADC FLAG
 }
}    */

void keypad_init(){
              /* INITIAL SETTINGS FOR DRIVER ON PIC16F887*/

  /* SETTING COMPARE MODULE */
     /* WE ARE USING COMPARE MODULE DUE TO ITS FEATURES (ALLOWS TO ENABLE PERIODIC ADC CONVERSIONS WITHOUT AN INTERRUPT) */
     CCP2CON.CCP2M3= SET;   //SET THE CCP2 REGISTER TO COMPARE MODE ON SPECIAL EVENT TRIGGER ADC
     CCP2CON.CCP2M2= CLEAR;
     CCP2CON.CCP2M1= SET;
     CCP2CON.CCP2M0= SET;

     //THE COMPARE MODULO WILL USE THE CCPR2 REGISTER AS A REFERENCE, WE WILL SET IT AS 255 BECAUSE WE WANT THE TMR1 TO COUNT WITH
     //FOSC/4, AND PIC IS CONTEMPLATED AS WORKING ON 4MHz, SO EVERY COUNT ON TMR1 IS EQUAL TO 1 MICRO SECOND
     CCPR2H = 0x00; CCPR2L = 0xFF; //SETTING THE COMPARE REGISTER TO 255

  /* SETTING ADC */
     //CHANNEL IS SELECTED AS DEFAULT (RA0)
     PORT_keypad = CLEAR;
     TRIS_keypad = 0xFF; //SETTING PORT AS INPUT
     ANSEL= 0xFF; //PORTA AS ADC (ANALOG) INPUTS
     ADCON0.ADCS0= SET; //PUT ADC TO FOSC/8
     ADCON0.ADCS1= CLEAR;
     INTCON.PEIE= SET; //PERIPEHRICAL INTERRUPT ENABLE (REQUIRED BY ADC INTERRUPT)
     ADCON1.ADFM= SET; //JUSTIFY TO RIGHT SIDE
     PIE1.ADIE= SET; //ENABLE ADC INTERRUPTS
     //ADC_ON; //ADC ENABLE



              /* SETTING PIC */
     INTCON.GIE =SET;
     INTCON.PEIE =SET;

  /* SETTING TMR1 */
     T1CON.TMR1ON= SET; //ENABLES TMR1
     T1CON.TMR1CS= CLEAR; //TMR1 SET TO FOSC/4

}

char evaluate_keypad(){
column = 0, row = 0, button=0;
RESET_TMR1;
//FOR EVALUTE ALL BUTTONS, EVERY ROW AND COLUMN NEED TO BE CHECKED

 //CHECKING ALL ROWS
  ADC_CH0;
  Delay_us(50);
  ADC_ON;
  RESET_TMR1;
  Delay_us(260);
  while(ADCON0.GO_DONE);
  if(input_value < 1000){ row=1;}

  ADC_CH1;
  Delay_us(50);
  ADC_ON;
  RESET_TMR1;
  Delay_us(260);
  while(ADCON0.GO_DONE);
  if(input_value < 1000){ row=2;}

  ADC_CH2;
  Delay_us(50);
  ADC_ON;
  RESET_TMR1;
  Delay_us(260);
  while(ADCON0.GO_DONE);
  if(input_value < 1000){ row=4;}


  ADC_CH3;
  Delay_us(50);
  ADC_ON;
  RESET_TMR1;
  Delay_us(260);
  while(ADCON0.GO_DONE);
  if(input_value < 1000){ row=8;}

 //CHECKING ALL COLUMNS
  ADC_CH4;
  Delay_us(50);
  ADC_ON;
  RESET_TMR1;
  Delay_us(260);
  while(ADCON0.GO_DONE);
  if(input_value > 100){ column=1;}
  
  ADC_CH5;
  Delay_us(50);
  ADC_ON;
  RESET_TMR1;
  Delay_us(260);
  while(ADCON0.GO_DONE);
  if(input_value > 100) { column=2;}
  
  ADC_CH6;
  Delay_us(50);
  ADC_ON;
  RESET_TMR1;
  Delay_us(260);
  while(ADCON0.GO_DONE);
  if(input_value > 100) { column=4;}
  
  ADC_CH7;
  Delay_us(50);
  ADC_ON;
  RESET_TMR1;
  Delay_us(260);
  while(ADCON0.GO_DONE);
  if(input_value > 100) { column=8;}
  
  button = row << 4 | column;
  if(button == 0x11){button = 1; return button;}
  if(button == 0x12){button = 2; return button;}
  if(button == 0x14){button = 3; return button;}
  if(button == 0x18){button = 'A'; return button;}
  if(button == 0x21){button = 4; return button;}
  if(button == 0x22){button = 5; return button;}
  if(button == 0x24){button = 6; return button;}
  if(button == 0x28){button = 'B'; return button;}
  if(button == 0x41){button = 7; return button;}
  if(button == 0x42){button = 8; return button;}
  if(button == 0x44){button = 9; return button;}
  if(button == 0x48){button = 'C'; return button;}
  if(button == 0x81){button = '*'; return button;}
  if(button == 0x82){button = 0; return button;}
  if(button == 0x84){button = '#'; return button;}
  if(button == 0x88){button = 'D'; return button;}
  return '/';
}