//this is .c file for i2c driver


void i2c_init(){
  SSPCON = 0b00101000; //MASTER MODE
  SSPCON2 = 0x00;
  SSPADD = (4000000 / (4 * 100000)) - 1; // SET TO 100KHZ
  SSPSTAT = 0x00;
  TRISC.B3 = SET;
  TRISC.B4 = SET;
}

void i2c_start(unsigned char ADDRESS, unsigned char DO){
     DO = DO & 0x01;                       //ASSURE THAT DO IS AN ACCEPTED VALUE
     ADDRESS = ADDRESS<<1;                 //SETTING ADDRESS PROPER FORMAT
     START_COM;                            //START CONDITION IS SET
     while(~PIR1.SSPIF);                   //THIS CONFIRMS THE START CONDITION WAS SET
     PIR1.SSPIF=CLEAR;
     SSPBUF = ADDRESS | DO;                //LOAD ADDRESS AND CLEAR THE LAST BIT BECAUSE OF WRITE MODE
     while(SSPSTAT.BF);                    //WAIT FOR SENDING DATA TO FINISH
     while(~PIR1.SSPIF);                   //WAIT FOR THE NINTH CLOCK CYCLE TO HAPPEN
     PIR1.SSPIF=CLEAR;
}

void i2c_rstart(unsigned char ADDRESS, unsigned char DO){
     DO = DO & 0x01;                       //ASSURE THAT DO IS AN ACCEPTED VALUE
     ADDRESS = ADDRESS<<1;                 //SETTING ADDRESS PROPER FORMAT
     REPEATED_START;                       //REPEATED START
     while(~PIR1.SSPIF);                   //THIS CONFIRMS THE START CONDITION WAS SET
     PIR1.SSPIF=CLEAR;
     SSPBUF = ADDRESS | DO;                //LOAD ADDRESS AND CLEAR THE LAST BIT BECAUSE OF WRITE MODE
     while(SSPSTAT.BF);                    //WAIT FOR SENDING DATA TO FINISH
     while(~PIR1.SSPIF);                   //WAIT FOR THE NINTH CLOCK CYCLE TO HAPPEN
     PIR1.SSPIF=CLEAR;
}

char i2c_send(unsigned char DATA){        //SET I2C TO  MASTER OR SLAVE
     SSPBUF = DATA;                        //SET THE DATA WE ARE WILLING TO SEND
     while(SSPSTAT.BF);                    //WAIT FOR SENDING DATA TO FINISH
     while(~PIR1.SSPIF);                   //WAIT FOR THE NINTH CLOCK CYCLE TO HAPPEN
     PIR1.SSPIF=CLEAR;
     return SSPCON2.ACKSTAT;               //LET KNOW IF ACKNOWLEDGE WAS RECEIVE
}

char i2c_receive(){
     I2C_RECEIVE;
     while(~PIR1.SSPIF);                    //THIS CONFIRMS THE STOP CONDITION WAS SET
     PIR1.SSPIF=CLEAR;
     return SSPBUF;
}

void i2c_stop(){
     STOP_COM;                              //SET STOP CONDITION
     while(~PIR1.SSPIF);                    //THIS CONFIRMS THE STOP CONDITION WAS SET
     PIR1.SSPIF=CLEAR;
}