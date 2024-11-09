# Tên của chương trình
TARGET = main

# Các tệp nguồn
SRC = main.c

# Thư viện chia sẻ
LIB = ../libshareprocess.so

# Trình biên dịch
CC = gcc

# Các cờ biên dịch
CFLAGS = -Wall -Wextra -O2 -I../include

# Các cờ liên kết
LDFLAGS = -L.. -lshareprocess

# Quy tắc mặc định
all: $(TARGET)

# Quy tắc biên dịch chương trình
$(TARGET): $(SRC) $(LIB)
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) -o $(TARGET)

# Quy tắc dọn dẹp
clean:
	rm -f $(TARGET)