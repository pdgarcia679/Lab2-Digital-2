#ifndef USART_H_
#define USART_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NormalSpeed		0
#define DoubleSpeed		(1<<U2X0)					// (1<<U2X1)
#define Asynch			0
#define Synch			(1<<UMSEL00)				// (1<<UMSEL10)
#define MasterSPI		(1<<UMSEL01 | 1<<UMSEL00)	// (1<<UMSEL11 | 1<<UMSEL10)
#define False			0
#define True			1
#define USART0			0
#define USART1			1

void SerialBegin(uint8_t NumUSART, uint8_t ModeUSART, uint32_t BaudRate, uint8_t SpeedMode, uint8_t InterruptRX, uint8_t InterruptTX);
void SerialWriteText(uint8_t NumUSART, char* TextToTransmit);
char* IntToString(int IntToConvert);
void SerialWriteFloat(uint8_t NumUSART, float Variable, uint8_t NumDecimal);

#endif