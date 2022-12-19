//this is .c file for PWM driver BY DEFAULT IT USES PORTC PIN 2
void pwm_init(){
//SET PIN IN PROPER MODE
      CCP1CON.P1M0=CLEAR;
      CCP1CON.P1M1=SET;
      
      CCP1CON.CCP1M2=SET;
      CCP1CON.CCP1M3=SET;
      
      PIR1.TMR2IF=CLEAR;
      T2CON.TMR2ON=SET;
      TRISC.B2=CLEAR;
      
      pwm_period(256);
      //CALCULATING POWER IN PWM TERMS
      pulse_width(50);
}

void pulse_width(int width){
      CCP1CON|=((width&0x0003)<<4);
      CCPR1L=width>>2;
}

void pwm_period(int period){
      PR2=period-1;
}
