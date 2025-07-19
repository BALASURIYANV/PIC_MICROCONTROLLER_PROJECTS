/*
 * File:   newmain.c
 * Author: balas
 *
 * Created on 18 May, 2025, 11:23 AM
 */


 #include <xc.h>
#define _XTAL_FREQ 20000000  // Define oscillator frequency for delay

// Configuration Bits
#pragma config FOSC = HS        // High-Speed Oscillator
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage Programming disabled
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// Define LCD control pins
#define RS RB0
#define EN RB1

// Define LCD data pins
#define D4 RB2
#define D5 RB3
#define D6 RB4
#define D7 RB5

// Define Keypad row pins
#define R1 RD0
#define R2 RD1
#define R3 RD2

// Define Keypad column pins
#define C1 RD3
#define C2 RD4
#define C3 RD5

// Function to send command to LCD
void lcd_cmd(unsigned char cmd) {
    RS = 0;
    D4 = (cmd >> 4) & 0x01;
    D5 = (cmd >> 5) & 0x01;
    D6 = (cmd >> 6) & 0x01;
    D7 = (cmd >> 7) & 0x01;
    EN = 1; __delay_ms(2); EN = 0;
    D4 = cmd & 0x01;
    D5 = (cmd >> 1) & 0x01;
    D6 = (cmd >> 2) & 0x01;
    D7 = (cmd >> 3) & 0x01;
    EN = 1; __delay_ms(2); EN = 0;
}

// Function to send data to LCD
void lcd_data(unsigned char data) {
    RS = 1;
    D4 = (data >> 4) & 0x01;
    D5 = (data >> 5) & 0x01;
    D6 = (data >> 6) & 0x01;
    D7 = (data >> 7) & 0x01;
    EN = 1; __delay_ms(2); EN = 0;
    D4 = data & 0x01;
    D5 = (data >> 1) & 0x01;
    D6 = (data >> 2) & 0x01;
    D7 = (data >> 3) & 0x01;
    EN = 1; __delay_ms(2); EN = 0;
}

// Function to initialize LCD
void lcd_init() {
    TRISB = 0x00;  // Set PORTB as output
    lcd_cmd(0x02); // Initialize LCD in 4-bit mode
    lcd_cmd(0x28); // 2 lines, 5x8 matrix
    lcd_cmd(0x0C); // Display on, cursor off
    lcd_cmd(0x06); // Increment cursor
    lcd_cmd(0x01); // Clear display
    __delay_ms(2);
}

// Function to scan keypad and return pressed key
char keypad_scan() {
    TRISD = 0xF8;  // RD0?RD2 as outputs (rows), RD3?RD5 as inputs (columns)
    PORTD = 0x00;  // Clear PORTD

    // Set R1 low and check columns
    R1 = 0; R2 = R3 = 1;
    if (!C1) return '1';
    if (!C2) return '2';
    if (!C3) return '3';

    // Set R2 low and check columns
    R2 = 0; R1 = R3 = 1;
    if (!C1) return '4';
    if (!C2) return '5';
    if (!C3) return '6';

    // Set R3 low and check columns
    R3 = 0; R1 = R2 = 1;
    if (!C1) return '7';
    if (!C2) return '8';
    if (!C3) return '9';

    return 0;  // No key pressed
}

void main() {
    lcd_init();  // Initialize LCD
    char key;
    while (1) {
        key = keypad_scan();  // Scan for key press
        if (key) {
            lcd_data(key);  // Display key on LCD
            __delay_ms(500);  // Debounce delay
        }
    }
}