FLAGS = --std=c++11 -Wall -Werror -pedantic -g
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lboost_system -lboost_filesystem
CC = g++
EXE = xts
OBJECTS = line.o system.o error_msgr.o ruler.o mouse.o command.o \
    graphic_system.o processor.o  text_buffer.o gui.o main.o

.SECONDARY:
.PHONY: clean

$(EXE): $(OBJECTS)
	$(CC) $(FLAGS) $(OBJECTS) $(LIBS) -o $(EXE)

%.o: %.cpp *.hpp config.hpp
	$(CC) $(FLAGS) -c $<

clean:
	rm -rf *.o $(EXE)
