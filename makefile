SDL=`sdl2-config --cflags --libs` -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf
GCC=g++
FLAGS=-c -Wall
NAME=Simulator
G=git

all: graphic.o input.o input_listener.o entity.o state.o start.o execute.o main.o
	$(GCC) main.o execute.o state.o start.o graphic.o input.o input_listener.o entity.o -o $(NAME) $(SDL)
	rm -f *.o *.gch
	./$(NAME)

main.o: mainheader.h main.cpp
	$(GCC) $(FLAGS) mainheader.h main.cpp

execute.o: execute.h execute.cpp
	$(GCC) $(FLAGS) execute.h execute.cpp

state.o: state.h state.cpp
	$(GCC) $(FLAGS) state.h state.cpp

start.o: start.cpp
	$(GCC) $(FLAGS) start.cpp

graphic.o: graphic.h graphic.cpp
	$(GCC) $(FLAGS) graphic.h graphic.cpp $(SDL)

input.o: input.h input.cpp
	$(GCC) $(FLAGS) input.h input.cpp $(SDL)

input_listener.o: input_listener.cpp
	$(GCC) $(FLAGS) input_listener.cpp $(SDL)

entity.o: entity.h entity.cpp
	$(GCC) $(FLAGS) entity.h entity.cpp
