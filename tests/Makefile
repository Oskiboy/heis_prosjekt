#########################
#	Toolchain
#########################
CFLAGS += -I../src -I ../Unity/src
LDFLAGS = 
#########################
#	Defines
#########################
OUTPUT_DIR 	= build
TESTS		= fsm_tests
TEST_DEPS	= $(OUTPUT_DIR)/unity.o libelev_wrapper.a

#########################
#	Rules
#########################
.DEFAULT_RULE: all fsm_tests

all: $(OUTPUT_DIR) fsm_tests
	@echo "Building tests"

run_tests:
	./fsm_tests

$(OUTPUT_DIR)/unity.o:../Unity/src/unity.c | $(OUTPUT_DIR)
	$(CC) -o $@ -c $< $(CFLAGS)

$(OUTPUT_DIR)/elev.o: elev.c elev.h
	$(CC) -o $@ -c $< $(CFLAGS) -I.

fsm_tests: fsm_tests.c ../$(BUILD_DIR)/fsm.o $(TEST_DEPS)
	$(CC) -o $@ $^  $(CFLAGS) $(LDFLAGS)

$(OUTPUT_DIR):
	mkdir $(OUTPUT_DIR)