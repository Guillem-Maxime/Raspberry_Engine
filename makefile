MAKEFILE_PATH = $(abspath $(lastword $(MAKEFILE_LIST)))
MAKE_DIR = $(MAKEFILE_PATH:/makefile=)
 
OBJ_DIR			:= $(MAKE_DIR)/objects
SRC_DIR			:= $(MAKE_DIR)/src

ENGINE_DIR		:= $(MAKE_DIR)/engine
GRAPHICS_DIR	:= $(MAKE_DIR)/graphics
UTILS_DIR		:= $(MAKE_DIR)/utils
COMMON_DIR		:= $(MAKE_DIR)/common
EXT_DIR			:= $(MAKE_DIR)/ext

INCLUDE := $(MAKE_DIR)/

CXX = clang++-8
EXEC = Rasp_Earth_Display.exe
DEBUG = yes
CXXFLAGS = -I$(INCLUDE) -std=c++17 -pedantic -fPIC -Wall -W $(WARNINGFLAGS)
WARNINGFLAGS =
ifeq ($(DEBUG),yes)
CXXFLAGS := $(CXXFLAGS) -g
endif

LIBS := -lGL -lglut -lGLEW -lassimp

export MAKE_DIR CXX CXXFLAGS WARNINGFLAGS LIBS INCLUDE EXEC OBJ_DIR

all:
	@$(MAKE) -C $(ENGINE_DIR)   	-f engine.mk
	@$(MAKE) -C $(EXT_DIR)    		-f ext.mk
	@$(MAKE) -C $(GRAPHICS_DIR) 	-f graphics.mk
	@$(MAKE) -C $(UTILS_DIR)    	-f utils.mk

	@$(MAKE) -C $(SRC_DIR) 			-f rasp_earth_display.mk

.PHONY: clean
clean:
##	rm -f $(MAKE_DIR)/src/
	@$(MAKE) -C $(SRC_DIR) 			-f rasp_earth_display.mk clean
	@$(MAKE) -C $(GRAPHICS_DIR) 	-f graphics.mk clean
	@$(MAKE) -C $(UTILS_DIR)		-f utils.mk clean	
	@$(MAKE) -C $(EXT_DIR)			-f ext.mk clean
	@$(MAKE) -C $(ENGINE_DIR)			-f engine.mk clean

