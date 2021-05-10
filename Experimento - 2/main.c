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

uint32_t loadval;

void toggle(void);

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
    loadval = SysCtlClockGet(); // un segundo


    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER0_BASE, TIMER_A, loadval-1);

    //habilitando la interrupción del timer0
    IntEnable(INT_TIMER0A);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);


    TimerEnable(TIMER0_BASE, TIMER_A);

    IntRegister(INT_TIMER0A, toggle);

    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 , 2);

    while(1){

    }





    return 0;
}

void toggle(void){
        TimerIntClear(TIMER0_BASE,TIMER_TIMA_TIMEOUT);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 , ~GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_1));
}



