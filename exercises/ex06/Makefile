#-----------------------------------------------------------------------------------#
# Makefile for main program                                                         #
# Variables created for compiler and standard flags                                 #
# Also created variables for the separate directories to keep build location clean  #
#                                                                                   #
# Targets:                                                                          #
# main: builds main program in /                                                 #
# main.o: builds main build objects in /                                       #
# print.o: builds print objects in /                                           #
# clean: removes all objects and program files                                      #
#                                                                                   #
# @author:  David Hines                                                             #
#-----------------------------------------------------------------------------------#

CC = gcc
CFLAGS = -Wall -std=c99 -g
SRC_DIR = ./
BUILD_DIR = ./
BIN_DIR = ./
SRC_LIST = $(wildcard $(SRC_DIR)*.c)
OBJ_LIST = $(BUILD_DIR)main.o $(BUILD_DIR)print.o 
PROGRAM = $(wildcard $(BIN_DIR)*.exe)


#Main program target
main: main.o print.o
	$(CC) $(CFLAGS) $(OBJ_LIST) -o $(BIN_DIR)main

#object file targets
main.o: $(SRC_DIR)print.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)main.c -o $(BUILD_DIR)main.o 

print.o: $(SRC_DIR)print.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)print.c -o $(BUILD_DIR)print.o

clean:
	rm -f $(PROGRAM) $(OBJ_LIST)


