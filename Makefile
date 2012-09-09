CC=gcc
AR=ar

C_FILES= $(wildcard src/*.c)
OBJ_FILES= $(addprefix obj/,$(notdir $(C_FILES:.c=.o)))

PLATFORM = $(shell uname)

ifeq ($(findstring Linux,$(PLATFORM)),Linux)
	DOUT= liblautoc.so
	SOUT= liblautoc.a
	INCS= -I ./include -I/usr/include/lua5.2
	CFLAGS= $(INCS) -std=gnu99 -Wall -Werror -Wno-unused -O3 -g -fPIC
	LFLAGS= -llua5.2
	DISTUTIL=
endif

ifeq ($(findstring Darwin,$(PLATFORM)),Darwin)
	DOUT= liblautoc.so
	SOUT= liblautoc.a
	INCS= -I ./include -I/usr/include/lua5.2
	CFLAGS= $(INCS) -std=gnu99 -Wall -Werror -Wno-unused -O3 -g -fPIC
	LFLAGS= -llua5.2
	DISTUTIL=
endif

ifeq ($(findstring MINGW,$(PLATFORM)),MINGW)
	DOUT= lautoc.dll
	SOUT= lautoc.lib
	INCS= -I ./include -I./lua52/include
	CFLAGS= $(INCS) -std=gnu99 -Wall -Werror -Wno-unused -O3 -g
	LFLAGS= -g -L./lua52 -L./ -llua52 -lmingw32
	DISTUTIL= -c mingw32
endif

# Library

all: $(DOUT) $(SOUT)

$(DOUT): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) $(LFLAGS) -shared -o $(DOUT)

$(SOUT): $(OBJ_FILES)
	$(AR) rcs $(SOUT) $(OBJ_FILES)
  
obj/%.o: src/%.c | obj
	$(CC) $< -c $(CFLAGS) -o $@
	
obj:
	mkdir obj
  
# Demos

demos: demo_func demo_struct demo_convert demo_mod demo_embed
  
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
  
# Clean
	
clean:
	rm $(OBJ_FILES)
