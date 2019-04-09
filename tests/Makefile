#########################
#	Toolchain
#########################
CFLAGS	+= -I../src -I ../Unity/src

#########################
#	Defines
#########################
OUTPUT_DIR 	= build
TESTS		= logger_test
TEST_DEPS	= $(OUTPUT_DIR)/unity.o

#########################
#	Rules
#########################
.DEFAULT_RULE: all
.PHONY: all run_tests logger_test clean

all: $(OUTPUT_DIR)/unity.o $(TESTS)
	@echo "Building tests"

run_tests: all
	echo "LOGGER TESTS:"
	./logger_test

logger_test: ../build/logger.o test_logger.c $(TEST_DEPS)
	$(CC) -o $@ $^ $(CFLAGS)

queue_test: ../build/queue_handler.o test_queue.c $(TEST_DEPS)
	$(CC) -o $@ $^ $(CFLAGS)

$(OUTPUT_DIR)/unity.o:../Unity/src/unity.c | $(OUTPUT_DIR)
	$(CC) -o $@ -c $< $(CFLAGS)

$(OUTPUT_DIR):
	mkdir $(OUTPUT_DIR)

clean:
	rm $(TESTS)