# Atmega644p uses avr-gcc. Be sure the AVR toolchain is installed
CC = avr-gcc

# Configure directories
INC = inc
OBJDIR = obj

# Source files (If you're adding extra source files be sure to add them in here)
SRC = main.c src/millis.c src/RFM69.c src/spi.c src/uart.c src/xorrand.c

# Compiler and linker flags. Note F_CPU is already defined here!
CFLAGS = -mmcu=atmega644p -Os -Wall -DF_CPU=12000000UL -I$(INC) -std=c99
LDFLAGS = -mmcu=atmega644p

# Object files helper macro
OBJ = $(SRC:%.c=$(OBJDIR)/%.o)

# Default make target when run with no arguments
all: build

# Compile source files into object files
$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files into the final executable
$(OBJDIR)/main.elf: $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $@

# Convert elf to a hex file for flashing
$(OBJDIR)/main.hex: $(OBJDIR)/main.elf
	avr-objcopy -O ihex $< $@

build: $(OBJDIR)/main.hex

# Flash the Il Matto using AVRDUDE
flash: build
	avrdude -c usbasp -p m644p -U flash:w:$(OBJDIR)/main.hex

# Clean up build artifacts
clean:
	rm -f $(OBJDIR)/*.o $(OBJDIR)/src/*.o $(OBJDIR)/main.elf $(OBJDIR)/main.hex

.PHONY: all clean build flash