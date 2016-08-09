.PHONY:clean

clean:
	cd ./src/; make clean
	cd ./tests/; make clean

.PHONY: tests

tests:
	cd ./tests; make; make tests;
