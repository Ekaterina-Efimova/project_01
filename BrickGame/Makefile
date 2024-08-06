CC = g++

CFLAGS = -Wall -Wextra -Werror -std=c++17
GFLAGS = -fprofile-arcs -ftest-coverage
TFLAGS = -lgtest -lgtest_main

TETRIS_LIB = tetris.a
TETRIS_SRC = $(wildcard ./brick_game/tetris/*.c)
TETRIS_OBJ = $(TETRIS_SRC:.c=.o)

SNAKE_LIB = snake.a 
SNAKE_SRC = brick_game/snake/snake_controller.cpp brick_game/snake/snake_model.cpp
SNAKE_OBJ =  $(SNAKE_SRC:.cpp=.o)

MAIN_SRC = brick_game/brick_game_ncurses.cpp
MAIN_OBJ = $(MAIN_SRC:.cpp=.o)

COMMON_SRC =$(wildcard ./common/*.cpp) 
COMMON_OBJ = $(COMMON_SRC:.cpp=.o)
COMMON_LIB = common.a

EXEC = build/brick_game

CLI_LIB = interface.a
CLI_SRC = gui/cli/interface.c gui/cli/bg_objects.c
CLI_OBJ = $(CLI_SRC:.c=.o)

TEST_SRC = tests/*cpp
TEST_OBJ = $(TEST_SRC:.cpp=.o)

all: clear install run

test: clear $(TEST_OBJ) $(SNAKE_LIB) $(TETRIS_LIB) $(COMMON_OBJ)
	@$(CC) $(CFLAGS) $(TEST_OBJ) -o test $(COMMON_OBJ) -L. -l:$(SNAKE_LIB) -l:$(TETRIS_LIB)  $(TFLAGS)
	@rm -f $(TEST_OBJ) 
	@./test --gtest_brief=1

%.o: %.cpp
	@$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(SNAKE_LIB): $(SNAKE_OBJ)
	@ar rcs $(SNAKE_LIB) $(SNAKE_OBJ)
	@ranlib $(SNAKE_LIB)
	@rm -f $(SNAKE_OBJ)

$(TETRIS_LIB): $(TETRIS_OBJ) 
	@ar rcs $(TETRIS_LIB) $(TETRIS_OBJ) 
	@ranlib $(TETRIS_LIB)
	@rm -f $(TETRIS_OBJ) 

$(COMMON_LIB): $(COMMON_OBJ)
	@ar rcs $(COMMON_LIB) $(COMMON_OBJ)
	@ranlib $(COMMON_LIB)
	@rm -f $(COMMON_OBJ)

install: clear clean  install_desktop install_cli

install_cli: $(MAIN_OBJ)  $(CLI_OBJ) $(SNAKE_LIB) $(TETRIS_LIB) $(COMMON_OBJ)
	@$(CC) $(CFLAGS) $(MAIN_OBJ) $(CLI_OBJ) -o $(EXEC) -L. -l:$(SNAKE_LIB) -l:$(TETRIS_LIB) -lm -lncursesw
	@rm -f $(MAIN_OBJ)  $(CLI_OBJ) $(TETRIS_OBJ) $(SNAKE_OBJ) $(COMMON_OBJ)

install_desktop: clear clean clean_build $(SNAKE_LIB) $(TETRIS_LIB) 
	mkdir build
	cd build && cmake ../ && make desktopBrickGame

run_desktop: install_desktop
	./build/desktopBrickGame

run_cli: install_cli
	./$(EXEC)

style_check: clear
	@cppcheck --enable=all --suppress=missingIncludeSystem brick_game/*.cpp brick_game/tetris/*.c common/*.c gui/cli/*.c gui/desktop/*.cpp gui/desktop/*.h gui/cli/*.h brick_game/snake/*.cpp brick_game/snake/*.h brick_game/snake/*.cpp brick_game/snake/*.hpp brick_game/tetris/*.h 
	@cp ../materials/linters/.clang-format .
	@clang-format -n brick_game/*.cpp brick_game/tetris/*.c common/*.c gui/cli/*.c gui/desktop/*.cpp gui/desktop/*.h gui/cli/*.h brick_game/snake/*.cpp brick_game/snake/*.h brick_game/snake/*.cpp brick_game/snake/*.hpp brick_game/tetris/*.h 

leak_check: clear
	@valgrind --tool=memcheck --leak-check=yes ./test

clean:
	@rm -f $(SNAKE_OBJ) $(SNAKE_LIB) $(TEST_OBJ) $(MAIN_OBJ) $(COMMON_OBJ)  $(CLI_OBJ) $(TETRIS_OBJ) $(TETRIS_LIB) test 
	@rm -f *.gcno *.gcda *.gcov

add_coverage:
	$(eval CFLAGS:=$(CFLAGS) $(GFLAGS))

re: clean all

clear:
	@clear

gcov_report: clean add_coverage $(SNAKE_OBJ) $(SNAKE_LIB) 
	@$(CC) $(CFLAGS) -o gcov_r $(TEST_SRC) -L. -l:$(SNAKE_LIB) $(TFLAGS)
	@mkdir coverage_report
	@./gcov_r
	@python3 -m gcovr -r . --html --html-details -o coverage_report/index.html --exclude test
	@rm -f *.gcno *.gcda

clean_build:
	@rm -rf build