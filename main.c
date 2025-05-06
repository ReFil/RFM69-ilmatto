#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>

//#include the library for the RFM69 module and the UART
#include "RFM69.h"
#include "RFM69registers.h"
#include "uart.h"
#include "millis.h"

int main(void)
{
	millis_init(); // Required for RFM69
	init_debug_uart0();
	rfm69_init(433);    //init the RFM69 
	setPowerLevel(25); //set transmit power
	char testing[] = "Test string";
	while(1)
   { 
	if((!(millis()%1000)) && canSend())
		{
		send((const void*)&testing, sizeof(testing));
		printf("Sending\n");
		}
	if(receiveDone())
		printf("Received %s\n", DATA);
   }
}
