/*
 * timer.h
 *
 *  Created on: Jul 18, 2024
 *      Author: admin
 */

#ifndef TIMER_H_
#define TIMER_H_

//================ INCLUDE ================/
#include "stdint.h"
#include "MKL46Z4.h"
//================ DEFINED ================/
#define PIT_TIMER PIT_TIMER0
//typedef interrupt function

//================ SUPPORT ================/

//================ FOCUSED ================/
void TIMER_Init();

void TIMER_WAIT_Sync(uint16_t timeMs);
void TIMER_WAIT_();

void TIMER_COUNTDOWN_Async(uint16_t timeMs);
void TIMER_COUNTDOWN_Async_Start();
void TIMER_COUNTDOWN_Async_Stop();

#endif /* TIMER_H_ */
