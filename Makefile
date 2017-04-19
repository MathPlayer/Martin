SHELL := /bin/bash
CXX := g++
CXXFLAGS := -Werror

BIN_DIR := bin
SRC_DIR := src

EXEC := $(BIN_DIR)/martin
SOURCES := $(wildcard $(SRC_DIR)/*.cc)
HEADERS := $(wildcard $(SRC_DIR)/*.h)
OBJECTS := $(SOURCES:$(SRC_DIR)/%.cc=$(BIN_DIR)/%.o)

.PHONY: all prebuild debug clean

all: prebuild $(EXEC)

debug: CXXFLAGS += -DDEBUG
debug: clean prebuild $(EXEC)

prebuild: | $(BIN_DIR)

$(BIN_DIR):
	mkdir -p $@

$(EXEC): $(OBJECTS) | $(BIN_DIR)
	$(CXX) -o $@ $^

$(BIN_DIR)/%.o: $(SRC_DIR)/%.cc
	$(CXX) -o $@ -c $(CXXFLAGS) $<

clean:
	rm -rf $(EXEC) $(BIN_DIR)
