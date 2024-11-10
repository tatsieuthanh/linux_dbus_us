# Complier
CC = gcc

# Name of the target: main
TARGET = ../out/main

# souece files
SRC = main.c

OBJ = $(SRC:%.c=%.o)

# shared library
LIB = ../lib/libshareprocess_cd.so

# Comnpile flags
CFLAGS = -Wall -Wextra -O2 -I../include

# Linker flags
LDFLAGS = -L../lib -lshareprocess_cd

# 
all: $(TARGET)

# Quy tắc biên dịch chương trình
$(TARGET): $(OBJ) $(LIB)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(TARGET)

# Quy tắc dọn dẹp
clean:
	rm -f $(TARGET) $(OBJ)