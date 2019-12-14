# File: Makefile
# Author: Cody Burrows (dcodyburrows@gmail.com)
# Battleship Plus Plus 0.1
#
# This makefile provides various options to build this project.
# ##############################################################################

CXX         := -g++
CXXFLAGS    := -pedantic-errors -Wall -Wextra # -Werror # TODO DCB uncomment later
LDFLAGS     := 
BUILD       := ./build
OBJ_DIR     := $(BUILD)/obj
SRV_TARGET  := bpp_server
CLT_TARGET  := bpp_client
INCLUDE     := -Iinclude/
CLT_SRC     := $(wildcard src/client/*.cpp)
SRV_SRC     := $(wildcard src/serv/*.cpp)

SRV_OBJECTS     := $(SRV_SRC:%.cpp=$(OBJ_DIR)/%.o)
CLT_OBJECTS     := $(CLT_SRC:%.cpp=$(OBJ_DIR)/%.o)

server: build $(SRV_TARGET)
client: build $(CLT_TARGET)

all: build $(SRV_TARGET) $(CLT_TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

$(SRV_TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) -o $(SRV_TARGET) $(SRV_OBJECTS)

$(CLT_TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) -o $(CLT_TARGET) $(CLT_OBJECTS)

build:
	@mkdir -p $(OBJ_DIR)

debug: CXXFLAGS += -DDEBUG -g
debug: all

clean:
	-@rm -rvf $(OBJ_DIR)/*
