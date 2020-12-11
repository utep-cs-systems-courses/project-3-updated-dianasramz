# makfile configuration
COMMON_OBJECTS  = 
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h
LDFLAGS		= -L../lib -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS		= msp430-elf-gcc -mmcu=${CPU} -c
AR		= msp430-elf-ar

OBJECTS 	= p2switches.o

libp2sw.a: $(OBJECTS)
	$(AR) crs $@ $^

$(OBJECTS): p2switches.h

all: main.elf 

#additional rules for files
main.elf: ${COMMON_OBJECTS} ToyMain.o  buzzer.o p2switches.o led.o stateMachines.o wdt_handler.o dim_red_state.o libp2sw.a ../lib/libTimer.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd -L../lib

load: main.elf
	msp430loader.sh main.elf

clean:
	rm -f *.o *.elf *~ *# *.a




