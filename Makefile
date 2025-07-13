CC = g++
CFLAGS = -Wall -Werror -Wextra -std=c++17

all: gcov_report

test:
	$(CC) $(CFLAGS) tests/*.cpp -lgtest -pthread -o test_all
	./test_all

rebuild:
	make clean
	make gcov_report

gcov_report:
	mkdir output
	$(CC) $(CFLAGS) tests/*.cpp -lgtest -pthread -o output/test_gcov --coverage
	./output/test_gcov
	lcov --directory ./output --capture --output-file coverage.info
	lcov --remove coverage.info '/usr/*' -o coverage.info
	mkdir report
	genhtml coverage.info --output-directory ./report
	xdg-open report/index.html

clang:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n *.h tests/*.cpp tests/*.h containers/*.h containers/*.tpp
clean:
	rm -f *.o *.a *.gcno *.gcda *.gcov *.info test_gcov test_all main
	rm -fr report
	rm -fr output

valgrind:
	valgrind  --tool=memcheck --track-fds=yes --trace-children=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./test_all

.PHONY: all clean rebuild gcov_report test clang valgrind