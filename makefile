CC = g++
CFLAGS = -Iinclude -Wall -Wextra

SRC_DIR = src
BIN_DIR = bin
TARGET = $(BIN_DIR)/TrayRacer

SRCS = $(SRC_DIR)/main.cpp

all: $(BIN_DIR) $(TARGET)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)                     

