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
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, 255);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE,255);

    //se configuran los pines como entradas (para los push buttons)
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, 255);

    //se configuran las pull up
    GPIOPadConfigSet(GPIO_PORTE_BASE, 255,
    GPIO_STRENGTH_8MA,
                     GPIO_PIN_TYPE_STD_WPU);

    //GPIOPinWrite(GPIO_PORTB_BASE, 255, 255);

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

        }
        else
        {
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, 0b000);
            GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2, 0b1111);
        }

        if(parqueo2 == 0){


                   GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4, 0);
                   GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_6, 255);

               }else{
                   GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4, 255);
                   GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_6, 0);
               }


        if(parqueo3 == 0){


                     GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_7, 0);
                     GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, 255);

                 }else{
                     GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_7, 255);
                     GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_3, 0);
                 }

        if(parqueo4 == 0){


                     GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0);
                     GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0, 255);

                 }else{
                     GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 255);
                     GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_0, 0);
                 }

    }

    return 0;
}
