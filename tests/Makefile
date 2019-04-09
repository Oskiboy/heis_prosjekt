#########################
#	Toolchain
#########################
CFLAGS	+= -I../src -I ../Unity/src

#########################
#	Defines
#########################
OUTPUT_DIR 	= build
TESTS		= fsm_tests
TESTS		:= $(addprefix $(OUTPUT_DIR)/,$(TESTS))
TEST_DEPS	= $(OUTPUT_DIR)/unity.o libelev_wrapper.a

#########################
#	Rules
#########################
.DEFAULT_RULE: all
	
.PHONY: all run_tests logger_tests clean

all: $(OUTPUT_DIR)/unity.o $(TESTS)
	@echo "Building tests"

run_tests: all
	@echo "Running tests"
	./build/fsm_tests

$(OUTPUT_DIR)/fsm_tests: fsm_tests.c ../$(BUILD_DIR)/fsm.o ../$(BUILD_DIR)/light_handler.o $(TEST_DEPS)
	$(CC) -o $@ $^  $(CFLAGS) $(LDFLAGS)

$(OUTPUT_DIR)/queue_test: ../build/queue_handler.o test_queue.c $(TEST_DEPS)
	$(CC) -o $@ $^ $(CFLAGS)

$(OUTPUT_DIR)/unity.o:../Unity/src/unity.c | $(OUTPUT_DIR)
	$(CC) -o $@ -c $< $(CFLAGS)

$(OUTPUT_DIR)/elev.o: elev.c elev.h
	$(CC) -o $@ -c $< $(CFLAGS)

$(OUTPUT_DIR):
	mkdir $(OUTPUT_DIR)

clean:
	rm -rf $(OUTPUT_DIR)