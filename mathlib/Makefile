CC = gcc
MATHLIB = mathops.c

.PHONY: clean

mathtest: mathtest.c $(MATHLIB)
	$(CC) mathtest.c $(MATHLIB) -o mathtest

clean:
	@rm -vf mathtest *.o
