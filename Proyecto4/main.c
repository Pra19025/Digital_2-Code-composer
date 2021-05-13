//Noel Prado
//19025
//Proyecto 4

#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/uart.h"

#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"



uint32_t loadval;

uint32_t parqueoTotal = 3;

uint32_t tabla7(uint32_t entrada)
{
    //el 7 segmetnos esta conectado al puerto F (0 a 4) y a los pines del puerto D PD2 y PD3
    // D3, D2, F4, F3 , F2, F1, F0
   // C,  D,  E,  G,  F ,  A,  B


    //esta tabla como que regresa la mascara
    static uint32_t tabla[] = { 0b01110111, 0b01000001, 0b00111011, 0b01101011,
                               0b01001101, 0b01101110, 0b01111110, 0b01000011,
                               0b01111111, 0b01101111, 0b01011111, 0b01111100,
                               0b00110110, 0b01111001, 0b00111110, 0b00011110 };

    return tabla[entrada];
}

void sevenseg(void);

int main(void)
{



    //configuración del reloj
    // a 40Mhz
    SysCtlClockSet(
    SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);




    //se configuran los pines como salidas (para los leds)
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, 255);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, 255);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    HWREG(GPIO_PORTF_BASE+GPIO_O_LOCK) = GPIO_LOCK_KEY;
       HWREG(GPIO_PORTF_BASE+GPIO_O_CR) |= GPIO_PIN_0;

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, 255);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, 255);

    //se configuran los pines como entradas (para los push buttons)
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, 255);


    //se configuran las pull up
    GPIOPadConfigSet(GPIO_PORTE_BASE, 255,
    GPIO_STRENGTH_8MA,
                     GPIO_PIN_TYPE_STD_WPU);

    //configuración del timer0 a 32 bits, periódico
    loadval = SysCtlClockGet() /100; //para que cuente poco tiempo

    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER0_BASE, TIMER_A, loadval - 1);

    //habilitando la interrupción del timer0
    IntEnable(INT_TIMER0A);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    TimerEnable(TIMER0_BASE, TIMER_A);

    IntRegister(INT_TIMER0A, sevenseg);

    uint32_t parqueo1 = 0;
    uint32_t parqueo2 = 0;
    uint32_t parqueo3 = 0;
    uint32_t parqueo4 = 0;

    //Loop forever
    while (1)
    {

        parqueo1 = GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_2);

        parqueo2 = GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_3);

        parqueo3 = GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_1);

        parqueo4 = GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_5);

        if (parqueo1 == 0)
        {

            GPIOPinWrite(GPIO_PORTA_BASE, 0b1000, 0b1111);
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2, 0b0000);
            //parqueoTotal--;

        }
        else
        {
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, 0b000);
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2, 0b1111);
            //parqueoTotal++;
        }

        if (parqueo2 == 0)
        {

            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4, 0);
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_6, 255);

        }
        else
        {
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4, 255);
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_6, 0);
        }

        if (parqueo3 == 0)
        {

            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_7, 0);
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, 255);

        }
        else
        {
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_7, 255);
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, 0);
        }

        if (parqueo4 == 0)
        {

            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0);
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0, 255);

        }
        else
        {
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 255);
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0, 0);
        }

    }

    return 0;
}

void sevenseg(void)
{
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);


    uint32_t var = tabla7(parqueoTotal);
    uint8_t var2 = var & 0b00011111;

    uint8_t aux = var ;
       aux = (aux >> 3);
       uint8_t var3= aux;


    GPIOPinWrite(GPIO_PORTF_BASE, 0b11111,var2);
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2 | GPIO_PIN_3,var3);


}



