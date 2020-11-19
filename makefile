#---------------------------------------------------------------------
# Flags
#---------------------------------------------------------------------
CFLAGS = -ansi -pedantic -Wall
#---------------------------------------------------------------------
# executables
#---------------------------------------------------------------------
ifeq ($(OS),Windows_NT)
	MD := mkdir
	RM := rm
	CC := gcc
	EXTENSION := .exe
else
	MD := mkdir
	RM := rm
	CC := gcc-10
	EXTENSION := .out
endif

#---------------------------------------------------------------------
# Variabels
#---------------------------------------------------------------------
build_folder = build/
program_folder = Programme/
#---------------------------------------------------------------------
# build functions
#---------------------------------------------------------------------
all:
	$(CC) $(CFLAGS) -c $(program_folder)data.c -o $(build_folder)data.o
	$(CC) $(CFLAGS) -c $(program_folder)energy.c -o $(build_folder)energy.o
	$(CC) $(CFLAGS) -c $(program_folder)user_com.c -o $(build_folder)user_com.o
	$(CC) $(CFLAGS) -c $(program_folder)localisation.c -o $(build_folder)localisation.o
	$(CC) $(CFLAGS) -c $(program_folder)main.c -o $(build_folder)main.o
	
	$(CC) $(CFLAGS) \
		$(build_folder)localisation.o \
		$(build_folder)data.o \
		$(build_folder)energy.o \
		$(build_folder)user_com.o \
		$(program_folder)main.c -o $(build_folder)main$(EXTENSION)