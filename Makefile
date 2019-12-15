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
SRV_TARGET  := bpp_server
CLT_TARGET  := bpp_client
INCLUDE     := -Isrc/common/
COMMON_SRC  := $(wildcard src/common/*.cpp)
CLT_SRC     := $(wildcard src/client/*.cpp)
SRV_SRC     := $(wildcard src/serv/*.cpp)
CTRL_SRC    := $(wildcard src/controller/*.cpp)

SRV_OBJECTS     := $(SRV_SRC:%.cpp=$(OBJ_DIR)/%.o)
CLT_OBJECTS     := $(CLT_SRC:%.cpp=$(OBJ_DIR)/%.o)
COMMON_OBJECTS  := $(COMMON_SRC:%.cpp=$(OBJ_DIR)/%.o)
CTRL_OBJECTS    := $(CTRL_SRC:%.cpp=$(OBJ_DIR)/%.o)

all: build $(SRV_TARGET) $(CLT_TARGET)

server: build $(SRV_TARGET)
client: build $(CLT_TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

$(SRV_TARGET): $(SRV_OBJECTS) $(COMMON_OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) -o $(SRV_TARGET) $(SRV_OBJECTS) \
        $(COMMON_OBJECTS)

$(CLT_TARGET): $(CLT_OBJECTS) $(COMMON_OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) -o $(CLT_TARGET) $(CLT_OBJECTS) \
        $(COMMON_OBJECTS)

build:
	@mkdir -p $(OBJ_DIR)

debug: CXXFLAGS += -DDEBUG -g
debug: all

clean:
	-@rm -rv $(BUILD)/*
	-@rmdir -v $(BUILD)

uberclean: clean
	-@rm -v $(SRV_TARGET)
	-@rm -v $(CLT_TARGET)
