CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++17
GFLAGS = -fprofile-arcs -ftest-coverage
TFLAGS = -lgtest -lgtest_main
LIB_NAME = s21_matrix_oop.a
LIB_SRC = $(wildcard *.cpp)
LIB_OBJ = $(LIB_SRC:.cpp=.o)
TEST_SRC = tests/test.cpp
TEST_OBJ = $(TEST_SRC:.cpp=.o)

all: clear $(LIB_NAME)

test: clear $(TEST_OBJ) $(LIB_NAME)
	@$(CC) $(CFLAGS) $(TEST_OBJ) -o test -L. -l:$(LIB_NAME) $(TFLAGS)
	@rm -f $(TEST_OBJ)
	@./test --gtest_brief=1

%.o: %.cpp
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIB_NAME): clear $(LIB_OBJ)
	@ar rcs $(LIB_NAME) $(LIB_OBJ)
	@ranlib $(LIB_NAME)
	@rm -f $(LIB_OBJ)


style_check: clear
	@cppcheck --enable=all --suppress=missingIncludeSystem *.cpp
	@cp ../materials/linters/.clang-format .
	@clang-format -n *.cpp *.h tests/*

leak_check: clear
	@valgrind --tool=memcheck --leak-check=yes ./test

clean:
	@rm -f $(LIB_OBJ) $(LIB_NAME) $(TEST_OBJ) test 

add_coverage:
	$(eval CFLAGS:=$(CFLAGS) $(GFLAGS))

re: clean all

clear:
	@clear

gcov_report: clean add_coverage $(LIB_OBJ) $(LIB_NAME) 
	@$(CC) $(CFLAGS) -o gcov_r $(TEST_SRC) -L. -l:$(LIB_NAME) $(TFLAGS)
	@mkdir coverage_report
	@./gcov_r
	@python3 -m gcovr -r . --html --html-details -o coverage_report/index.html --exclude test
	@rm -f *.gcno *.gcda