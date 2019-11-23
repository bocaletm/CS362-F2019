CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

randomtestcard1: randomtestcard1.c randomtestcard1.c randomtests.h dominion.o rngs.o
		gcc -o randomtestcard1 -g randomtestcard1.c randomtests.c randomtests.h dominion.o rngs.o $(CFLAGS)

randomtestcard2: randomtestcard2.c randomtestcard2.c randomtests.h dominion.o rngs.o
		gcc -o randomtestcard2 -g randomtestcard2.c randomtests.c randomtests.h dominion.o rngs.o $(CFLAGS)

randomtestcard3: randomtestcard3.c randomtestcard3.c randomtests.h dominion.o rngs.o
		gcc -o randomtestcard3 -g randomtestcard3.c randomtests.c randomtests.h dominion.o rngs.o $(CFLAGS)

randomtestresults: randomtestcard1 randomtestcard2 randomtestcard3
		./randomtestcard1 &> randomtestresult.out
		./randomtestcard2 &> randomtestresult.out
		./randomtestcard3 &> randomtestresult.out
		gcov -b -f dominion.c >> randomtestresult.out

unittest1: unittest1.c unittests.c unittests.h dominion.o rngs.o
	gcc -o unittest1 -g unittest1.c unittests.c unittests.h dominion.o rngs.o $(CFLAGS)

unittest2: unittest2.c unittests.c unittests.h dominion.o rngs.o
	gcc -o unittest2 -g unittest2.c unittests.c unittests.h dominion.o rngs.o $(CFLAGS)

unittest3: unittest3.c unittests.c unittests.h dominion.o rngs.o
	gcc -o unittest3 -g unittest3.c unittests.c unittests.h dominion.o rngs.o $(CFLAGS)

unittest4: unittest4.c unittests.c unittests.h dominion.o rngs.o
	gcc -o unittest4 -g unittest4.c unittests.c unittests.h dominion.o rngs.o $(CFLAGS)

unittest5: unittest5.c unittests.c unittests.h dominion.o rngs.o
	gcc -o unittest5 -g unittest5.c unittests.c unittests.h dominion.o rngs.o $(CFLAGS)

unittestresults: unittest1 unittest2 unittest3 unittest4 unittest5
	./unittest1 &> unittestresult.out
	./unittest2 >> unittestresult.out
	./unittest3 >> unittestresult.out
	./unittest4 >> unittestresult.out
	./unittest5 >> unittestresult.out
	gcov -b -f dominion.c >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe randkomtestcard1 randkomtestcard2 randkomtestcard3 unittest1 unittest2 unittest3 unittest4 unittest5 playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
