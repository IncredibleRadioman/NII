/*
 * Utilities.h
 *
 *  Created on: 24 янв. 2018 г.
 *      Author: User
 */

#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <stdint.h>
#include "stm32l1xx_conf.h"
#include "stdlib.h"


#define    DWT_CYCCNT    *(volatile unsigned long *)0xE0001004
#define    DWT_CONTROL   *(volatile unsigned long *)0xE0001000
#define    SCB_DEMCR     *(volatile unsigned long *)0xE000EDFC


//-------------------- таймер

void DWT_Init(void);
//static __inline uint32_t delta(uint32_t t0, uint32_t t1);
void delay_us(uint32_t us);
void delay_ms(uint32_t ms);
//-------------------- преобразование типов


#endif /* UTILITIES_H_ */
