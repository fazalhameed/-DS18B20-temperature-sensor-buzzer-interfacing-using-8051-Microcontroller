#include<reg51.h>
#include "temprature.h"
#define LCD_data P0

sbit en=P2^7;
sbit rs=P2^6;
sbit wr=P2^5;
unsigned char index=0;
unsigned int select[]  =  {0x0C,0x08,0x04,0x00};
unsigned int message[] = {0x3f,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6f};
unsigned char values[4];
void TEM();
unsigned int indexx=0;
unsigned char tmp_lsb=0,tmp_msb=0;
unsigned char Unite,Ten,intpart,decpart;
char tmp_f;
unsigned char tmp_c;
sbit DQ= P3^7;
sbit buzzer_pin=P1^5;

void ow_reset()
{
DQ = 1; //pull DQ line low
delay_18B20(8); // leave it low for 480us
DQ = 0; // allow line to return high
delay_18B20(65); // wait for presence
DQ=1;
delay_18B20(20);    
}  

void delay_18B20(unsigned int ud)
{
    while(ud--); 
}

// READ_BYTE - reads a byte from the one-wire bus.
unsigned char read_byte(void)
{
    unsigned char i=0;
    unsigned char dat = 0;
    for (i=8;i>0;i--){
          DQ = 0;
          dat>>=1;
          DQ = 1;
          if(DQ)
          dat |= 0x80;
          delay_18B20(4);
    }
    return(dat);
}
// WRITE_BYTE - writes a byte to the one-wire bus.
void write_byte(char dat)
{
    unsigned char i=0;
    for (i=8; i>0; i--){
        DQ = 0;
        DQ = dat&0x01;
        delay_18B20(5);
        DQ = 1;
        dat>>=1;
    }
}
void Read_Temperature(void)
{
ow_reset();
write_byte(0xCC); //Skip ROM
write_byte(0x44); // Start Conversion
delay_18B20(10); 
ow_reset();
write_byte(0xCC); // Skip ROM
write_byte(0xBE); // Read Scratch Pad
delay_18B20(10);
	
tmp_msb = read_byte(); // Sign byte + msbit
tmp_lsb = read_byte(); // Temp data plus lsb

tmp_c = ((tmp_lsb*256+tmp_msb)>>4);
tmp_f = (((int)tmp_c)* 9)/5 + 32;
}
void hex2lcd(unsigned char z){

	Ten=(z%100/10) + 0x30; //ten
	Unite=(z%10) + 0x30; //uni
	intpart = (int)z;
  decpart = (z - intpart) + 0x30;
	lcd_write(Ten);
	lcd_write(Unite);
	lcd_string(".");
	lcd_write(decpart);
}
void timer0_intrupt (void) interrupt 1   // called after 50 ms 
{
	indexx+=1;
	if(indexx==400)
	{
  LCD_Command(0x80);
	lcd_string("Temp:");
  Read_Temperature();
	hex2lcd(tmp_c);
	lcd_string(" C");
	indexx=0;
	LCD_Command(0xc0);
	lcd_string("Temp:");
	Read_Temperature();
	hex2lcd(tmp_f);

	lcd_string(" f");
	indexx=0;
	}
	display_num_7seg(tmp_c);
	values_on_ssd();
  
	if(tmp_c>=33)
	{
		buzzer_pin=0;
		delay1(2);
		buzzer_pin=1;
		delay1(2);
	}
	
	buzzer_pin=1;
	TH0=0xFC;
	TL0=0x18;
}

void TEM()
{
  lcd_init();
	IE=0x82; // enable timer 0 interrupt and serial interrupt

	TMOD = 0x21; // using timer0 in mode1 and timer1 in mode2
	SCON=0x50; // Asyncronous mode, 8-bit and 1-stop bit
	TH1=0xFD;
	TH0=0xFC;
	TL0=0x18;
	TR0=1;
	TR1=1;
while(1)
	{
	  display_num_serial(tmp_c);
    serial_data();
		display_num_serial(tmp_f);
    serial_data();
	}
}
void lcd_init()
{
	delay1(20);		/* LCD Power ON Initialization time >15ms */
	LCD_Command (0x38);	/* Initialization of 16X2 LCD in 8bit mode */
	LCD_Command (0x0E);	/* Display ON Cursor blinking */
	LCD_Command (0x06);	/* Auto Increment cursor */
	LCD_Command (0x01);	/* clear display */
	LCD_Command (0x80);	/* cursor at home position */

}
void lcd_string(unsigned char *lcd_data)
{
   while(*lcd_data)
   {
   lcd_write(*lcd_data++);
   }

}

void LCD_Command (unsigned char cmd)	
{
	LCD_data= cmd;
	rs=0;				/* command reg. */
	wr=0;				/* Write operation */
	en=1; 
	delay1(1);
	en=0;
	delay1(5);
}
void lcd_write(unsigned char lcd_data)
{
LCD_data=lcd_data;
rs=1;
wr=0;
en=1;
delay1(1);
en=0;

}
void delay1(unsigned int count)  /* Function to provide delay Approx 1ms */
{
	int i,j;
	for(i=0;i<count;i++)
	for(j=0;j<112;j++);
}
void display_num_7seg(unsigned char num)
{
 int i=2;
 while(num!=0)
 {
  values[i]=num%10;
	 num=num/10;
	 i--;
 }
 
 }
void values_on_ssd(void)
 {
  switch(values[index])
	{
		case 0:
		   {
			 P2=select[index];
			 P0=message[0];		 
			 }
	     break;
		case 1:
		   {
			 P2=select[index];
			 P0=message[1];		 
			 }
	     break;
		case 2:
		   {
			 P2=select[index];
			 P0=message[2];		 
			 }
	     break;
		case 3:
		   {
			  P2=select[index];
			 P0=message[3];		 
			 }
	     break;
		case 4:
		   {
			 P2=select[index];
			 P0=message[4];		 
			 }
	     break;
		case 5:
		   {
			  P2=select[index];
			 P0=message[5];		 
			 }
	     break;
		case 6:
		   {
			  P2=select[index];
			 P0=message[6];		 
			 }
	     break;
		case 7:
		   {
			 P2=select[index];
			 P0=message[7];		 
			 }
	     break;
		case 8:
		   {
			 P2=select[index];
			 P0=message[8];		 
			 }
	     break;
		case 9:
		   {
			 P2=select[index];
			 P0=message[9];		 
			 }
	     break;
	default:
		break;
	}
 index+=1;
	if(index > 2)
	{
          index=0;
	 }
}
 unsigned char Unite1,Ten1,Hunderd1;
unsigned char j=0;
unsigned char z;
unsigned char serial_values[5]={0};
	
void display_num_serial(unsigned int z)
{
	Ten1=(z%100/10) + 0x30; //ten
	Unite1=(z%10) + 0x30; //unit
	serial_values[1]= Ten1;
	serial_values[2]= Unite1;
	serial_values[3]='\n';
 }
void serial_data(void)
	{
	 for(z=0;z<6;z++)
	 {
	 SBUF=serial_values[z];
		 while(TI==0);
		  TI=0;
	    delay1(100);
	 }

 }
void main()
{
	TEM();
}
