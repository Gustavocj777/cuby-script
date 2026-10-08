---

## Part 3: Makefile (Build Automation)

```makefile
CC = gcc
CFLAGS = -Wall -Wextra -O3
TARGET = cuby
SRC = main.c

all: $(TARGET)

$(TARGET):$(SRC)
	$(CC)$(CFLAGS) $(SRC) -o$(TARGET)
	@echo "[Build] Cuby / Mini-Geny compilado com sucesso!"

clean:
	rm -f $(TARGET)
	rm -rf gen/
	@echo "[Clean] Ambiente limpo."

.PHONY: all clean
