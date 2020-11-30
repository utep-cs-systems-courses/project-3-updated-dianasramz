# makfile configuration
COMMON_OBJECTS  = 
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h
LDFLAGS		= -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: main.elf 

#additional rules for files
main.elf: ${COMMON_OBJECTS} ToyMain.o  buzzer.o p2_interrupt_handler.o led.o switches.o stateMachines.o wdInterruptHandler.o ../lib/libTimer.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

load: main.elf
	msp430loader.sh main.elf

clean:
	rm -f *.o *.elf

ToyMain.o: ToyMain.c

led.o: led.c led.h

buzzer.o: buzzer.c buzzer.h

switches.o: switches.c switches.h

stateMachines.o: stateMachines.c stateMachines.h

p2_interrupt_handler.o: p2_interrupt_handler.c

wdInterrupt_Handler.o: wdInterrupt_Handler.c buzzer.h led.h switches.h stateMachines.h
