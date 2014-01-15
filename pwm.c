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
    AT91C_PMC_PCER = (1 << PWMC); //주변장치 클록 허용 레지스터(1<<10, PWMC[PID10]

    AT91C_PIOB_PPUDR = (1 << PWM3); //풀업저항 off
    AT91C_PIOB_BSR = (1 << PWM3); //Peripheral B mode
    AT91C_PIOB_PDR = (1 << PWM3); //해당핀을 병렬I/O사용 금지

    //48,000,000Hz / 8 / 30 = 200,000HZ => 200KHz
    AT91C_PWMC_MR = (3 << PREB) | (3 << PREA) | (30 << DIVA) | (30 << DIVB);

    //CPD(duty),CPOL(H),CALG(single),CPRE(CLKA)
    AT91C_PWMC_CH3_CMR = (0 << CPD) | (1 << CPOL) | (0 << CALG) | (11 << CPRE);

    AT91C_PWMC_CH3_CDTYR = 100;
    AT91C_PWMC_CH3_CPRDR = 800;

    AT91C_PWMC_ENA = (1 << CHID); //use chanel3

}

