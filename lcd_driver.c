//this is .c file for LCD driver

void lcd_init(char BIT_MODE){
  //PREPARING PORT
  TRIS_LCD=CLEAR;
  PORT_LCD=CLEAR;

 BIT_MODE=BIT_MODE;
 Delay_ms(45);

 if(BIT_MODE == 4){
 BIT_MODE==BIT_MODE;
   //SET 4 BIT MODE
   PORT_LCD.B5=SET;
   enable_lcd();
   Delay_ms(5);
    //SET
   PORT_LCD=CLEAR;
   enable_lcd();
   send_data(0x28);
   enable_lcd();
   Delay_ms(5);
   //Display On
   PORT_LCD=0;
   enable_lcd();
   PORT_LCD=0xD0;//E0
   enable_lcd();
   Delay_ms(5);
 }
 else if (BIT_MODE==8){
  //algun dia primero dios
 }
 mode_set_lcd();
}

void choose_display_position(unsigned char choose){
  RS=CLEAR;
  RW=CLEAR;
  send_data((0x80|choose));
}

void clear_display(){
  RS=CLEAR;
  RW=CLEAR;
  send_data(0x01); //SEND CLEAR COMMAND
}

void shift(unsigned char L_R, unsigned char which, unsigned char times){
 while(times>0){
  RS=CLEAR;
  RW=CLEAR;
  send_data(0x10|(L_R<<2)|(which<<3));
  times--;
 }
}

void enable_lcd(){
   E=SET;
   E=CLEAR;
   Delay_ms(1);
}

void mode_set_lcd(){
if(init_call){
  if(BIT_MODE==4){
    //Mode Set
    PORT_LCD=CLEAR;
    enable_lcd();
    PORT_LCD=0x60;
    enable_lcd();
    Delay_ms(5);
    }
  else if(BIT_MODE==8){
    //algun dia primero dios
  }
  init_call  = CLEAR;
  }
}

void prints(const unsigned char *string){
  //WRITE DATA
 RS=SET;
 RW=CLEAR;
 while(1){
  if(*string=='/') break;
  send_data(*string);
  string=string+1;
 }
}

void printc(unsigned char character){
  //WRITE DATA
 RS=SET;
 RW=CLEAR;
 send_data(character);
}

void printn(unsigned char number){

 i=0;
 numbers[0]=0;
 numbers[1]=0;
 numbers[2]=0;
 //SLITTING
 while(number>=100){
   numbers[0]+=1;
   number-=100;
 }
  while(number>=10){
   numbers[1]+=1;
   number-=10;
 }
 numbers[2]=number;
 //WRITE DATA
 RS=SET;
 RW=CLEAR;
 if(numbers[0]==0) i++;
 if(numbers[1]==0) i++;
 while(i<3){
  send_data((0x30|numbers[i]));
  i++;
 }
}

void home(){
 RS=CLEAR;
 RW=CLEAR;
 send_data(0x02); //SEND RETURN HOME COMMAND
}

void send_data(unsigned char datos){

 if(BIT_MODE==4){
  PORT_4B_PREPARE;
  PORT_LCD |=datos&0xF0;//SEND MOST SIGNIFICANT NIBBLE FIRST
  enable_lcd();
  PORT_4B_PREPARE;
  PORT_LCD |=(datos<<4)&0xF0;//SEND LESS SIGNIFICANT NIBBLE FIRST
  enable_lcd();

 }
 else if(BIT_MODE==8){
  //PROXIMAMENTE SOLO EN CINES
 }
}