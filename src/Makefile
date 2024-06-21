PROJECT_NAME = s21_matrix
CC = gcc
OS = $(shell uname)

ifeq ($(OS), Linux)
	FLAGS = -Werror -Wall -Wextra -std=c11
	TEST_FLAGS = -lcheck -pthread -lrt -lm -lsubunit
else
	FLAGS = -Werror -Wall -Wextra -std=c11
	TEST_FLAGS = -lcheck
endif

all: $(PROJECT_NAME).a

$(PROJECT_NAME).a:
	$(CC) $(FLAGS) -c s21_matrix.c -o s21_matrix.o
	ar rcs $(PROJECT_NAME).a s21_matrix.o


test:$(PROJECT_NAME).a
	$(CC) $(FLAGS) tests/*.c $(PROJECT_NAME).a -o test $(TEST_FLAGS)
	./test

check: test
	cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config *.c *.h
	make test
	leaks -atExit -- test

gcov_report: clean
	$(CC) $(FLAGS) -c tests/*.c
	$(CC) $(FLAGS) --coverage *.o s21_matrix.c -o test $(TEST_FLAGS)
	./test
	lcov -d ./ --capture --output-file $(PROJECT_NAME).info
	genhtml $(PROJECT_NAME).info --output-directory report
	open report/index.html
	
style: clean
	cp ../materials/linters/.clang-format ./
	clang-format -n *.c test/*.c
	clang-format -n *.h test/*.h
	rm -rf .clang-format

clang: clean
	cp ../materials/linters/.clang-format ./
	clang-format -i *.c test/*.c
	clang-format -i *.h	test/*.h
	rm -rf .clang-format

clean:
	rm -rf *.a *.out *.o test *.html *.css
	rm -rf *.g* *.info report
