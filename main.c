#include <avr/io.h>
#include <avr/interrupt.h>
#include "LiquidCrystal_1602A/LiquidCrystal_1602A.h"
#include "USART/USART.h"
#include "ADC/ADC.h"

ISR(USART1_RX_vect);

volatile char character_RX1;

uint8_t Counter = 0;
uint8_t UpdateCounter = 0;
float	Voltage_Sensor1_Now = 0;
float	Voltage_Sensor2_Now = 0;
float	Voltage_Sensor1_Prev = 0;
float	Voltage_Sensor2_Prev = 0;

int main(void)
{	
	SerialBegin(USART1, Asynch, 9600, NormalSpeed, True, False);
	SettingADC(AVcc, LeftJustified, ADC_Prescaler128, FreeRunning);
	lcd_begin(D9, D8, D0, D1, D2, D3, D4, D5, D6, D7);
	lcd_setcursor(1, 2);
	lcd_print("S1:");
	lcd_setcursor(1, 8);
	lcd_print("S2:");
	lcd_setcursor(1, 13);
	lcd_print("S3:");
	
	lcd_setcursor(2, 13);
	lcd_print("   ");
	lcd_setcursor(2, 13);
	lcd_print(IntToString(Counter));
	
	SerialWriteText(USART1,"Inicio\n");
	
    while (1) 
    {	
		if (UpdateCounter) {
			UpdateCounter = 0;
			lcd_setcursor(2, 13);
			lcd_print("   ");
			lcd_setcursor(2, 13);
			lcd_print(IntToString(Counter));
		}
		if (Voltage_Sensor1_Now != Voltage_Sensor1_Prev) {
			Voltage_Sensor1_Prev = Voltage_Sensor1_Now;
			lcd_setcursor(2, 1);
			lcd_print("     ");
			lcd_setcursor(2, 1);
			lcd_print_float(Voltage_Sensor1_Now, 2);
			lcd_print("V");
		}
		if (Voltage_Sensor2_Now != Voltage_Sensor2_Prev) {
			Voltage_Sensor2_Prev = Voltage_Sensor2_Now;
			lcd_setcursor(2, 7);
			lcd_print("     ");
			lcd_setcursor(2, 7);
			lcd_print_float(Voltage_Sensor2_Now, 2);
			lcd_print("V");
		}
		Voltage_Sensor1_Now = ((AnalogRead(ChannelADC0)*Voltage_AVcc)/255);
		Voltage_Sensor2_Now = ((AnalogRead(ChannelADC1)*Voltage_AVcc)/255);
    }
}

ISR(USART1_RX_vect) {
	character_RX1 = UDR1;
	if (character_RX1 == '\r' || character_RX1 == '\n') return;
	if (character_RX1 >= 32 && character_RX1 <= 126) UpdateCounter = 1;
	if (character_RX1 == '+') Counter++;
	if (character_RX1 == '-') Counter--;
}
