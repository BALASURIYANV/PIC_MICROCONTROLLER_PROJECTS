/*
 * File:   newmain.c
 * Author: balas
 *
 * Created on 12 June, 2025, 11:30 AM
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
#include<htc.h>
#define SBIT_TXEN 5
#define SBIT_SPEN 7
#define SBIT_CREN 4
void UART_Init(int baudRate)
{
TRISC=0x80; //Configure RX pin as input and TX pin as output
TXSTA=(1<<SBIT_TXEN); //Asynchronous mode, 8bit data & enable transmitter
RCSTA=(1<<SBIT_SPEN)|(1<<SBIT_CREN); //enable serial port and 8 bit contimuous reveive
SPBRG=(20000000UL/(long)(64UL*baudRate))-1; //baud rate @20MHz clock
}
void UART_TxChar(char ch)
{
while(TXIF==0); //wait till transmission register becomes empty
TXIF=0; //clear transmitter flag
TXREG=ch;
}
char UART_RxChar()
{
while(RCIF==0); //wait till the data is received
RCIF=0; //clear reveive flag
return(RCREG); //return the received data to calling function
}
int main()
{
char i,a[]={"Innovation Technology Hub"};
char ch;
UART_Init(9600); //initiate the UART module woth 9600 baud rate
for(i=0;a[i]>0;i++)
{
UART_TxChar(a[i]); //transmit predefined string
}
while(1)
{
ch=UART_RxChar(); //reveive a char from serial port
UART_TxChar(ch); //transmit the reveived char
}
}