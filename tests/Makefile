#########################
#	Toolchain
#########################
CFLAGS	+= -I../src -I ../Unity/src

#########################
#	Defines
#########################
OUTPUT_DIR 	= build
TESTS		= 
TEST_DEPS	= $(OUTPUT_DIR)/unity.o

#########################
#	Rules
#########################
.DEFAULT_RULE: all

all: $(OUTPUT_DIR)/unity.o
	@echo "Building tests"

$(OUTPUT_DIR)/unity.o:../Unity/src/unity.c | $(OUTPUT_DIR)
	$(CC) -o $@ -c $< $(CFLAGS)

$(OUTPUT_DIR):
	mkdir $(OUTPUT_DIR)