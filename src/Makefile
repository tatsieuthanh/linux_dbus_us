# Name of the target: main
TARGET = main

# souece files
SRC = main.c

# shared library
LIB = ../lib/libshareprocess.so

# Complier
CC = gcc

# Comnpile flags
CFLAGS = -Wall -Wextra -O2 -I../include

# Linker flags
LDFLAGS = -L../lib -lshareprocess

# 
all: $(TARGET)

# Quy tắc biên dịch chương trình
$(TARGET): $(SRC) $(LIB)
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) -o $(TARGET)

# Quy tắc dọn dẹp
clean:
	rm -f $(TARGET)