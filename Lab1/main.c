#include <avr/io.h>
#include <util/delay.h>
int main(void)
{
	DDRC = 0xFF;
	PORTC = 0xFF;
}

