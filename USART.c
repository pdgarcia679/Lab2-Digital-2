#include "USART.h"

void SerialBegin(uint8_t NumUSART, uint8_t ModeUSART, uint32_t BaudRate, uint8_t SpeedMode, uint8_t InterruptRX, uint8_t InterruptTX) {
	if (InterruptRX || InterruptTX)	sei();
	/*----------------------------------------------------USART0---------------------------------------------------------------------*/
	if (NumUSART == USART0) {
		DDRD &= ~(1<<DDD0);										// D0 as input RX
		UCSR0B |= (1<<RXEN0);									// Receiver enable
		DDRD |= (1<<DDD1);										// D1 as output TX
		UCSR0B |= (1<<TXEN0);									// Transmitter enable
		UCSR0A = (UCSR0A & 0xFD) | (SpeedMode);					// Transmission speed
		UCSR0B = (UCSR0B & 0x7F) | (InterruptRX<<RXCIE0);		// RX complete interrupt enable
		UCSR0B = (UCSR0B & 0xBF) | (InterruptTX<<TXCIE0);		// TX complete interrupt enable
		UCSR0C = (UCSR0C & 0x3F) | (ModeUSART);					// USART mode
		UCSR0C = (UCSR0C & 0xC0) | (1<<UCSZ01 | 1<<UCSZ00);		// Frame: no parity, 1 stop bit, 8-bit size
	
		if (SpeedMode == NormalSpeed) {
			if (ModeUSART == Synch) {
				switch (BaudRate) {
					case 9600:
					UBRR0 = 832;
					break;
					default:
					UBRR0 = 832;
					break;
				}
			}
			else if (ModeUSART == Asynch) {
				switch (BaudRate) {
					case 9600:
					UBRR0 = 103;
					break;
					default:
					UBRR0 = 103;
					break;
				}
			}
		}
		else if (SpeedMode == DoubleSpeed) {
			if (ModeUSART == Synch) {
				UCSR0A = (UCSR0A & 0xFD);						// Forces normal speed on synchronous operation
				switch (BaudRate) {
					case 9600:
					UBRR0 = 832;
					break;
					default:
					UBRR0 = 832;
					break;
				}
			}
			else if (ModeUSART == Asynch) {
				switch (BaudRate) {
					case 9600:
					UBRR0 = 207;
					break;
					default:
					UBRR0 = 207;
					break;
				}
			}
		}
	}
	/*----------------------------------------------------USART1---------------------------------------------------------------------*/
	else {
		DDRB &= ~(1<<DDB4);										// B4 as input RX
		UCSR1B |= (1<<RXEN1);									// Receiver enable
		DDRB |= (1<<DDB3);										// B3 as output TX
		UCSR1B |= (1<<TXEN1);									// Transmitter enable
		UCSR1A = (UCSR1A & 0xFD) | (SpeedMode);					// Transmission speed
		UCSR1B = (UCSR1B & 0x7F) | (InterruptRX<<RXCIE1);		// RX complete interrupt enable
		UCSR1B = (UCSR1B & 0xBF) | (InterruptTX<<TXCIE1);		// TX complete interrupt enable
		UCSR1C = (UCSR1C & 0x3F) | (ModeUSART);					// USART mode
		UCSR1C = (UCSR1C & 0xC0) | (1<<UCSZ11 | 1<<UCSZ10);		// Frame: no parity, 1 stop bit, 8-bit size
		
		if (SpeedMode == NormalSpeed) {
			if (ModeUSART == Synch) {
				switch (BaudRate) {
					case 9600:
					UBRR1 = 832;
					break;
					default:
					UBRR1 = 832;
					break;
				}
			}
			else if (ModeUSART == Asynch) {
				switch (BaudRate) {
					case 9600:
					UBRR1 = 103;
					break;
					default:
					UBRR1 = 103;
					break;
				}
			}
		}
		else if (SpeedMode == DoubleSpeed) {
			if (ModeUSART == Synch) {
				UCSR1A = (UCSR1A & 0xFD);						// Forces normal speed on synchronous operation
				switch (BaudRate) {
					case 9600:
					UBRR1 = 832;
					break;
					default:
					UBRR1 = 832;
					break;
				}
			}
			else if (ModeUSART == Asynch) {
				switch (BaudRate) {
					case 9600:
					UBRR1 = 207;
					break;
					default:
					UBRR1 = 207;
					break;
				}
			}
		}
	}
}

void SerialWriteText(uint8_t NumUSART, char* TextToTransmit) {
	if (NumUSART == USART0) {
		if (TextToTransmit == NULL) return;
		for (uint8_t i = 0; TextToTransmit[i] != '\0'; i++) {
			while (!(UCSR0A & (1<<UDRE0)));
			UDR0 = TextToTransmit[i];
		}
	}
	else {
		if (TextToTransmit == NULL) return;
		for (uint8_t i = 0; TextToTransmit[i] != '\0'; i++) {
			while (!(UCSR1A & (1<<UDRE1)));
			UDR1 = TextToTransmit[i];
		}
	}
}

char* IntToString(int IntToConvert) {
	int ConvertedLength = snprintf(NULL, 0, "%d", IntToConvert) + 1;
	char* IntConverted = malloc(ConvertedLength);
	if (IntConverted == NULL) return NULL;
	sprintf(IntConverted, "%d", IntToConvert);
	return IntConverted;
}

void SerialWriteFloat(uint8_t NumUSART, float Variable, uint8_t NumDecimal) {
	int Variable_int = (int)(Variable);
	int Variable_dec = (int)((Variable - Variable_int) * pow(10, NumDecimal));
	SerialWriteText(NumUSART, IntToString(Variable_int));
	SerialWriteText(NumUSART, ".");
	SerialWriteText(NumUSART, IntToString(Variable_dec));
}
