 #include <xc.h>
#define _XTAL_FREQ 20000000

#define SDA RC4
#define SCL RC3

void I2C_Init() {
    SSPCON = 0x28;
    SSPCON2 = 0x00;
    SSPADD = ((_XTAL_FREQ / 4) / 100000) - 1;
    SSPSTAT = 0x00;
    TRISC3 = 1;
    TRISC4 = 1;
}

void I2C_Wait() {
    while ((SSPCON2 & 0x1F) || (SSPSTAT & 0x04));
}

void I2C_Start() {
    I2C_Wait();
    SEN = 1;
}

void I2C_Stop() {
    I2C_Wait();
    PEN = 1;
}

void I2C_Write(unsigned char data) {
    I2C_Wait();
    SSPBUF = data;
}

void LCD_Command(unsigned char cmd) {
    unsigned char temp = cmd & 0xF0;
    I2C_Start();
    I2C_Write(0x4E);
    I2C_Write(temp | 0x0C);
    I2C_Write(temp | 0x08);
    temp = (cmd << 4) & 0xF0;
    I2C_Write(temp | 0x0C);
    I2C_Write(temp | 0x08);
    I2C_Stop();
    __delay_ms(2);
}

void LCD_Char(unsigned char data) {
    unsigned char temp = data & 0xF0;
    I2C_Start();
    I2C_Write(0x4E);
    I2C_Write(temp | 0x0D);
    I2C_Write(temp | 0x09);
    temp = (data << 4) & 0xF0;
    I2C_Write(temp | 0x0D);
    I2C_Write(temp | 0x09);
    I2C_Stop();
    __delay_ms(2);
}

void LCD_Init() {
  __delay_ms(50);
    LCD_Command(0x33);
    LCD_Command(0x32);
    LCD_Command(0x28);
    LCD_Command(0x0C);
    LCD_Command(0x01);
    __delay_ms(2);
}

void LCD_String(const char *str) {
    while (*str) {
        LCD_Char(*str++);
    }
}

void LCD_SetCursor(unsigned char row, unsigned char col) {
    unsigned char cmd;
    cmd = (row == 1) ? 0x80 + col : 0xC0 + col;
    LCD_Command(cmd);
}

void main() {
    TRISB0 = 1;
    TRISB1 = 1;
    TRISD0 = 0;
    TRISD1 = 0;
    I2C_Init();
    LCD_Init();

    while (1) {
        if (PORTBbits.RB0 == 0) {
            PORTDbits.RD0 = 1;
            LCD_SetCursor(1, 0);
            LCD_String("Door: Open");
        } else {
            PORTDbits.RD0 = 0;
            LCD_SetCursor(1, 0);
            LCD_String("Door: Close");
        }

        if (PORTBbits.RB1 == 0) {
            PORTDbits.RD1 = 1;
            LCD_SetCursor(2, 0);
            LCD_String("Light: ON ");
        } else {
            PORTDbits.RD1 = 0;
            LCD_SetCursor(2, 0);
            LCD_String("Light: OFF");
        }

        __delay_ms(20);
    }
}