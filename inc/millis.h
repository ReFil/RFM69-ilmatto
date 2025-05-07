// Source: https://gist.github.com/adnbr/2439125#file-counting-millis-c

#ifndef MILLIS_H
#define MILLIS_H

/// @brief Initialise the millisecond timer, execute at the beginning of the program to keep count of milliseconds since start
void millis_init();


/// @brief Gets the current number of milliseconds since it got initialised
/// @return Number of milliseconds since millis_init();
unsigned long millis();

#endif
