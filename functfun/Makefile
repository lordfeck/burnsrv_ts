CC = gcc
TEST_EXEC = fftest

.PHONY: clean run

# Need to call GCC with -lm to link math library defined in math.h

$(TEST_EXEC): $(TEST_EXEC).c 
	$(CC) $(TEST_EXEC).c -o $(TEST_EXEC) -lm

ffi : ffi.c
	$(CC) ffi.c -o ffi

run: $(TEST_EXEC)
	./$(TEST_EXEC)

clean:
	@rm -vf $(TEST_EXEC) ffi *.log *.o
