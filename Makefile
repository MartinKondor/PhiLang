
prototype:
	@python prototype.py examples/test.phi

compile:
	@gcc src/* -I "include" -o bin/phi.exe
	@bin/phi.exe examples/test.phi
