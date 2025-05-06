// **********************************************************************************
// Driver definition for HopeRF RFM69W/RFM69HW/RFM69CW/RFM69HCW, Semtech SX1231/1231H
// **********************************************************************************
// Copyright Felix Rusu 2016, http://www.LowPowerLab.com/contact
// **********************************************************************************
// License
// **********************************************************************************
// This program is free software; you can redistribute it 
// and/or modify it under the terms of the GNU General    
// Public License as published by the Free Software       
// Foundation; either version 3 of the License, or        
// (at your option) any later version.                    
//                                                        
// This program is distributed in the hope that it will   
// be useful, but WITHOUT ANY WARRANTY; without even the  
// implied warranty of MERCHANTABILITY or FITNESS FOR A   
// PARTICULAR PURPOSE. See the GNU General Public        
// License for more details.                              
//                                                        
// Licence can be viewed at                               
// http://www.gnu.org/licenses/gpl-3.0.txt
//
// Please maintain this license information along with authorship
// and copyright notices in any redistribution of this code
// **********************************************************************************


// **********************************************************************************
// Converted to AVR environment by Zulkar Nayem
// Modified by Willow Herring
// **********************************************************************************

#include <avr/io.h>

#ifndef RFM69_H
#define RFM69_H

// Pin definitions for the ELEC3227 Breakout board
#define SS_PORT              PORTB
#define SS_PIN                 PB4

#define INT_DDR               DDRB
#define SS_DDR                DDRB
#define INT_PORT             PORTB
#define INT_PIN               PINB

// If using legacy EXT interrupt
//#define INT_pin_num              2
//#define INT_PIN_n              PB2
//#define EXTERNAL_INTERRUPT
//#define INTn                  INT2
//#define ISCn0                ISC20
//#define ISCn1                ISC21
//#define INT_VECT         INT2_vect
//
//#define EICRn               EICRA

#define INT_pin_num              0
#define INT_PIN_n              PB0
#define PIN_CHANGE_INTERRUPT
#define PCINTn PCINT8
#define PCMSKn PCMSK1
#define PCIEn PCIE1
#define INT_VECT         PCINT1_vect



#define RF69_MAX_DATA_LEN       61  // we want to limit the frame size to the internal FIFO size (66 bytes - 3 bytes overhead - 2 bytes crc)
#define CSMA_LIMIT             -90 // upper RX signal sensitivity threshold in dBm for carrier sense access
#define RF69_MODE_SLEEP         0   // XTAL OFF
#define RF69_MODE_STANDBY       1   // XTAL ON
#define RF69_MODE_SYNTH         2   // PLL ON
#define RF69_MODE_RX            3   // RX MODE
#define RF69_MODE_TX            4   // TX MODE
#define null                  0
#define COURSE_TEMP_COEF    -90     // puts the temperature reading in the ballpark, user can fine tune the returned value
#define RF69_BROADCAST_ADDR   0
#define RF69_CSMA_LIMIT_MS 1000
#define RF69_TX_LIMIT_MS   1000
#define RF69_FSTEP    61.03515625   // == FXOSC / 2^19 = 32MHz / 2^19 (p13 in datasheet) / FXOSC = module crystal oscillator frequency 

// Global Variables
extern volatile uint8_t DATA[RF69_MAX_DATA_LEN+1];  // RX/TX payload buffer, including end of string NULL char

// Function Declerations
void rfm69_init(uint16_t freqBand);
void setAddress(uint8_t addr);
uint8_t canSend();
void send( const void* buffer, uint8_t bufferSize);
void receiveBegin();
uint8_t receiveDone();
uint32_t getFrequency();
void setFrequency(uint32_t freqHz);
int16_t readRSSI(uint8_t forceTrigger);
void setPowerLevel(uint8_t level);            // reduce/increase transmit power level
void sleep();
void rcCalibration();                         // calibrate the internal RC oscillator for use in wide temperature variations - see datasheet section [4.3.5. RC Timer Accuracy]
uint8_t readReg(uint8_t addr);
void writeReg(uint8_t addr, uint8_t val);
void sendFrame(const void* buffer, uint8_t size);
void setMode(uint8_t mode);
void setHighPowerRegs(uint8_t onOff);
void maybeInterrupts();
void select();
void unselect();
uint8_t receiveDone();

#endif

