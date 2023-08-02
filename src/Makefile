CC = gcc
CFLAGS = -std=c11 -Wall -Werror -Wextra

all: s21_matrix.a

s21_matrix: 
	$(CC) $(CFLAGS) $(C11) s21_*.c -o s21_matrix

test: s21_matrix.a
	$(CC) -fsanitize=address -lcheck test.c s21_matrix.a -o test.out && ./test.out

# Для корректной работы установи lcov: brew install lcov
gcov_report: coverage run_coverage lcov genhtml open

coverage:
	$(CC) --coverage test.c s21_matrix.c -o test -lcheck
run_coverage:
	./test
lcov:
	lcov -t "Core" -o s21_test.info -c -d .
genhtml:
	genhtml -o report s21_test.info
open:
	open ./report/index.html

s21_matrix.a: clean s21_matrix.o
	ar rc s21_matrix.a s21_*.o

s21_matrix.o:
	$(CC) -c $(FLAGS) s21_*.c

style:
	cp clang/.clang-format .clang-format
	clang-format -n *.c *.h
	rm .clang-format

clean:
	rm -rf s21_matrix *.o *.a *.info *.gcda *.gcno *.out test report/

rebuild: clean all
