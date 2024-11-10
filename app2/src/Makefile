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
CFLAGS = -Wall -Wextra -O2 -I../include -I/usr/include/dbus-1.0/ -I/usr/lib/x86_64-linux-gnu/dbus-1.0/include/
# Linker flags
LDFLAGS = -L../lib -lshareprocess_cd  -ldbus-1

# 
all: $(TARGET)

# Quy tắc biên dịch chương trình
$(TARGET): $(OBJ) $(LIB)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(TARGET)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Quy tắc dọn dẹp
clean:
	rm -f $(TARGET) $(OBJ)