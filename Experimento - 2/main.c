//Noel Prado
//19025

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

uint32_t loadval;

uint8_t entrada;
uint8_t rojo = 0;
uint8_t verde = 0;
uint8_t azul = 0;

void toggle(void);
void entradaUART(void);

int main(void)
{

    //configuración del reloj
    // a 40Mhz
    SysCtlClockSet(
    SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);

    //se configuran los pines como salidas (son los leds)
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,
    GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);

    //configuración del timer0 a 32 bits, periódico
    loadval = SysCtlClockGet() * 2; // esta función me da el clock rate de la tiva.
    // loadval al tener el valor de la frecuencia de reloj, equivale a 1s (los pulsos que ocurren en 1s)
    //se multipica por dos para tener la frecuencia de interrupción a 0.5Hz

    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER0_BASE, TIMER_A, loadval - 1);

    //habilitando la interrupción del timer0
    IntEnable(INT_TIMER0A);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    TimerEnable(TIMER0_BASE, TIMER_A);

    IntRegister(INT_TIMER0A, toggle);

    //configuración UART

    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
    UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
    UART_CONFIG_PAR_NONE);

    UARTFIFOLevelSet(UART0_BASE, UART_FIFO_TX1_8, UART_FIFO_RX1_8);

    UARTEnable(UART0_BASE);
    IntEnable(INT_UART0);
    UARTIntEnable(UART0_BASE, UART_INT_RX);

// se hace que se vaya a la función especificada en la interrupción del uart
    IntRegister(INT_UART0, entradaUART);

    IntMasterEnable();

    while (1)
    {
        if (entrada == 'r')
        {
            rojo = ~rojo & GPIO_PIN_1;
            entrada = 0;
        }

        if (entrada == 'b')
        {
            azul = ~azul & GPIO_PIN_2;
            entrada = 0;
        }
        if (entrada == 'g')
        {
            verde = ~verde & GPIO_PIN_3;
            entrada = 0;
        }

    }

    return 0;
}

//esta rutina hace el toggle a 0.5hz
void toggle(void)
{


        TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
        //GPIOPinWrite tiene como parametros, puerto, pines y valor a escribir
        GPIOPinWrite(
                GPIO_PORTF_BASE,
                rojo | verde | azul,
                ~GPIOPinRead(GPIO_PORTF_BASE,
                             GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3));



}

//rutina para la entrada del UART

void entradaUART(void)
{

    UARTIntClear(UART0_BASE, UART_INT_RX);
    entrada = UARTCharGetNonBlocking(UART0_BASE);

}

