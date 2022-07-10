/*
 * blue.h
 *
 *  Created on: 2022Äê6ÔÂ30ÈÕ
 *      Author: 35509
 */

#ifndef BLUE_BLUE_H_
#define BLUE_BLUE_H_

#include "debug.h"

void USARTx_CFG(void);
void DMA_INIT(void);
void GPIO_CFG(void);
FlagStatus uartWriteBLE(char * data , uint16_t num);
FlagStatus uartWriteBLEstr(char * str);
uint32_t uartReadBLE(char * buffer , uint16_t num);
char uartReadByteBLE();
uint16_t uartAvailableBLE();

#endif /* BLUE_BLUE_H_ */
