CFLAGS= -Wall -fpic -coverage -lm -std=c99

testme: testme.c 
	gcc -o testme -g testme.c $(CFLAGS)
	./testme &> testme.out || true
	gcov -b -f testme.c >> testme.out

clean:
	rm -f *.o *.gcov *.gcda *.gcno *.so *.out testme
