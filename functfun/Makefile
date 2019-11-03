CC = gcc
TEST_EXEC = fftest

.PHONY: clean 

# Need to call GCC with -lm to link math library defined in math.h

$(TEST_EXEC): $(TEST_EXEC).c 
	$(CC) $(TEST_EXEC).c -o $(TEST_EXEC) -lm

clean:
	@rm -vf $(TEST_EXEC) *.o
