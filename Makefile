CC = g++
OBJS = main.cpp
OBJ_NAME = run
FLAGS = -w
LIBS = -lSDL2

all:
	$(CC) $(OBJS) $(LIBS) $(FLAGS) -o $(OBJ_NAME)
