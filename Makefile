CC = g++
OBJS = src/main.cpp src/draw.cpp
HEADERS = ./src/
OBJ_NAME = run
FLAGS = -w
LIBS = -lSDL2

all:
	$(CC) $(OBJS) -I$(HEADERS)  $(LIBS) $(FLAGS) -o $(OBJ_NAME)
