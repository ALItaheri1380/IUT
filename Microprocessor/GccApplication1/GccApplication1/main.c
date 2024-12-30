#include <avr/io.h>
#include <util/delay.h>

#define MAX_SENSORS 4
#define F_CPU 16000000UL

int segment_digits[] = {
	0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F
};

void ADC_init() {
	ADMUX = (1 << REFS0) | (1 << REFS1); 
	ADCSRA = (1 << ADEN) | (1 << ADATE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); 
}

int ADC_read(int channel) {
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F); 
	ADCSRA |= (1 << ADSC); 
	while (ADCSRA & (1 << ADSC)); 
	return ADC; 
}

void display_on_segment(int digit, int position) {
	if (position == 0) {
		PORTD = segment_digits[digit];
		} else if (position == 1) {
		PORTC = segment_digits[digit];
	}
}

int main(void) {
	int sensor_values[MAX_SENSORS];
	int max_temp = 0;
	int i, max_digit_ones, max_digit_tens;

	DDRC = 0xFF;  
	DDRD = 0xFF;  
	DDRA = 0x00;  

	ADC_init();

	while (1) {

		
		
		for (i = 0; i < MAX_SENSORS; i++) {
			sensor_values[i] = ADC_read(i + 1); 
		}

		
		max_temp = sensor_values[0];
		for (i = 1; i < MAX_SENSORS; i++) {
			if (sensor_values[i] > max_temp) {
				max_temp = sensor_values[i];
			}
		}

		
		int temperature = (max_temp * 2.56 * 100) / 1024 ; 
		

		max_digit_ones = temperature % 10;
		max_digit_tens = temperature / 10;

		
		display_on_segment(max_digit_ones, 0);  
		display_on_segment(max_digit_tens, 1);  

		_delay_ms(10);  
	}

	return 0;
}