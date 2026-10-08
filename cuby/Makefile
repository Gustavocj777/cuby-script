CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
TARGET = cuby-mux

SRC = src/main.c

all: $(TARGET)

$(TARGET): $(SRC)
$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
rm -f $(TARGET)

.PHONY: all clean
