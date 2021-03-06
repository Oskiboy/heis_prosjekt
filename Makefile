###################
# Set up variables
###################


SOURCES 		:= main.c fsm.c queue_handler.c light_handler.c

ELEV_DRIVER_SRC := elev.c io.c
BUILD_DIR 		:= build
SRC_DIR 		:= src

##################
# Import all source files.
##################
OBJ 			:= $(SOURCES:%.c=$(BUILD_DIR)/%.o)
SRC 			:= $(SOURCES:%.c=$(SRC_DIR)/%.c)
ELEV_DRIVER_OBJ := $(ELEV_DRIVER_SRC:%.c=$(BUILD_DIR)/%.o)


##################
# Set up toolchain
##################
CC 		:= clang
CFLAGS 	:= -O0 -g3 -Wall -Werror -std=gnu99
LDFLAGS := -lcomedi -lm



# This gives make a search pattern for all %.c targets.
vpath %.c $(SRC_DIR)

.DEFAULT_GOAL := heis

#################
# Defines rules.
#################
.PHONY: heis
heis: $(OBJ) $(ELEV_DRIVER_OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $(BUILD_DIR)/$@

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)/*

.PHONY: docs
docs:
	doxygen Doxyfile

#############################
# Unit tests.
#############################
.PHONY: tests run_tests clean_tests
export BUILD_DIR
export CFLAGS
export CC
tests: heis
	make -C tests

run_tests: tests
	make -C tests run_tests

clean_tests:
	make -C tests clean
