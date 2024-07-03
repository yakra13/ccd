# gcc -c zmath.c -o zmath.o -lm
# gcc -c main.c -o main.o

# gcc main.o zmath.o -o test

CC = gcc
CFLAGS = -Wall
LDFLAGS = -lm
OBJFILES = zmath.o main.o
TARGET = test

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET)