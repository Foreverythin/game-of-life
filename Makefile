
# code details

EXE_DIR = bin
EXE = $(EXE_DIR)/GameOfLife

SRC_DIR = src
SRC = main.c $(SRC_DIR)/fileIO.c $(SRC_DIR)/game.c $(SRC_DIR)/utility.c $(SRC_DIR)/interface.c

INCLUDE_DIR = ./include
LIB_DIR = ./lib
LIB1 = SDL2
LIB2 = SDL2_image
#LIB_DIR1 = /opt/homebrew/Cellar/sdl2/2.0.20/lib
#LIB_DIR2 = /opt/homebrew/Cellar/sdl2_image/2.0.5/lib
#LIB1 = SDL2
#LIB2 = SDL2_image
LINKS = -L$(LIB_DIR) -l$(LIB1) -L$(LIB_DIR) -l$(LIB2)

# generic build details

CC =     gcc
CFLAGS = -Wall -O

# compile to  object code

OBJ= $(SRC:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

# build executable

$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $(EXE) $(LINKS)
all: $(EXE)
.PHONY: all

# clean up compilation

clean:
	rm -f $(OBJ) $(EXE)

# dependencies

main.o: main.c $(INCLUDE_DIR)/fileIO.h $(INCLUDE_DIR)/game.h $(INCLUDE_DIR)/interface.h
fileIO.o: $(SRC_DIR)/fileIO.c $(INCLUDE_DIR)/fileIO.h
game.o: $(SRC_DIR)/game.c $(INCLUDE_DIR)/game.h $(INCLUDE_DIR)/utility.h $(INCLUDE_DIR)/interface.h $(INCLUDE_DIR)/fileIO.h
utility.o: $(SRC_DIR)/utility.c $(INCLUDE_DIR)/utility.h
interface.o: $(SRC_DIR)/interface.c $(INCLUDE_DIR)/interface.h
