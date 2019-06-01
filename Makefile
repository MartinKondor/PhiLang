
ccflags = -std=c++17 -I"header" -static-libstdc++
inputfile = examples/test.phi


build:
	@g++ source/phi.cpp $(ccflags) -o bin/phi.exe

run:
	@g++ source/phi.cpp $(ccflags) -o bin/phi.exe
	@bin/phi.exe $(inputfile)
    
test:
	@g++ tests/phi.cpp $(ccflags) -o bin/phitest.exe
	@./bin/phitest.exe
    