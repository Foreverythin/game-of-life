
# code details

EXE_DIR = bin
EXE = $(EXE_DIR)/GameOfLife

SRC_DIR = ./src
SRC = main.c

# generic build details

CC =     gcc
CFLAGS = -Wall -O

# compile to  object code

OBJ= $(SRC:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $< -arch x86_64

# build executable

$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $(EXE) -F/Library/Frameworks -framework SDL2_image -framework SDL2 -arch x86_64

all: $(EXE)
.PHONY: all

# clean up compilation

clean:
	rm -f $(OBJ) $(EXE)

# dependencies

main.o: main.c
