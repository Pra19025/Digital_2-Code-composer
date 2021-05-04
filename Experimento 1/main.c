//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

//*****************************************************************************
//
// EXPERIMENTO 1
// Noel Prado 19025
//
//*****************************************************************************

int main(void)
{
    uint8_t LED = 8;
    uint8_t control = 0;

    volatile uint32_t ui32Loop; //variable para el delay

    //configuración del reloj
    //determinar la frecuencia, porque solo se copio del ejemplo

    SysCtlClockSet(
    SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);

    //configuración del reloj para habilitarlo como puerto F
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    // Check if the peripheral access is enabled.

    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
    {
    }

    // Enable the GPIO pin for the LED (PF2).  Set the direction as output, and
    // enable the GPIO pin for digital function.

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,
    GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);

    // Loop forever.

    while (1)
    {

        // Turn on the LED.

        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3,
                     LED);

        // Delay for a bit.

        for (ui32Loop = 0; ui32Loop < 2000000; ui32Loop++)
        {

        }

        //Cuando LED vale 2, es rojo
        //Cuando LED vale 4, es azul
        //Cuando LED, vale 8, es verde

        if (LED == 8)
        {
            LED = 10;   //deberia ser amarillo
        }

        if (control == 1)
        {
            LED = 2;
            control = 0;
        }

        control = 1;

    }
}
