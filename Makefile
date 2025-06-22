CC = gcc
CFLAGS = -Wall -static
TARGET = cfget.exe
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
INCLUDE = -Iinclude
LIBS = -lwininet -lshell32

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
