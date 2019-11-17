CFLAGS= -Wall -fpic -coverage -lm -std=c99

randomtests.o: dominion.h dominion.c rngs.o randomtests.h randomtests.c
		gcc -c randomtests.c -g  $(CFLAGS)

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

randomtestresults: randomtestcard1 randomtestcard2
		#./randomtestcard1 &> randomtestresult.out
		./randomtestcard2 &> randomtestresult.out
		gcov -b -f dominion.c >> randomtestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
