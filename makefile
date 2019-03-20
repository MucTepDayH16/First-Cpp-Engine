SDL=`sdl2-config --cflags --libs` -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf
LUA=-I/usr/local/include -L/usr/local/lib -llua -ldl
GCC=g++
FLAGS=-c -Wall -fopenmp
NAME=Simulator
G=git

all: const.o graphic.o input.o input_listener.o entity.o state.o start.o execute.o main.o
	$(GCC) main.o execute.o state.o start.o const.o graphic.o input.o input_listener.o entity.o -o $(NAME) $(SDL) $(LUA)

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

const.o: const.h const.cpp
	$(GCC) $(FLAGS) const.h const.cpp $(LUA)

entity.o: entity.h entity.cpp
	$(GCC) $(FLAGS) entity.h entity.cpp
