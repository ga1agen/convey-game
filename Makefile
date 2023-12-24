LIBS_FLAGS = -lmingw32 -mwindows -lSDL2main -lSDL2
CFLAGS = -Wall -g

all: test.exe

clean:
		$(RM) *.o
		$(RM) *.exe

test.exe: main.o convey.o
		gcc $^ $(LIBS_FLAGS) -o $@

main.o: main.c
		gcc -x c $^ $(CFLAGS) -c -o $@

convey.o: convey.c
		gcc -x c $^ $(CFLAGS) -c -o $@  