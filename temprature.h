#ifndef Main_H
#define Main_H

sbit r0=P1^0;
sbit r1=P1^1;
sbit r2=P1^2;
sbit r3=P1^3;
sbit c0=P1^4;
sbit c1=P1^5;
sbit c2=P1^6;
sbit c3=P1^7;
//lcd
void dataa(unsigned char lcd_data);
void MSDelay(unsigned int itime);
void lcd_init(void);
void lcd_write(unsigned char);
void LCD_Command (unsigned char);
void delay1(unsigned int);
void lcd_string(unsigned char *);

//DS18B20 temperature sensor & buzzer
void ow_reset(void);
unsigned char read_byte(void);
void write_byte(char);
void delay_18B20(unsigned int);
void Read_Temperature(void);
void hex2lcd(unsigned char hex);

//SSD seven segment display
void display_num_7seg(unsigned char);
void values_on_ssd(void);

// serial
void display_num_serial(unsigned int);
void serial_data(void);
#endif