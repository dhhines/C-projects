#-----------------------------------------------------------------------------------#
# Makefile for 'reading' program                                                    #
# Variables created for compiler and standard flags                                 #
# Also created variables for the separate directories to keep build location clean  #
#                                                                                   #
# Targets:                                                                          #
# all: builds all target programs in /                                              #
# reading: builds reading build objects in /                                        #
# catalog: builds catalog objects in /                                              #
# input: builds text objects in /                                                   #
# clean: removes all objects, program and temporary files                           #
#                                                                                   #
# @author:  David Hines                                                             #
#-----------------------------------------------------------------------------------#

CC = gcc
CFLAGS = -Wall -std=c99 -g
SRC_DIR = ./
BUILD_DIR = ./
BIN_DIR = ./
SRC_LIST = $(wildcard $(SRC_DIR)*.c)
READ_OBJ_LIST = $(BUILD_DIR)reading.o $(BUILD_DIR)catalog.o $(BUILD_DIR)input.o
CAT_OBJ_LIST = $(BUILD_DIR)catalog.o
IN_OBJ_LIST = $(BUILD_DIR)input.o
PROGRAM = $(wildcard $(BIN_DIR)*.exe)
TEMP_FILES = $(wildcard $(BIN_DIR)output*.txt) $(BIN_DIR)stderr.txt $(BIN_DIR)stdout.txt

# reading program target
reading: reading.o catalog.o input.o
	$(CC) $(CFLAGS) $(READ_OBJ_LIST) -o $(BIN_DIR)reading

# object file targets
reading.o: $(SRC_DIR)reading.c $(SRC_DIR)catalog.h $(SRC_DIR)input.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)reading.c -o $(BUILD_DIR)reading.o

catalog.o: $(SRC_DIR)catalog.c $(SRC_DIR)input.h $(SRC_DIR)catalog.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)catalog.c -o $(BUILD_DIR)catalog.o

input.o: $(SRC_DIR)input.c $(SRC_DIR)input.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)input.c -o $(BUILD_DIR)input.o

# clean target
clean:
	rm -f $(PROGRAM) $(READ_OBJ_LIST) $(TEMP_FILES)
