#include <avr/io.h>
#include <util/delay.h>
const uint8_t digits[10] = {
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

void init_ports() {
	DDRB = 0xFF;
	DDRC = 0xFF;
	PORTB = 0x00;
	PORTC = 0x00;
}
int main(void) {
	init_ports();
	while (1) {
		for (uint8_t i = 0; i <= 9; i++) {
			PORTC = digits[i];
			for (uint8_t i = 0; i <= 9; i++){
				PORTB = digits[i];
				_delay_ms(500);
			}
		}
	}
	return 0;
}

