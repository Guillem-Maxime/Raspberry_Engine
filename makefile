MAKEFILE_PATH = $(abspath $(lastword $(MAKEFILE_LIST)))
MAKE_DIR = $(MAKEFILE_PATH:/makefile=)
 
OBJ_DIR			:= $(MAKE_DIR)/objects
SRC_DIR			:= $(MAKE_DIR)/src

GRAPHICS_DIR	:= $(MAKE_DIR)/graphics
UTILS_DIR		:= $(MAKE_DIR)/utils

INCLUDE := $(MAKE_DIR)/

CXX = clang++

EXEC = Rasp_Earth_Display.exe
DEBUG = yes
CXXFLAGS = -std=c++17 -W -Wall -pedantic -fPIC -I$(INCLUDE)
ifeq ($(DEBUG),yes)
CXXFLAGS := $(CXXFLAGS) -g
endif

LIBS := -lGL -lglut -lGLEW


export MAKE_DIR CXX CXXFLAGS LIBS INCLUDE EXEC OBJ_DIR

all:
##      @$(MAKE) -C $(ENGINE_DIR)   -f makefile_engine.mk
	@$(MAKE) -C $(GRAPHICS_DIR) -f graphics.mk
	@$(MAKE) -C $(UTILS_DIR)    -f utils.mk

	@$(MAKE) -C $(SRC_DIR) -f rasp_earth_display.mk

.PHONY: clean
clean:
##	rm -f $(MAKE_DIR)/src/
	@$(MAKE) -C $(SRC_DIR) 	-f rasp_earth_display.mk clean
	@$(MAKE) -C $(GRAPHICS_DIR) 	-f graphics.mk clean
	@$(MAKE) -C $(UTILS_DIR)	-f utils.mk clean
