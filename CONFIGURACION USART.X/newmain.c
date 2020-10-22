/*
 * File:   newmain.c
 * Author: Juan Pablo
 *
 * Created on 21 de octubre de 2020, 11:21 PM
 */

#include <xc.h>
#define _XTAL_FREQ 8000000
// CONFIG1
#pragma config FOSC = INTRC_CLKOUT// Oscillator Selection bits (INTOSC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)






int aux=1;
int p[44]={80,82,69,67,73,79,78,69,32,76,65,32,84,69,67,76,65,32,34,65,34,32,80,65,82,65,32,86,69,82,32,73,78,84,69,71,82,65,78,84,69,83,13,13};
int x[9]={70,69,82,68,73,78,65,78,13}; 
int x1[7]={74,85,65,78,80,73,13};
int x2[5]={76,85,73,83,13};
int x3[8]={67,65,80,79,82,65,76,13};
char entrada;

void __interrupt() usart(void){
      if(PIR1bits.RCIF==1){
            entrada=RCREG;
           if(entrada=='a'){
            for(int i=0;i<9;i++){
            while(TXSTAbits.TRMT==0);
            TXREG=x[i];
            __delay_ms(10);
        }  
            for(int i=0;i<7;i++){
            while(TXSTAbits.TRMT==0);
            TXREG=x1[i];
            __delay_ms(10);
        }
            for(int i=0;i<5;i++){
            while(TXSTAbits.TRMT==0);
            TXREG=x2[i];
            __delay_ms(10);
            }
            for(int i=0;i<8;i++){
            while(TXSTAbits.TRMT==0);
            TXREG=x3[i];
            __delay_ms(10);
            }
             }
            }
}

void main(void) {
    
     TRISCbits.TRISC7=1;       //pin RX como una entrada digital
     TRISCbits.TRISC6=0;      //pin TX como una salida digital
     
     
     TXSTA=0b00100110;      // 8bits, transmisión habilitada,modo asíncrono, alta velocidad
     RCSTA=0b10010000;     //puerto serial habilitado , recepción 8 bits, 
                          //Bit de habilitación de recepción continua habilitada
     BAUDCTL=0b00000000; //En el bit 3 se configura el generador de velocidad en baudios de 8 bits
     
     INTCON=0B11000000; // Se habilitan las interrupciones globales y perifericas en los bits 6 y 7
     PIE1=0b00100000;  //  Se habilita la interrupcion por recepcion de datos en el bit 5
     
     SPBRG=25;           //para una velocidad de 9600baudios con un oscilador de 4Mhz    
    
     
   while(1){
        if(aux==1){
                   for(int i=0;i<44;i++){
            while(TXSTAbits.TRMT==0);
            TXREG=p[i];
            __delay_ms(20);
                }
        }
        aux=0;
 
    }
    return;
}
    
