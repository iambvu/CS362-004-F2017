CFLAGS = -Wall -fpic -coverage -lm

testme: testme.c
	gcc -o testme testme.c -g  $(CFLAGS)
	./testme

clean:
	rm -f testme *.o *.gcov *.gcda *.gcno *.out