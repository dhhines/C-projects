#-----------------------------------------------------------------------------------#
# Makefile for 'chop' program                                                       #
# Variables created for compiler and standard flags                                 #
# Also created variables for the separate directories to keep build location clean  #
#                                                                                   #
# Targets:                                                                          #
# all: builds all target programs in /                                              #
# chop: builds chop build objects in /                                              #
# edit: builds edit objects in /                                                    #
# text:	builds text objects in /                                                    #
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
CHOP_OBJ_LIST = $(BUILD_DIR)chop.o $(BUILD_DIR)edit.o $(BUILD_DIR)text.o
EDIT_OBJ_LIST = $(BUILD_DIR)edit.o
TEXT_OBJ_LIST = $(BUILD_DIR)text.o
PROGRAM = $(wildcard $(BIN_DIR)*.exe)
TEMP_FILES = $(wildcard $(BIN_DIR)output*.txt) $(BIN_DIR)stderr.txt $(BIN_DIR)stdout.txt

# chop program target
chop: chop.o edit.o text.o
	$(CC) $(CFLAGS) $(CHOP_OBJ_LIST) -o $(BIN_DIR)chop

# object file targets
chop.o: $(SRC_DIR)edit.h $(SRC_DIR)text.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)chop.c -o $(BUILD_DIR)chop.o

edit.o: $(SRC_DIR)edit.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)edit.c -o $(BUILD_DIR)edit.o

text.o: $(SRC_DIR)text.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)text.c -o $(BUILD_DIR)text.o

# clean target
clean:
	rm -f $(PROGRAM) $(CHOP_OBJ_LIST) $(TEMP_FILES)

