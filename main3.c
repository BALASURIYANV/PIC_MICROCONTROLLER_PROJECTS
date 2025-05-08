/*
 * File:   main3.c
 * Author: balas
 *
 * Created on 8 May, 2025, 6:23 PM
 */
#pragma config FOSC = HS        
#pragma config WDTE = OFF       
#pragma config PWRTE = OFF      
#pragma config BOREN = ON       
#pragma config LVP = ON         
#pragma config CPD = OFF        
#pragma config WRT = OFF        
#pragma config CP = ON  

#include <xc.h>
#define _XTAL_FREQ 2000000

void main(void) {
    TRISB = 0x07; // RB0, RB1, RB2 as input (00000111)
    TRISC = 0x00; // PORTC as output
    PORTC = 0x00;

    while(1) {
        if (PORTBbits.RB0 == 1) {
            PORTC = 0x0F; // LEDs 1?4 ON
        } 
        else if (PORTBbits.RB1 == 1) {
            PORTC = 0xF0; // LEDs 5?8 ON
        } 
        else if (PORTBbits.RB2 == 1) {
            PORTC = 0x00; // All LEDs OFF
        }
    }
}

