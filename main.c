#include "at91sam7s256.h"
#include "board.h"

void
Timer0IrqHandler(void);
extern void
LowLevelInit(void);
extern void
TimerSetup(void);
extern unsigned
enableIRQ(void);
extern unsigned
enableFIQ(void);

int
main(void)
{
    /* Initialize the Atmel AT91SAM7S256 (watchdog, PLL clock, default
     interrupts, etc.) */
    LowLevelInit();

    /* Enable the Timer0 peripheral clock */
    /* pointer to PMC data structure */
    volatile AT91PS_PMC pPMC = AT91C_BASE_PMC;
    /* enable Timer0 peripheral clock */
    pPMC->PMC_PCER = (1 << AT91C_ID_TC0);

    /* Set up the LED PA20 */
    volatile AT91PS_PIO pPIO = AT91C_BASE_PIOA;
    /* PIO Enable Register - allow PIO to control pins PA20 */
    pPIO->PIO_PER = LED;
    /* PIO Output Enable Register - sets pins PA20 */
    pPIO->PIO_OER = LED;
    /* PIO Set Output Data Register - turns off the LED */
    pPIO->PIO_SODR = LED;

    /* Set up the AIC  registers for Timer 0 */
    /* pointer to AIC data structure */
    volatile AT91PS_AIC pAIC = AT91C_BASE_AIC;
    /* disable timer 0 interrupt in AIC Interrupt Disable Command Register */
    pAIC->AIC_IDCR = (1 << AT91C_ID_TC0);
    /* Set the TC0 IRQ handler address in AIC Source */
    pAIC->AIC_SVR[AT91C_ID_TC0] = (unsigned int) Timer0IrqHandler;
    /* Set the interrupt source type and priority */
    pAIC->AIC_SMR[AT91C_ID_TC0] = (AT91C_AIC_SRCTYPE_INT_HIGH_LEVEL | 0x4);
    /* Clear the TC0 interrupt in AIC Interrupt Clear Command Register */
    pAIC->AIC_ICCR = (1 << AT91C_ID_TC0);
    /* Disable timer 0 interrupt in AIC Interrupt Disable Command Reg */
    pAIC->AIC_IDCR = (0 << AT91C_ID_TC0);
    /* Enable the TC0 interrupt in AIC Interrupt Enable Command Register */
    pAIC->AIC_IECR = (1 << AT91C_ID_TC0);

    /* Setup timer0 to generate a 1 sec periodic interrupt */
    TimerSetup();

    /* Enable interrupts */
    enableIRQ();

    unsigned long j;

    /* Endless blink loop */
    while (1)
        {
            if ((pPIO->PIO_ODSR & LED) == LED)    // read previous state of LED1
                pPIO->PIO_CODR = LED;                      // turn LED1 (DS1) on
            else
                pPIO->PIO_SODR = LED;                     // turn LED1 (DS1) off

            for (j = 1000000; j != 0; j--);                // wait 1 second 1000000


        }
}
