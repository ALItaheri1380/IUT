
#include "main.h"
#include "keypad.h" 
#define PORTKey GPIOD
char keypad(void)
{
 char row[4]={0x10,0x20,0x40,0x80};
 char key=100;
 char c;
 for (int r=0;r<4;r++)
 {
 keypad_write(row[r]);
 c=20;

 if (keypad_read_pin(0)==1) c=0;
 if (keypad_read_pin(1)==1) c=1;
 if (keypad_read_pin(2)==1) c=2;
 if (keypad_read_pin(3)==1) c=3;
 if (!(c==20)){
 key=(r*4)+c;
 keypad_write(0xf0);
 while (keypad_read_pin(0)==1) {HAL_Delay(10);}
 while (keypad_read_pin(1)==1) {HAL_Delay(10);}
 while (keypad_read_pin(2)==1) {HAL_Delay(10);}
 while (keypad_read_pin(3)==1) {HAL_Delay(10);}
 }
 keypad_write(0xf0);
 }
 return key;
} 

void keypad_write(int data)
{
 PORTKey->ODR =(PORTKey->ODR & 0xffffff00) | (data & 0x000000ff);
}
int keypad_read_pin( int pin)
{
 return (PORTKey->IDR >> pin) & 0x00000001;
}
int keypad_read( void)
{
 return (PORTKey->IDR & 0x000000FF);
}