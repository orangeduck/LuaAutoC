CC=gcc

C_FILES= $(wildcard src/*.c)
OBJ_FILES= $(addprefix obj/,$(notdir $(C_FILES:.c=.o)))

PLATFORM = $(shell uname)

ifeq ($(findstring Linux,$(PLATFORM)),Linux)
	OUT= liblua_autoc.so
	INCS= -I ./include -I/usr/include/lua52
	CFLAGS= $(INCS) -std=gnu99 -Wall -Werror -Wno-unused -O3 -g -fPIC
	LFLAGS= -llua5.2
	DISTUTIL=
endif

ifeq ($(findstring MINGW,$(PLATFORM)),MINGW)
	OUT= lua_autoc.dll
	INCS= -I ./include -I./lua52/include
	CFLAGS= $(INCS) -std=gnu99 -Wall -Werror -Wno-unused -O3 -g
	LFLAGS= -g -L./lua52 -L./ -llua52 -lmingw32
	DISTUTIL= -c mingw32
endif

all: library

library: $(OBJ_FILES)
	$(CC) $(OBJ_FILES) $(LFLAGS) -shared -o $(OUT)
	
obj/%.o: src/%.c | obj
	$(CC) $< -c $(CFLAGS) -o $@
	
obj:
	mkdir obj
	
clean:
	rm $(OBJ_FILES)
