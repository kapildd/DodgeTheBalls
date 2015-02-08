CXX=g++
CPPFLAGS=-Wall 
LDLIBS=-lglfw -lm -lGL -lGLU -lglut

SRCS=main.cpp
OBJ=obj/Release/DodgeTheBalls.o

all: DodgeTheBalls

DodgeTheBalls: $(OBJ)
	$(CXX) $(CPPFLAGS) -o bin/Release/DodgeTheBalls $(OBJ) $(LDLIBS)

$(OBJ): main.cpp main.h vmath.h
	$(CXX) $(CPPFLAGS) -c main.cpp -o obj/Release/DodgeTheBalls.o

clean:
	rm -f bin/Release/DodgeTheBalls obj/Release/DodgeTheBalls.o
