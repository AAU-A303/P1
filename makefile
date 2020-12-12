#---------------------------------------------------------------------
# Flags
#---------------------------------------------------------------------
CFLAGS = -ansi -pedantic -Wall -O3
#---------------------------------------------------------------------
# executables
#---------------------------------------------------------------------
ifeq ($(OS),Windows_NT)
	MD := mkdir
	RM := del /Q /S *.o
	CC := gcc
	EXTENSION := .exe
else
	UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S), Linux)
        CC := gcc
    endif
    ifeq ($(UNAME_S), Darwin)
        CC := gcc-10
    endif
	MD := mkdir
	RM := rm -f *.o
	EXTENSION := .out
endif
#---------------------------------------------------------------------
# Variabels
#---------------------------------------------------------------------
build_folder = Build/
program_folder = Programme/
libary_folder = Programme/libaries/
target = main
dependencies = data energy localisation present user_com
obj = \
	$(build_folder)data.o \
	$(build_folder)energy.o \
	$(build_folder)localisation.o \
	$(build_folder)present.o \
	$(build_folder)user_com.o
#---------------------------------------------------------------------
# build functions
#---------------------------------------------------------------------
all: $(target)

main: $(dependencies) strings
	$(CC) $(CFLAGS) $(build_folder)strings.o $(obj) $(program_folder)$@.c -o $(build_folder)$@$(EXTENSION)

cutest: $(dependencies) CuTest strings
	$(CC) $(CFLAGS) $(build_folder)CuTest.o $(build_folder)strings.o $(obj) $(program_folder)$@.c -o $(build_folder)$@$(EXTENSION)

$(dependencies):
	$(CC) $(CFLAGS) -c $(program_folder)$@.c -o $(build_folder)$@.o -lm

strings:
	$(CC) $(CFLAGS) -c $(libary_folder)$@.c -o $(build_folder)$@.o -lm

CuTest:
	$(CC) $(CFLAGS) -c $(libary_folder)$@.c -o $(build_folder)$@.o

clean:	
	$(RM)
