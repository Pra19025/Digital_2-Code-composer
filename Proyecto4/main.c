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

int main(void)
{
    //configuración del reloj
    // a 40Mhz
    SysCtlClockSet(
    SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);

    //se configuran los pines como salidas (para los leds)
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinTypeGPIOOutput(
            GPIO_PORTA_BASE,
            GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4
                    | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);

    //se configuran los pines como entradas (para los push buttons)
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    GPIOPinTypeGPIOInput(GPIO_PORTE_BASE,
                         255);

    //se configuran las pull up
    GPIOPadConfigSet(GPIO_PORTE_BASE,
                     255,
                     GPIO_STRENGTH_8MA,
                     GPIO_PIN_TYPE_STD_WPU);

    //GPIOPinWrite(GPIO_PORTA_BASE, 0b1100, 0b1100);


    int32_t boton1 = 16;
    int32_t boton2 = 16;


    //Loop forever
    while(1){

        SysCtlDelay(1000);
        //escritura de prueba
        GPIOPinWrite(GPIO_PORTA_BASE, 0b0100, 0b1111);
        boton1 = boton2;
        boton2 = GPIOPinRead(GPIO_PORTE_BASE, 0b1111);

        if(boton1 == 0 && boton2 == 16){
            //escritura de prueba
                  GPIOPinWrite(GPIO_PORTA_BASE, 0b0000, 0b1111);
            GPIOPinWrite(GPIO_PORTA_BASE, 0b1111, 0b1111);
        }


    }

    return 0;
}
