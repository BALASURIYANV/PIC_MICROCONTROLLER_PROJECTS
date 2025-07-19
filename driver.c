/*
 * File:   driver.c
 * Author: balas
 *
 * Created on 12 June, 2025, 10:22 AM
 */
#pragma config FOSC = HS        
#pragma config WDTE = OFF       
#pragma config PWRTE = OFF      
#pragma config BOREN = ON       
#pragma config LVP = OFF         
#pragma config CPD = OFF        
#pragma config WRT = OFF        
#pragma config CP = OFF
#include<pic.h>
#include <xc.h>
void delay(int);
#define dcmotor PORTC
void main()
{
while(1)
{
TRISC=0;
dcmotor=0x05;
delay(1000000);
dcmotor=0x0a;
delay(1000000);
}
}
void delay(int a)
{
int i;
for(i=0;i<=a;i++);
}



