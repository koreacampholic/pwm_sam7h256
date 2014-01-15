#include "at91sam7s256.h"
#include "board.h"

extern void
LowLevelInit(void);
extern void
PWM3_init(void);

int
main(void)
{
    /* Initialize the Atmel AT91SAM7S256 (watchdog, PLL clock, default
     interrupts, etc.) */
    LowLevelInit();

    PWM3_init();

    /* Set up the LED PA20 */
    volatile AT91PS_PIO pPIO = AT91C_BASE_PIOA;
    /* PIO Enable Register - allow PIO to control pins PA20 */
    pPIO->PIO_PER = LED;
    /* PIO Output Enable Register - sets pins PA20 */
    pPIO->PIO_OER = LED;
    /* PIO Set Output Data Register - turns on the LED */
    pPIO->PIO_SODR = LED;

    int j;
    while (1)
        {
            if ((pPIO->PIO_ODSR & LED) != LED)
                {    // read previous state of LED
                    pPIO->PIO_SODR = LED;                  // turn LED1 (DS1) on

                }
            else
                {
                    pPIO->PIO_CODR = LED;                 // turn LED1 (DS1) off
                }

            for (j = 1000000; j != 0; j--)
                ;                // wait 1 second 1000000

        }
}
