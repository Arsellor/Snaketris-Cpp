EXE = snaketris
CPP = g++
SDL_INC = `sdl2-config --cflags`
SDL_LIB = `sdl2-config --libs`
CFLAGS = -Wall -Wextra -O2 $(SDL_INC)
LIBS = $(SDL_LIB)

OBJ = \
	obj/window.o \
	obj/world.o \
	obj/snake.o \
	obj/view.o \
	obj/game.o

all: $(EXE)

obj:
	mkdir -p obj

obj/window.o: src/window.cpp src/window.hpp | obj
	$(CPP) $(CFLAGS) -c src/window.cpp -o $@

obj/world.o: src/world.cpp src/world.hpp src/enum.hpp | obj
	$(CPP) $(CFLAGS) -c src/world.cpp -o $@

obj/snake.o: src/snake.cpp src/snake.hpp src/enum.hpp | obj
	$(CPP) $(CFLAGS) -c src/snake.cpp -o $@

obj/view.o: src/view.cpp src/view.hpp src/window.hpp src/world.hpp src/snake.hpp | obj
	$(CPP) $(CFLAGS) -c src/view.cpp -o $@

obj/game.o: src/game.cpp src/game.hpp src/world.hpp src/snake.hpp src/view.hpp | obj
	$(CPP) $(CFLAGS) -c src/game.cpp -o $@

$(EXE): $(OBJ) src/main.cpp
	$(CPP) $(CFLAGS) $(OBJ) src/main.cpp -o $(EXE) $(LIBS)

run: $(EXE)
	./$(EXE)

clean:
	rm -f obj/*.o $(EXE)

.PHONY: all run clean
