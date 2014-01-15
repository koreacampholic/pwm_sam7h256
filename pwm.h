/*
 * pwm.h
 *
 *  Created on: 2014. 1. 15.
 *      Author: gshwang
 */

#ifndef PWM_H_
#define PWM_H_



//PWM 허용레지스터
#define PWMC 10
#define PWM1 12 //PA12

//PWM_MR
#define PREA 8
#define PREB 24
#define DIVA 0
#define DIVB 16

//PWM_CMRx(PWM3)
#define CPRE 0 //분주비
#define CALG 8 //톱니파, 삼각파설정
#define CPOL 9 // H/L 설정
#define CPD 10 // 듀티, 주기수정

//PWM_CDTYx
#define CDTY 0
#define CPRD 0
#define CHID 3

#define LED (1 << 20)

void PWM3_init(void);
void PWM3_duty(unsigned uiDuty);

#endif /* PWM_H_ */
