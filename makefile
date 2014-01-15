# ***************************************************************
# *     Makefile for Atmel AT91SAM7S256 - ram execution         *
# *                                                             *
# *                                                             *
# * James P Lynch  May 12, 2007                                 *
# ***************************************************************

NAME   = at91sam7_pwm

# variables 
CC      = /Users/gshwang/yagarto/yagarto-4.7.2/bin/arm-none-eabi-gcc
LD      = /Users/gshwang/yagarto/yagarto-4.7.2/bin/arm-none-eabi-ld -v
AR      = /Users/gshwang/yagarto/yagarto-4.7.2/bin/arm-none-eabi-ar
AS      = /Users/gshwang/yagarto/yagarto-4.7.2/bin/arm-none-eabi-as
CP      = /Users/gshwang/yagarto/yagarto-4.7.2/bin/arm-none-eabi-objcopy
OD		= /Users/gshwang/yagarto/yagarto-4.7.2/bin/arm-none-eabi-objdump

CFLAGS  = -I./ -c -fno-common -O0 -g
AFLAGS  = -ahls -mapcs-32 -o crt.o

# Uncomment one of each lines to build the code for running on flash or ram memory.
LFLAGS  =  -Map main.map -T linker_script_ram.lds
//LFLAGS  =  -Map main.map -T linker_script_flash.lds

CPFLAGS = --output-target=binary
ODFLAGS	= -x --syms

OBJECTS = crt.o	main.o timerisr.o timersetup.o isrsupport.o lowlevelinit.o pwm.o


# make target called by Eclipse (Project -> Clean ...)
clean:
	-rm $(OBJECTS) crt.lst main.out main.bin main.map main.dmp

         
#make target called by Eclipse  (Project -> Build Project)
all:  main.out
	@ echo "...copying"
	$(CP) $(CPFLAGS) main.out main.bin
	$(OD) $(ODFLAGS) main.out > main.dmp

main.out: $(OBJECTS)
	@ echo "..linking"
	$(LD) $(LFLAGS) -o main.out $(OBJECTS) libgcc.a

crt.o: crt.s
	@ echo ".assembling"
	$(AS) $(AFLAGS) crt.s > crt.lst

main.o: main.c
	@ echo ".compiling"
	$(CC) $(CFLAGS) main.c
	
timerisr.o: timerisr.c
	@ echo ".compiling"
	$(CC) $(CFLAGS) timerisr.c
	
lowlevelinit.o: lowlevelinit.c
	@ echo ".compiling"
	$(CC) $(CFLAGS) lowlevelinit.c
	
timersetup.o: timersetup.c
	@ echo ".compiling"
	$(CC) $(CFLAGS) timersetup.c
	
isrsupport.o: isrsupport.c
	@ echo ".compiling"
	$(CC) $(CFLAGS) isrsupport.c
	
pwm.o: pwm.c
	@ echo ".comiling"
	$(CC) $(CFLAGS) pwm.c
	
