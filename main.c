#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>

//#include the library for the RFM69 module and the UART
#include "RFM69.h"
#include "RFM69registers.h"
#include "uart.h"
#include "millis.h"
#include "xorrand.h"

int main(void)
{
	millis_init(); // Required for RFM69
	rand_init(); // Initialise the RNG
	init_debug_uart0();
	rfm69_init(433);    //init the RFM69 
	setPowerLevel(24); //set transmit power
	setChannel(0);
	char testing[] = "Test string 1";
	while(1)
    { 
		// Your code here
    }
}
