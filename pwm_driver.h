//this is .h file for PWM driver BY DEFAULT IT USES PORTC PIN 2

#define CLEAR 0
#define SET 1

void pwm_init();
void pulse_width(int width); //1023 bits de resolucion
void pwm_period(int period);

#include "pwm_driver.c"