MCU = atmega328p
F_CPU = 16000000UL
CC = avr-gcc
OBJCOPY = avr-objcopy
SIZE = avr-size

CFLAGS = -Wall -Wextra -Os -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Iinclude -Isrc
LDFLAGS = -mmcu=$(MCU)

SRC = $(wildcard src/*.c) \
      $(wildcard src/system/*.c) \
      $(wildcard src/drivers/*.c) \
      $(wildcard src/devices/*.c) \
      $(wildcard src/sensors/*.c) \
      $(wildcard src/communication/*.c) \
      $(wildcard src/application/*.c)

OBJ = $(SRC:.c=.o)
TARGET = water_meter

all: $(TARGET).hex

$(TARGET).elf: $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^
	$(SIZE) -A $@

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	-$(RM) $(OBJ) $(TARGET).elf $(TARGET).hex

.PHONY: all clean
