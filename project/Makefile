# makefile configuration
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -Os -I../h
LDFLAGS         = -L../lib -L/opt/ti/msp430_gcc/include/

# switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-gcc -mmcu=${CPU} -c

# List of common objects used in multiple programs
COMMON_OBJECTS  = ../lib/libTimer.a

# List of source files
# wdt_handler.c
SRC_FILES       = main.c game.c wdt_handler.c buzzer.c

all: wakedemo.elf

# additional rules for files
wakedemo.elf: ${COMMON_OBJECTS} ${SRC_FILES:.c=.o}
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd

load: wakedemo.elf
	msp430loader.sh $^

clean:
	rm -f *.o *.elf

