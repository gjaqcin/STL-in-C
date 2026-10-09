CC = gcc
AR = ar
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -g
CPPFLAGS = -Iinclude

BUILD = build
LIB = $(BUILD)/libcstl.a
OBJ = $(BUILD)/int_vector.o

.PHONY: all test example clean

all: $(LIB) $(BUILD)/test_int_vector $(BUILD)/vector_example

$(BUILD):
	mkdir -p $(BUILD)

$(OBJ): src/int_vector.c include/cstl/int_vector.h | $(BUILD)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(LIB): $(OBJ)
	$(AR) rcs $@ $^

$(BUILD)/test_int_vector: tests/test_int_vector.c $(LIB)
	$(CC) $(CPPFLAGS) $(CFLAGS) $< $(LIB) -o $@

$(BUILD)/vector_example: examples/vector_example.c $(LIB)
	$(CC) $(CPPFLAGS) $(CFLAGS) $< $(LIB) -o $@

test: $(BUILD)/test_int_vector
	./$(BUILD)/test_int_vector

example: $(BUILD)/vector_example
	./$(BUILD)/vector_example

clean:
	rm -rf $(BUILD)
