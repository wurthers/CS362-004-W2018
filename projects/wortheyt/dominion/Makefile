CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g testDrawCard.c dominion.o rngs.o $(CFLAGS)

randomtests.out: randomtest*.c dominion.o rngs.o
	echo "Running Assignment 4 Random Test for Adventurer" >> randomtestadventurer.out
	gcc -o randomtestadventurer randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
	./randomtestadventurer >> randomtestadventurer.out
	gcov dominion.c >> randomtestadventurer.out

	echo "Running Assignment 4 Random Test for Village" >> randomtestcard1.out
	gcc  -o randomtestcard1 randomtestcard1.c dominion.o rngs.o $(CFLAGS)
	./randomtestcard1 >> randomtestcard1.out
	gcov dominion.c >> randomtestcard1.out

	echo "Running Assignment 4 Random Test for Baron" >> randomtestcard2.out
	gcc -o randomtestcard2 randomtestcard2.c dominion.o rngs.o $(CFLAGS)
	./randomtestcard2 >> randomtestcard2.out
	gcov dominion.c >> randomtestcard2.out

tests.out: unittest*.c cardtest*.c dominion.o rngs.o
	echo "Running Assignment 3 Unit Tests" >> tests.out

	echo "unittest1" >> tests.out
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)
	./unittest1 >> tests.out
	gcov dominion.c >> tests.out

	echo "unittest2" >> tests.out
	gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)
	./unittest2 >> tests.out
	gcov dominion.c >> tests.out

	echo "unittest3" >> tests.out
	gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)
	./unittest3 >> tests.out
	gcov dominion.c >> tests.out

	echo "unittest4" >> tests.out
	gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)
	./unittest4 >> tests.out
	gcov dominion.c >> tests.out

	echo "cardtest1" >> tests.out
	gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)
	./cardtest1 >> tests.out
	gcov dominion.c >> tests.out

	echo "cardtest2" >> tests.out
	gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)
	./cardtest2 >> tests.out
	gcov dominion.c >> tests.out

	echo "cardtest3" >> tests.out
	gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)
	./cardtest3 >> tests.out
	gcov dominion.c >> tests.out

	echo "cardtest4" >> tests.out
	gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)
	./cardtest4 >> tests.out
	gcov dominion.c >> tests.out


badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

tests: unittest1.c cardtest1.c
	gcc -o unittest1 unittest1.c
	gcc -o cardtest1 cardtest1.c

all: playdom player testDrawCard testBuyCard badTestDrawCard tests

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
