/*
 * File:   adc1.c
 * Author: balas
 *
 * Created on 6 June, 2025, 9:59 AM
 */

#pragma config FOSC = HS        
#pragma config WDTE = OFF       
#pragma config PWRTE = OFF      
#pragma config BOREN = ON       
#pragma config LVP = OFF         
#pragma config CPD = OFF        
#pragma config WRT = OFF        
#pragma config CP = OFF
#include<htc.h>
__CONFIG(0x3f7a);
void main()
{
TRISA0=1;
TRISB=0X00;
TRISC=0X00;
ADCON0=0X81;
ADCON1=0XC0;
while(1)
{
GO_DONE=1;
while(GO_DONE);
PORTB=ADRESL;
PORTC=ADRESH;
}
}