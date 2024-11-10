#Complier
CC = gcc

# Name of the target: libshareprocess_ab.so
LIB_TARGET = lib/libshareprocess_ab.so

# source files
SRC = src/processA_dbus_us.c src/processB_dbus_us.c 

OBJ = $(SRC:%.c=%.o)

CFLAGS = -Wall -Wextra -O2 -fPIC -Iinclude

LDFLAGS = -shared

# Compile the target
all: $(LIB_TARGET) 
	$(MAKE) -C src

$(LIB_TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -o $(LIB_TARGET) $(OBJ)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

#clean
clean:
	rm -f $(LIB_TARGET) $(OBJ) 
	$(MAKE) -C src clean