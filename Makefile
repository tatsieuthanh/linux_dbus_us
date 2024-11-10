TARGET = lib/libshareprocess.so

SRC = src/processA_dbus_us.c src/processB_dbus_us.c 

OBJ = $(SRC:%.c=%.o)

CC = gcc

CFLAGS = -Wall -Wextra -O2 -fPIC -Iinclude

LDFLAGS = -shared

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -o $(TARGET) $(OBJ)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(TARGET) $(OBJ)