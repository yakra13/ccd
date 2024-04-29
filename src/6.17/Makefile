CC = gcc
CFLAGS = -Wall
LDFLAGS = -lm
OBJFILES = vector3.o main.o
TARGET = vectors

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET)