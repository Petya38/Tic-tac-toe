.PHONY: all clean

CXXFLAGS=-c -Wall -Wextra -Werror -Iinclude -g -fsanitize=address -std=c++17

all: hw_02 test_hw_02

hw_02: obj/main.o obj/Board.o obj/BoardView.o obj/StdioBoardView.o obj/NcursesBoardView.o obj/GameController.o
	g++ obj/main.o obj/Board.o obj/BoardView.o obj/StdioBoardView.o obj/NcursesBoardView.o obj/GameController.o -lncurses -o hw_02 -g -fsanitize=address

test: test_hw_02

test_hw_02: obj/test_hw_02.o obj/Test.o obj/BoardTest.o obj/Board.o
	g++ obj/test_hw_02.o obj/Test.o obj/BoardTest.o obj/Board.o -o test_hw_02 -g -fsanitize=address

obj: 
	mkdir obj

obj/main.o: src/main.cpp obj/Board.o obj/BoardView.o obj/StdioBoardView.o | obj
	g++ $(CXXFLAGS) src/main.cpp -o obj/main.o

obj/Board.o: src/Board.cpp include/Board.hpp | obj
	g++ $(CXXFLAGS) src/Board.cpp -o obj/Board.o

obj/BoardView.o: src/BoardView.cpp include/BoardView.hpp | obj
	g++ $(CXXFLAGS) src/BoardView.cpp -o obj/BoardView.o

obj/StdioBoardView.o: obj/BoardView.o src/StdioBoardView.cpp include/StdioBoardView.hpp | obj
	g++ $(CXXFLAGS) src/StdioBoardView.cpp -o obj/StdioBoardView.o

obj/NcursesBoardView.o: obj/BoardView.o src/NcursesBoardView.cpp include/NcursesBoardView.hpp | obj
	g++ $(CXXFLAGS) src/NcursesBoardView.cpp -o obj/NcursesBoardView.o

obj/GameController.o: src/GameController.cpp include/GameController.hpp obj/Board.o obj/BoardView.o obj/StdioBoardView.o | obj
	g++ $(CXXFLAGS) src/GameController.cpp -o obj/GameController.o
	
obj/test_hw_02.o: obj/Test.o obj/BoardTest.o | obj
	g++ $(CXXFLAGS) test/test.cpp -o obj/test_hw_02.o

obj/Test.o: test/Test.cpp include/Test.hpp obj/BoardTest.o | obj
	g++ $(CXXFLAGS) test/Test.cpp -o obj/Test.o

obj/BoardTest.o: test/BoardTest.cpp include/BoardTest.hpp | obj
	g++ $(CXXFLAGS) test/BoardTest.cpp -o obj/BoardTest.o

clean:
	rm obj hw_02 test_hw_02 -rf