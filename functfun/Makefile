CC = gcc
TEST_EXEC = fftest
CMP_EXEC = ffcmp
FLAGS = -DDEBUG

.PHONY: clean run debug

# Need to call GCC with -lm to link math library defined in math.h

$(TEST_EXEC): $(TEST_EXEC).c 
	$(CC) $(TEST_EXEC).c -o $(TEST_EXEC) -lm

$(CMP_EXEC): $(CMP_EXEC).c 
	$(CC) $(CMP_EXEC).c -o $(CMP_EXEC)

debug: $(TEST_EXEC).c 
	$(CC) $(FLAGS) $(TEST_EXEC).c -o $(TEST_EXEC) -lm

ffi : ffi.c
	$(CC) ffi.c -o ffi

run: $(TEST_EXEC)
	./$(TEST_EXEC)

clean:
	@rm -vf $(TEST_EXEC) $(CMP_EXEC) ffi *.log *.o
