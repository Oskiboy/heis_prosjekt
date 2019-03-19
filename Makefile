SOURCES := main.c
ELEV_DRIVER_SRC := elev.c io.c
BUILD_DIR := build
OBJ := $(SOURCES:%.c=$(BUILD_DIR)/%.o)

SRC_DIR := src
SRC := $(SOURCES:%.c=$(SRC_DIR)/%.c)

CC := gcc
CFLAGS := -O0 -g3 -Wall -Werror -std=gnu99

LDFLAGS := -lcomedi -lm

.DEFAULT_GOAL := heis

vpath %.c $(SRC_DIR)

heis : $(OBJ) 
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) -o $@

elev_drv: $(BUILD_DIR)/elev_driver.o

$(BUILD_DIR)/elev_driver: $(ELEV_DRIVER_SRC)
	$(CC) $(CFLAGS) $(LDFLAGS) $^

$(BUILD_DIR) :
	mkdir $(BUILD_DIR)

$(BUILD_DIR)/%.o : %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY : clean
clean:
	rm -rf $(.DEFAULT_GOAL) $(BUILD_DIR)
