
build:
	@g++ src/phi.cpp -o bin/phi.exe

run:
	@bin/phi.exe examples/test.phi

test:
	@g++ src/phi.cpp -o bin/phi.exe
	@bin/phi.exe examples/test.phi
