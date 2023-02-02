test1: clean compile testInsert
test2: clean compile testSearches
test3: clean compile testRemovals
test4: clean compile testRebalance

clean:
	rm -f test
  
compile: main.cpp
	g++ -I . -o test main.cpp
  
testInsert:
	./test 1

testSearches:
	./test 2

testRemovals:
	./test 3

testRebalance:
	./test 4

