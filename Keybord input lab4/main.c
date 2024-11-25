#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

const uint8_t segment_display[10] = {
	0b00111111,
	0b00000110,
	0b01011011,
	0b01001111,
	0b01100110,
	0b01101101,
	0b01111101,
	0b00000111,
	0b01111111,
	0b01101111
};


const uint8_t keypad_mapping[4][3] = {
	{1, 2, 3},
	{4, 5, 6},
	{7, 8, 9},
	{0, 0, 0}
};

void init_peripherals() {
	DDRB = 0xFF;
	PORTB = 0x00;

	DDRD = 0xFF;
	PORTD = 0x00;

	DDRC = 0x0F;
	PORTC = 0xF0;
}

uint8_t read_keypad() {
	for (uint8_t row = 0; row < 4; row++) {
		PORTC = ~(1 << row);
		for (uint8_t col = 0; col < 3; col++) {
			if (!(PINC & (1 << (col + 4)))) {
				_delay_ms(50);
				if (!(PINC & (1 << (col + 4)))) {
					return keypad_mapping[row][col];
				}
			}
		}
	}
	return 0xFF;
}

void display_number(uint8_t number) {
	if (number < 10) {
		PORTB = segment_display[number];
		PORTD = 0x00;
		} else {
		uint8_t tens = number / 10;
		uint8_t ones = number % 10;

		PORTD = segment_display[tens];
		PORTB = segment_display[ones];
	}
}

int main() {
	init_peripherals();

	uint8_t number = 0;

	while (1) {
		uint8_t key = read_keypad();
		if (key != 0xFF) {
			number = (number * 10 + key) % 100;
			_delay_ms(200);
		}
		display_number(number);
	}
}
