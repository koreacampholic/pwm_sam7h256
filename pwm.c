/*
 * pwm.c
 *
 *  Created on: 2014. 1. 15.
 *      Author: gshwang
 */

#include "at91sam7s256.h"
#include "pwm.h"

void
PWM3_init(void)
{
    volatile AT91PS_PMC pPMC = AT91C_BASE_PMC;
    pPMC->PMC_PCER = (1 << PWMC) | (1 << 12); //주변장치 클록 허용 레지스터(1<<10, PWMC[PID10]

    volatile AT91PS_PIO pPIO = AT91C_BASE_PIOB;
    pPIO->PIO_PPUDR = (1 << PWM1); //풀업저항 off
    pPIO->PIO_BSR = (1 << PWM1); //Peripheral B mode
    pPIO->PIO_PDR = (1 << PWM1); //해당핀을 병렬I/O사용 금지

    volatile AT91PS_PWMC pPWMC = AT91C_BASE_PWMC;
    //48,000,000Hz / 8 / 30 = 200,000HZ => 200KHz
    pPWMC->PWMC_MR = (3 << PREB) | (3 << PREA) | (30 << DIVA) | (30 << DIVB);

    volatile AT91PS_PWMC_CH pPWMCH = AT91C_BASE_PWMC_CH1;
    //CPD(duty),CPOL(H),CALG(single),CPRE(CLKA)
    pPWMCH->PWMC_CMR = ((0 << CPD) | (1 << CPOL) | (0 << CALG) | (11 << CPRE));

    pPWMCH->PWMC_CDTYR = 100;
    pPWMCH->PWMC_CPRDR = 800;

    pPWMC->PWMC_ENA = (1 << CHID); //use chanel 3

}

void
PWM3_dutyset(unsigned int uiDuty) //듀티비로 LED조절
{
    if (800 < uiDuty)
        {
            uiDuty = 800;
        }

    volatile AT91PS_PWMC_CH pPWMCH = AT91C_BASE_PWMC_CH1;
    pPWMCH->PWMC_CUPDR = uiDuty;
}
