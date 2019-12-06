
prototype:
	@python py/main.py examples/test.phi

build:
	@gcc src/* -I "include" -o bin/phi.exe
	@bin/phi.exe examples/test.phi
