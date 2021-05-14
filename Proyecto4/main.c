//Noel Prado
//19025
//Proyecto 4

#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
//#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/uart.h"

uint32_t loadval;

uint8_t parqueoTotal = 0;

uint8_t tabla7(uint8_t entrada)
{
    //el 7 segmetnos esta conectado al puerto F (0 a 4) y a los pines del puerto D PD2 y PD3
    // D3, D2, F4, F3 , F2, F1, F0
    // C,  D,  E,  G,  F ,  A,  B

    //esta tabla como que regresa la mascara
    uint8_t tabla[] = { 0b01110111, 0b01000001, 0b00111011, 0b01101011,
                        0b01001101, 0b01101110, 0b01111110, 0b01000011,
                        0b01111111, 0b01101111, 0b01011111, 0b01111100,
                        0b00110110, 0b01111001, 0b00111110, 0b00011110 };

    return tabla[entrada];
}

void sevenseg(uint8_t parqueo);

int main(void)
    {

    //configuraci�n del reloj
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

    //configuraci�n UART

        SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

        GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

        UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
        UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
        UART_CONFIG_PAR_NONE);

        UARTFIFOLevelSet(UART0_BASE, UART_FIFO_TX1_8, UART_FIFO_RX1_8);

        UARTEnable(UART0_BASE);





    uint32_t parqueo1 = 0;
    uint8_t park1 = 0;
    uint8_t park2 = 0;
    uint8_t park3 = 0;
    uint8_t park4 = 0;

    uint32_t parqueo2 = 0;
    uint32_t parqueo3 = 0;
    uint32_t parqueo4 = 0;

    //sevenseg(parqueoTotal);

    //Loop forever
    while (1)
    {
        SysCtlDelay(10000);

        parqueo1 = GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_2);

        parqueo2 = GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_3);

        parqueo3 = GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_1);

        parqueo4 = GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_5);

        parqueoTotal = park1 + park2 + park3 + park4;

        UARTCharPut(UART0_BASE, park1);


        sevenseg(parqueoTotal);

        if (parqueo1 == 0)
        {

            GPIOPinWrite(GPIO_PORTA_BASE, 0b1000, 0b1111);
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2, 0b0000);

            if (park1 == 1)
            {
                park1 = 0;

            }

        }
        else
        {
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, 0b000);
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2, 0b1111);
            if (park1 == 0)
            {

                park1 = 1;
            }
        }

        if (parqueo2 == 0)
        {

            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4, 0);
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_6, 255);

            if (park2 == 1)
            {
                park2 = 0;

            }

        }
        else
        {
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4, 255);
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_6, 0);

            if (park2 == 0)
            {

                park2 = 1;
            }
        }

        if (parqueo3 == 0)
        {

            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_7, 0);
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, 255);

            if (park3 == 1)
                {
                    park3 = 0;

                }

        }
        else
        {
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_7, 255);
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, 0);

            if (park3 == 0)
                    {

                        park3 = 1;
                    }
        }

        if (parqueo4 == 0)
        {

            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0);
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0, 255);

            if (park4 == 1)
                 {
                     park4 = 0;

                 }

        }
        else
        {
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 255);
            GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0, 0);

            if (park4 == 0)
                      {

                          park4 = 1;
                      }
        }

    }

}

void sevenseg(uint8_t parqueo)
{

    uint32_t var = tabla7(parqueo);
    uint8_t var2 = var & 0b00011111;

    uint8_t aux = var;
    aux = (aux >> 3);
    uint8_t var3 = aux;

    GPIOPinWrite(GPIO_PORTF_BASE, 0b11111, var2);
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2 | GPIO_PIN_3, var3);

}



