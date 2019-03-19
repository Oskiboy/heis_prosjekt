###################
# Set up variables
###################

SOURCES 		:= main.c
ELEV_DRIVER_SRC := elev.c io.c
BUILD_DIR 		:= build
SRC_DIR 		:= src

##################
# Import all source files.
##################
OBJ := $(SOURCES:%.c=$(BUILD_DIR)/%.o)
SRC := $(SOURCES:%.c=$(SRC_DIR)/%.c)


##################
# Set up toolchain
##################
CC 		:= gcc
CFLAGS 	:= -O0 -g3 -Wall -Werror -std=gnu99
LDFLAGS := -lcomedi -lm



# This gives make a search pattern for all %.c targets.
vpath %.c $(SRC_DIR)

.DEFAULT_GOAL := heis

#################
# Defines rules.
#################
.PHONY: heis
heis: $(OBJ) 
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) -o $@

.PHONY: elev_drv
elev_drv: $(BUILD_DIR)/elev_driver.o

$(BUILD_DIR)/elev_driver.o: $(ELEV_DRIVER_SRC)
	$(CC) $(CFLAGS) $(LDFLAGS) $^

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(.DEFAULT_GOAL) $(BUILD_DIR)


#############################
# Unit tests.
#############################
UNITY_DIR 	:= Unity
TEST_DIR 	:= tests
TEST_SOURCES:= 
TEST_SRC	:= $(TEST_SRC:%.c=$(TEST_DIR)/%.c)
TESTS		:=
.PHONY: tests
tests: unity
run_tests: tests

.PHONY: unity
unity: $(UNITY_DIR)/unity.c
	$(CC) -o $@ $< -I$(UNITY_DIR)


