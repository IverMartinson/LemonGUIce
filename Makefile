COMPILER=gcc
FLAGS_ALL=-g -Wall -Wextra -Wno-unused-variable -Wno-unused-parameter
FLAGS_EXAMPLE=-Lbuilds/ -llemonguice -lsourparse -lpitmap -Wl,-rpath=builds/ -lm -lSDL2
FLAGS_LIB=-fPIC -shared -lc -lSDL2 -lm 

main.bin: lemonguice.so pitmap.so sourparse.so
	$(COMPILER) $(FLAGS_ALL) src/launch_program/main.c -o builds/main.bin $(FLAGS_EXAMPLE) 

lemonguice.so:
	$(COMPILER) $(FLAGS_ALL) src/library/main.c -o builds/liblemonguice.so $(FLAGS_LIB) 

sourparse.so:
	cp src/libraries/libsourparse.so builds/

pitmap.so:
	cp src/libraries/libpitmap.so builds/

clean:
	rm builds/*
