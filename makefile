CXXFLAGS := -pedantic -Wall
TESTFLAGS := -lgtest -lgtest_main -lpthread
GCOVFLAGS := -fprofile-arcs -ftest-coverage

clean:
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.gcov
	rm -f *.DS_Store
	rm -f RunBoggleSolver
	rm -f TestBoggleSolver
	rm -f TestBoggleSolver.out
	rm -f RunBoggleSolver.out

RunBoggleSolver: BoggleSolver.h BoggleSolver.c++ RunBoggleSolver.c++
	g++ $(CXXFLAGS) $(GCOVFLAGS) BoggleSolver.c++ RunBoggleSolver.c++ -o RunBoggleSolver

RunBoggleSolver.out: RunBoggleSolver
	./RunBoggleSolver > RunBoggleSolver.out

TestBoggleSolver: BoggleSolver.h BoggleSolver.c++ TestBoggleSolver.c++
	g++ $(CXXFLAGS) $(GCOVFLAGS) BoggleSolver.c++ TestBoggleSolver.c++ -o TestBoggleSolver $(TESTFLAGS)

TestBoggleSolver.out: TestBoggleSolver
	valgrind ./TestBoggleSolver > TestBoggleSolver.out 2>&1
	gcov -b BoggleSolver.c++ | grep -A 5 "File 'BoggleSolver.c++'" >> TestBoggleSolver.out
	gcov -b TestBoggleSolver.c++ | grep -A 5 "File 'TestBoggleSolver.c++'" >> TestBoggleSolver.out
