# File: Makefile
# Author: Cody Burrows (dcodyburrows@gmail.com)
# Battleship Plus Plus 0.1
#
# This makefile provides various options to build this project.
# ##############################################################################

CXX         := -g++
CXXFLAGS    := -pedantic-errors -Wall -Wextra -Werror
LDFLAGS     := 
BUILD       := ./build
OBJ_DIR     := $(BUILD)/obj
TARGET      := bpp
INCLUDE     := -Iinclude/
SRC         :=  $(wildcard src/serv/*.cpp) \
                $(wildcard src/client/*.cpp) \

OBJECTS     := $(SRC:%.cpp=$(OBJ_DIR)/%.o)

all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) -o $(APP_DIR)/$(TARGET) $(OBJECTS)

build:
	@mkdir -p $(OBJ_DIR)

debug: CXXFLAGS += -DDEBUG -g
debug: all

clean:
	-@rm -rvf $(OBJ_DIR)/*

