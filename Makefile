a.out: *.c *.h
	gcc *.c -Wall

.PHONY: test
test: a.out
	./a.out test.lox
