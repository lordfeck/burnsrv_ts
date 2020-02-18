CC = gcc
TEST_EXEC = fftest
CMP_EXEC = ffcmp
LIBRARY = fflib.c fflib.h

.PHONY: clean run debug all cleanbin tidy

# Need to call GCC with -lm to link math library defined in math.h
all: fftest ffcmp ffcnv ffimg

$(TEST_EXEC): $(TEST_EXEC).c $(LIBRARY)
	$(CC) fflib.c $(TEST_EXEC).c -o $(TEST_EXEC) -lm

$(CMP_EXEC): $(CMP_EXEC).c $(LIBRARY)
	$(CC) fflib.c $(CMP_EXEC).c -o $(CMP_EXEC) -lm

ffcnv: ffcnv.c $(LIBRARY)
	$(CC) fflib.c ffcnv.c -o ffcnv

ffimg: ffimg.c $(LIBRARY)
	$(CC) fflib.c ffimg.c -o ffimg 

debug: $(TEST_EXEC).c $(CMP_EXEC).c ffcnv.c $(LIBRARY) ffimg.c
	$(CC) -DDEBUG fflib.c ffcnv.c -o ffcnv
	$(CC) -DDEBUG fflib.c $(TEST_EXEC).c -o $(TEST_EXEC) -lm
	$(CC) -DDEBUG fflib.c $(CMP_EXEC).c -o $(CMP_EXEC) -lm
	$(CC) -DDEBUG fflib.c ffimg.c -o ffimg 

run: $(TEST_EXEC)
	./$(TEST_EXEC)

clean:
	@rm -vf $(TEST_EXEC) $(CMP_EXEC) ffi ffcnv ffimg *.o 

tidy:
	@echo 'Tidying up stray binfiles and textfiles.'
	rm -vf *.txt *.bin
