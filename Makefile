SHELL := /bin/bash
CC := gcc
CFLAGS := -Werror

BIN_DIR := bin
SRC_DIR := src

EXEC := $(BIN_DIR)/main
SOURCES := $(wildcard $(SRC_DIR)/*.c)
HEADERS := $(wildcard $(SRC_DIR)/*.h)
OBJECTS := $(SOURCES:$(SRC_DIR)/%.c=$(BIN_DIR)/%.o)

.PHONY: all prebuild debug clean

all: prebuild $(EXEC)

debug: CFLAGS += -DDEBUG
debug: clean prebuild $(EXEC) postbuild

prebuild: | $(BIN_DIR)

$(BIN_DIR):
	mkdir -p $@

$(EXEC): $(OBJECTS) | $(BIN_DIR)
	$(CC) -o $@ $^

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -o $@ -c $(CCFLAGS) $<

clean:
	rm -rf $(EXEC) $(BIN_DIR)
