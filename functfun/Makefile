CC = gcc
TEST_EXEC = fftest
CMP_EXEC = ffcmp

.PHONY: clean run debug all cleanbin

# Need to call GCC with -lm to link math library defined in math.h
all: fftest ffcmp ffcnv

$(TEST_EXEC): $(TEST_EXEC).c 
	$(CC) fflib.c $(TEST_EXEC).c -o $(TEST_EXEC) -lm

$(CMP_EXEC): $(CMP_EXEC).c 
	$(CC) fflib.c $(CMP_EXEC).c -o $(CMP_EXEC) -lm

ffcnv: ffcnv.c
	$(CC) fflib.c ffcnv.c -o ffcnv

debug: $(TEST_EXEC).c $(CMP_EXEC).c ffcnv.c
	$(CC) -DDEBUG fflib.c ffcnv.c -o ffcnv
	$(CC) -DDEBUG fflib.c $(TEST_EXEC).c -o $(TEST_EXEC) -lm
	$(CC) -DDEBUG fflib.c $(CMP_EXEC).c -o $(CMP_EXEC) -lm

ffi: ffi.c
	$(CC) ffi.c -o ffi

run: $(TEST_EXEC)
	./$(TEST_EXEC)

clean:
	@rm -vf $(TEST_EXEC) $(CMP_EXEC) ffi ffcnv *.o *.bin
