#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>

//#include the library for the RFM69 module and the UART
#include "RFM69.h"
#include "RFM69registers.h"
#include "uart.h"
#include "millis.h"

#define NODEID    1 //Modify this value, 0-255
#define MASTERID  2


int main(void)
{
	millis_init(); // Required for RFM69
	init_debug_uart0();
	rfm69_init(433, NODEID);    //init the RFM69 
	setPowerLevel(25); //set to maximum transmit power
	promiscuous(1); //Receive from anyone on the network
	char testing[] = "Test string";
	while(1)
   { 
	if((!(millis()%1000)) && canSend())
		{
		send(MASTERID, (const void*)&testing, sizeof(testing));
		printf("Sending\n");
		}
	if(receiveDone())
		printf("Received %s\n", DATA);
   }
}
