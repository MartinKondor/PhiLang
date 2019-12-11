
prototype:
	@python py/phi.py examples/test.phi

build:
	@gcc src/* -I "include" -o bin/phi.exe
	
test:
	@gcc src/* -I "include" -o bin/phi.exe
	@bin/phi.exe examples/short_test.phi
