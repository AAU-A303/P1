#---------------------------------------------------------------------
# Flags
#---------------------------------------------------------------------
CFLAGS = -ansi -pedantic -Wall
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
    ifeq ($(UNAME_S),Linux)
        CC := gcc
    endif
    ifeq ($(UNAME_S),Darwin)
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
target = main
dependencies = data energy localisation con_manager present user_com
obj = \
	$(build_folder)data.o \
	$(build_folder)energy.o \
	$(build_folder)localisation.o \
	$(build_folder)con_manager.o \
	$(build_folder)present.o \
	$(build_folder)user_com.o
#---------------------------------------------------------------------
# build functions
#---------------------------------------------------------------------
all: $(target)

main: $(dependencies)
	$(CC) $(CFLAGS) $(obj) $(program_folder)$@.c -o $(build_folder)$@$(EXTENSION)

$(dependencies):
	$(CC) $(CFLAGS) -c $(program_folder)$@.c -o $(build_folder)$@.o -lm

clean:	
	$(RM)
