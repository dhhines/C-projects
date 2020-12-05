#-----------------------------------------------------------------------------------#
# Makefile for 'hash' program                                                       #
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
HASH_OBJ_LIST = $(BUILD_DIR)hash.o $(BUILD_DIR)buffer.o $(BUILD_DIR)sha1.o $(BUILD_DIR)hmac-sha1.o
BUFR_OBJ_LIST = $(BUILD_DIR)buffer.o
SHA_OBJ_LIST = $(BUILD_DIR)sha1.o
HMAC_OBJ_LIST = $(BUILD_DIR)hmac-sha1.o
PROGRAM = $(wildcard $(BIN_DIR)*.exe)
TEMP_FILES = $(wildcard $(BIN_DIR)output*.txt) $(BIN_DIR)stderr.txt $(BIN_DIR)stdout.txt

# hash program target
hash: hash.o buffer.o sha1.o hmac-sha1.o
	$(CC) $(CFLAGS) $(HASH_OBJ_LIST) -o $(BIN_DIR)hash

# object file targets
buffer.o: $(SRC_DIR)buffer.c $(SRC_DIR)buffer.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)buffer.c -o $(BUILD_DIR)buffer.o

sha1.o: $(SRC_DIR)sha1.c $(SRC_DIR)buffer.h $(SRC_DIR)sha1.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)sha1.c -o $(BUILD_DIR)sha1.o

hmac-sha1.o: $(SRC_DIR)hmac-sha1.c $(SRC_DIR)hmac-sha1.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)hmac-sha1.c -o $(BUILD_DIR)hmac-sha1.o

# test driver target
testdriver:
	gcc -Wall -std=c99 -g -DTESTABLE testdriver.c sha1.c buffer.c -o testdriver

# test driver2 target
testdriver2:
	gcc -Wall -std=c99 -g -DTESTABLE testdriver2.c sha1.c buffer.c -o testdriver2

# clean target
clean:
	rm -f $(PROGRAM) $(HASH_OBJ_LIST) $(TEMP_FILES)
