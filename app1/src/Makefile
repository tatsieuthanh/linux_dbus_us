# Complier
CC = gcc

# Name of the target: main
TARGET = ../out/main

# soure files
SRC = main.c

OBJ = $(SRC:%.c=%.o)

# shared library
LIB = ../lib/libshareprocess_ab.so

# Comnpile flags
CFLAGS = -Wall -Wextra -O2 -I../include

# Linker flags
LDFLAGS = -L../lib -lshareprocess_ab

# Compile the target
all: $(TARGET)

$(TARGET): $(OBJ) $(LIB)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(TARGET) 

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# clean
clean:
	rm -f $(TARGET) $(OBJ)