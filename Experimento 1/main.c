//*****************************************************************************
//
// EXPERIMENTO 1
// Noel Prado 19025
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

void semaforo();

int main(void)
{


    volatile uint32_t ui32Loop; //variable para el delay

    //configuración del reloj
    //determinar la frecuencia, porque solo se copio del ejemplo

    SysCtlClockSet(
    SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);

    //configuración del reloj para habilitarlo como puerto F
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
    {
    }

    //se configuran los pines como salidas
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,
    GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);

    //se configura el boton
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_8MA,
    GPIO_PIN_TYPE_STD_WPU);
    int32_t boton1 = 16;
    int32_t boton2 = 16;

    // Loop forever.

    while (1)
    {

        // Delay for a bit.

        boton1 = boton2;
        boton2 = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4);

        if (boton1 == 0 && boton2 == 16)
        {
              semaforo();
        }

    }
}

void semaforo()
{

    //Cuando LED vale 2, es rojo
    //Cuando LED vale 4, es azul
    //Cuando LED, vale 8, es verde
    //ya no se usa led, pero aplica lo mismo para el último parámetro de la función

    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 8);

    // esta es la función para usar delay, el parámetro es el número de ciclos que se quiere que se ejecute
    SysCtlDelay(7900000);
    int i = 0;
    for (i = 0; i < 3; i++)
    {
        //se usa el for para el efecto de oscilar
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 0);
        SysCtlDelay(1900000);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 8);
        SysCtlDelay(1900000);

    }


    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 10);    //verde y rojo
    SysCtlDelay(7900000);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 2);    //rojo
    SysCtlDelay(7900000);


}
//este es el delay que se uso antes, el hecho a mano
//se sustituyo por la función

void delay()
{
    uint32_t ui32Loop = 0;
    for (ui32Loop = 0; ui32Loop < 2000000; ui32Loop++)
    {
        //delay
    }
}
