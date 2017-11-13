CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

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

########
unittest1_vub: unittest1_vub.c dominion.o rngs.o
	gcc -o unittest1_vub -g unittest1_vub.c dominion.o rngs.o $(CFLAGS)

unittest2_vub: unittest2_vub.c dominion.o rngs.o
	gcc -o unittest2_vub -g unittest2_vub.c dominion.o rngs.o $(CFLAGS)

unittest3_vub: unittest3_vub.c dominion.o rngs.o
	gcc -o unittest3_vub -g unittest3_vub.c dominion.o rngs.o $(CFLAGS)

unittest4_vub: unittest4_vub.c dominion.o rngs.o
	gcc -o unittest4_vub -g unittest4_vub.c dominion.o rngs.o $(CFLAGS)

cardtest1_vub: cardtest1_vub.c dominion.o rngs.o interface.o
	gcc -o cardtest1_vub -g cardtest1_vub.c dominion.o rngs.o interface.o $(CFLAGS)

cardtest2_vub: cardtest2_vub.c dominion.o rngs.o interface.o
	gcc -o cardtest2_vub -g cardtest2_vub.c dominion.o rngs.o interface.o $(CFLAGS)

cardtest3_vub: cardtest3_vub.c dominion.o rngs.o interface.o
	gcc -o cardtest3_vub -g cardtest3_vub.c dominion.o rngs.o interface.o $(CFLAGS)

cardtest4_vub: cardtest4_vub.c dominion.o rngs.o interface.o
	gcc -o cardtest4_vub -g cardtest4_vub.c dominion.o rngs.o interface.o $(CFLAGS)

unittestresults.out: unittest1_vub unittest2_vub unittest3_vub unittest4_vub cardtest1_vub cardtest2_vub cardtest3_vub cardtest4_vub
	./unittest1_vub &> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	./unittest2_vub >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	./unittest3_vub >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	./unittest4_vub >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	./cardtest1_vub >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	./cardtest2_vub >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	./cardtest3_vub >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	./cardtest4_vub >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
########

########
randomtestadventurerresult: randomtestadventurer_vub
	./randomtestadventurer_vub &> randomtestadventurerresult.out
	gcov -f -b dominion.c >> randomtestadventurerresult.out
	cat dominion.c.gcov >> randomtestadventurerresult.out

randomtestcard1result: randomtestcard1_vub
	./randomtestcard1_vub &> randomtestcard1result.out
	gcov -f -b dominion.c >> randomtestcard1result.out
	cat dominion.c.gcov >> randomtestcard1result.out

randomtestcard2result: randomtestcard2_vub
	./randomtestcard2_vub &> randomtestcard2result.out
	gcov -f -b dominion.c >> randomtestcard2result.out
	cat dominion.c.gcov >> randomtestcard2result.out

randomtestadventurer_vub: randomtestadventurer_vub.c dominion.o rngs.o interface.o
	gcc -o randomtestadventurer_vub -g randomtestadventurer_vub.c dominion.o rngs.o interface.o $(CFLAGS)

randomtestcard1_vub: randomtestcard1_vub.c dominion.o rngs.o interface.o
	gcc -o randomtestcard1_vub -g randomtestcard1_vub.c dominion.o rngs.o interface.o $(CFLAGS)

randomtestcard2_vub: randomtestcard2_vub.c dominion.o rngs.o interface.o
	gcc -o randomtestcard2_vub -g randomtestcard2_vub.c dominion.o rngs.o interface.o $(CFLAGS)
########

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard unittest1_vub unittest2_vub unittest3_vub unittest4_vub cardtest1_vub cardtest2_vub cardtest3_vub cardtest4_vub

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe badTestDrawCard
