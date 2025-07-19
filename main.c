/*
 * File:   main.c
 * Author: balas
 *
 * Created on 8 May, 2025, 8:00 PM
 */
#pragma config FOSC = HS        
#pragma config WDTE = OFF       
#pragma config PWRTE = OFF      
#pragma config BOREN = ON       
#pragma config LVP = OFF         
#pragma config CPD = OFF        
#pragma config WRT = OFF        
#pragma config CP = OFF

#include <xc.h>
#define _XTAL_FREQ 2000000
#define rs RC0
#define rw RC1
#define en RC2
#define delay for(j=0;j<1000;j++)
int j;
void lcd_init();
void cmd(unsigned char a);
void dat(unsigned char b);
void show(unsigned char *s);
void main(){
    unsigned int i;
    TRISB=0;
    TRISC=0;
    
    lcd_init();
    cmd(0x8A);
    show("WELCOME TO IOT");
    while(1){
        for(int i=0;i<15000;i++);
        cmd(0x18);
        for(int i=0;i<15000;i++);
    }
}
void lcd_init(){
    cmd(0x38);
    cmd(0x0c);
    cmd(0x06);
    cmd(0x80);
}
void cmd(unsigned char a){
    PORTB=a;
    rs=0;
    rw=0;
    en=1;
    delay;
    en=0;
}
void dat(unsigned char b){
    PORTB=b;
    rs=1;
    rw=0;
    en=1;
    delay;
    en=0;
}
void show(unsigned char *s){
    while(*s){
        dat(*s++);
    }
}