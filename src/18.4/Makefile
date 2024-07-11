CC_LINUX = gcc
CC_WINDOWS = i686-w64-mingw32-gcc-win32 

TARGET_LINUX = lin-cross
TARGET_WINDOWS = win-cross.exe

SRC = cross_compile.c
WARNINGS = -Werror -Wfatal-errors -Wpedantic
FLAGS = -lm -Os -s 

BMP_LELF = linux-elf.bmp
BMP_LEXE = linux-exe.bmp
BMP_WELF = windows-elf.bmp
BMP_WEXE = windows-exe.bmp

all: $(TARGET_LINUX) $(TARGET_WINDOWS)

$(TARGET_LINUX): $(SRC)
	$(CC_LINUX) $(WARNINGS) -o $@ $^ $(FLAGS)

$(TARGET_WINDOWS): $(SRC)
	$(CC_WINDOWS) $(WARNINGS) -o $@ $^ $(FLAGS)

clean:
	rm -f $(TARGET_LINUX) $(TARGET_WINDOWS) $(BMP_LELF) $(BMP_LEXE) $(BMP_WELF) $(BMP_WEXE)