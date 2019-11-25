
compile:
	@gcc src/* -Ihpp -o bin/phi.exe
	@bin/phi.exe examples/test.phi
