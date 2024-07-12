CC_WINDOWS = i686-w64-mingw32-gcc-win32 

WARNINGS = -Werror -Wfatal-errors -Wpedantic
FLAGS = -fPIC -lm


out_exe: main.o zmath.so
	$(CC_WINDOWS) $(WARNINGS) -o out.exe main.o zmath.so

main.o: main.c
	$(CC_WINDOWS) $(WARNINGS) -c main.c

zmath.so: zmath.o
	$(CC_WINDOWS) $(WARNINGS) -shared -o zmath.so zmath.o

zmath.o: zmath.c
	$(CC_WINDOWS) $(WARNINGS) -fPIC -lm -c zmath.c

clean:
	rm -f *.o *.exe *.so