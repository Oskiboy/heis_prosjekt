#########################
#	Toolchain
#########################
CFLAGS	+= -I../src -I ../Unity/src

#########################
#	Defines
#########################
OUTPUT_DIR 	= build
TESTS		= fsm_tests logger_test
TEST_DEPS	= $(OUTPUT_DIR)/unity.o libelev_wrapper.a

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
	echo "FSM TESTS:"
	./fsm_tests

logger_test: ../build/logger.o test_logger.c $(TEST_DEPS)
	$(CC) -o $@ $^ $(CFLAGS)

fsm_tests: fsm_tests.c ../$(BUILD_DIR)/fsm.o $(TEST_DEPS)
	$(CC) -o $@ $^  $(CFLAGS) $(LDFLAGS)

$(OUTPUT_DIR)/unity.o:../Unity/src/unity.c | $(OUTPUT_DIR)
	$(CC) -o $@ -c $< $(CFLAGS)

$(OUTPUT_DIR)/elev.o: elev.c elev.h
	$(CC) -o $@ -c $< $(CFLAGS) -I.

$(OUTPUT_DIR):
	mkdir $(OUTPUT_DIR)

clean:
	rm $(TESTS)