
CC = gcc

LIB_TARGET = lib/libshareprocess_cd.so

SRC = src/processC_dbus_us.c src/processD_dbus_us.c 

OBJ = $(SRC:%.c=%.o)

CFLAGS = -Wall -Wextra -O2 -fPIC -Iinclude

LDFLAGS = -shared

all: $(LIB_TARGET)
	$(MAKE) -C src


$(LIB_TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -o $(LIB_TARGET) $(OBJ)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(LIB_TARGET) $(OBJ)
	$(MAKE) -C src clean