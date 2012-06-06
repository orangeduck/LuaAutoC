CC=gcc
AR=ar

C_FILES= $(wildcard src/*.c)
OBJ_FILES= $(addprefix obj/,$(notdir $(C_FILES:.c=.o)))

PLATFORM = $(shell uname)

ifeq ($(findstring Linux,$(PLATFORM)),Linux)
	OUT= liblautoc.so
	INCS= -I ./include -I/usr/include/lua52
	CFLAGS= $(INCS) -std=gnu99 -Wall -Werror -Wno-unused -O3 -g -fPIC
	LFLAGS= -llua5.2
	DISTUTIL=
endif

ifeq ($(findstring MINGW,$(PLATFORM)),MINGW)
	OUT= lautoc.dll
	INCS= -I ./include -I./lua52/include
	CFLAGS= $(INCS) -std=gnu99 -Wall -Werror -Wno-unused -O3 -g
	LFLAGS= -g -L./lua52 -L./ -llua52 -lmingw32
	DISTUTIL= -c mingw32
endif

all: demo_func demo_struct demo_convert demo_mod demo_embed dlibrary slibrary

dlibrary: $(OBJ_FILES)
	$(CC) $(OBJ_FILES) $(LFLAGS) -shared -o $(OUT)

slibrary: $(OBJ_FILES)
	$(AR) rcs liblautoc.a $(OBJ_FILES)
  
demo_func: $(OBJ_FILES)
	$(CC) demos/demo_func.c $(OBJ_FILES) $(CFLAGS) $(LFLAGS) -o demos/$@
 
demo_struct: $(OBJ_FILES)
	$(CC) demos/demo_struct.c $(OBJ_FILES) $(CFLAGS) $(LFLAGS) -o demos/$@
  
demo_convert: $(OBJ_FILES)
	$(CC) demos/demo_convert.c $(OBJ_FILES) $(CFLAGS) $(LFLAGS) -o demos/$@
  
demo_mod: $(OBJ_FILES)
	$(CC) demos/demo_mod.c $(OBJ_FILES) $(CFLAGS) $(LFLAGS) -o demos/$@
  
demo_embed: $(OBJ_FILES)
	$(CC) demos/demo_embed.c $(OBJ_FILES) $(CFLAGS) $(LFLAGS) -o demos/$@
  
obj/%.o: src/%.c | obj
	$(CC) $< -c $(CFLAGS) -o $@
	
obj:
	mkdir obj
	
clean:
	rm $(OBJ_FILES)
