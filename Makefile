
ccflags = -std=c++17 -I"header" -static-libstdc++
inputfile = examples/test.phi


build:
	@g++ source/phi.cpp $(ccflags) -o bin/phi.exe

run:
	@bin/phi.exe $(inputfile)
    
test:
	$(build)
	$(run)
    