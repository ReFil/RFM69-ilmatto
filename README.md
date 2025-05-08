# RFM69-ilmatto #
Original library is written for arduino by [LowPowerLab](https://github.com/LowPowerLab/RFM69). This is a C ported version for the Il Matto development board, and includes some utilies you may find useful

</br>

## I/O pin connections: ##

You should be using the breakout board supplied as part of the lab

| RF Module | Microcontroller |
| --------- | --------------- |
|MOSI |	MOSI |
| MISO | MISO |
| SCK | SCK |
| SS | SS |
| DIO0 | PCINT8 |

</br>

## Building and Flashing

Ensure the avr toolchain is installed including AVRDUDE to handle flashing

You may need to install the libusb drivers using Zadig if using a Windows host to flash the Il Matto

Note you do not need to remove the breakout board to flash the Il Matto

A makefile is provided with the repository to handle building, flashing and cleaning up build artifacts
1. Ensure `make` is installed, this can be done by running the command `make -v` which should return the current version of `make`
1. Building alone is done with `make build`
1. You can build and flash with `make flash`. Note either of the build commands will only build the changed files
1. Leftover build artifacts (stored in the /obj folder) can be removed with `make clean`

Note the make build system allows all the header files in the inc folder to be directly included in all source files.

## Function Description: ##

1.	**rfm69_init(*uint16_t freqBand*):** Initializes rfm69 module. This function is called at the beginning of the program. Initializes IDs, modes etc. It takes one parameters, freqBand. You have to choose among 315, 433, 868 and 915. These specifies frequency in MHz. 
2.	**setChannel(*uint8_t channel*):** Sets radio channel, set between 0 and 31. each channel represents a 100KHz band.
4.  **canSend():** Returns a 1 or 0 depending on if the channel is free to send data.
5.	**send(*const void\* buffer, uint8_t bufferSize*):** Transmits data to the channel. In buffer you can put any kind of buffer like string or array etc.
6.	**receiveDone():**  Returns 1 if any data is present in receive buffer.
7.	**getFrequency():** Gets frequency Band.
8.	**setFrequency(*uint32_t freqHz*):** Sets frequency band. You can set frequency other than 315, 433, 868, 915 MHz through this function. Unit is Hz i.e 433000000. 
10.	**readRSSI(*uint8_t forceTrigger=0*):** Return received signal strength indicator
11.	**setPowerLevel(*uint8_t level*):** Sets transmit power. Range 0~31.
12.	**rcCalibration():** Calibrate the internal RC oscillator for use in wide temperature variations - see datasheet section 4.3.5. RC Timer Accuracy. Not tested yet.

</br>

## Basic Operation: ##
#### Transmit data: ####

```
rfm69_init(freq)
setPowerLevel(0~31)
send(buffer, bufferLen)
```

#### Receive data: ####

```
rfm69_init(freq)
setPowerLevel(0~31)
mainloop
    if receiveDone() then
        extract received data from DATA buffer
```

## Utilities

If you wish to use the UART pins on PD0 (RX) and PD1 (TX) for debugging and communication purposes, include "uart.h" in `main.c` and be sure to call `init_debug_uart0();` at the start of your program. After that you can use [printf](https://www.geeksforgeeks.org/printf-in-c/) and [scanf](https://www.geeksforgeeks.org/scanf-in-c/) to handle input and output.

If you wish to get the system uptime in milliseconds, include "millis.h" in `main.c`. The millisecond counter is initialised by the `millis_init()` function in main.c, so no additional initialisation steps are needed. The system uptime can be returned from `millis();` as an unsigned long (uint32_t).

The "xorrand.h" header file provides a farly robust PRNG implementation, it is initialised by the `rand_init()` function using noise in the lower 4 bits of the ADC0 channel. This should not preclude the use of ADC0 for other purposes. The unsigned long random number can be returned from `get_rand()`;

## Note
The millisecond timer occupies Timer 1 on the Il matto and thus it is unavailable for your program. The RFM69 code occupies PCINT1.