TARGET = libshareprocess.so

SRC = src/processA_dbus_us.c src/processB_dbus_us.c 

CC = gcc

CFLAGS = -Wall -Wextra -O2 -fPIC -Iinclude

LDFLAGS = -shared

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)