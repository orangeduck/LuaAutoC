-include config.mk

PLATFORM?= $(shell uname)

CC?=gcc
AR?=ar

LAC_CPPFLAGS= -I./include $(LUA_INCLUDE_DIR)
LAC_CFLAGS= -std=gnu99 -Wall -Werror -Wno-unused -O3 -g
LAC_LDFLAGS= $(LUA_LIBRARY_DIR)
LAC_LIBS= $(LUA_LIBRARY)

DEMOS= func struct convert mod embed
DEMO_TARGETS= $(DEMOS:%=demos/demo_%$(EXE_SUFFIX))
C_FILES= $(wildcard src/*.c)
OBJ_FILES= $(addprefix obj/,$(notdir $(C_FILES:.c=.o)))
SHARED_LIB= $(SHARED_LIB_PREFIX)lautoc$(SHARED_LIB_SUFFIX)
STATIC_LIB= $(STATIC_LIB_PREFIX)lautoc$(STATIC_LIB_SUFFIX)

ifeq ($(findstring Linux,$(PLATFORM)),Linux)
	LUA_INCLUDE_DIR?= -I/usr/include/lua5.2
	LUA_LIBRARY?= -llua5.2
	LAC_CFLAGS+= -fPIC
	LAC_LDFLAGS+= -fPIC
	SHARED_LIB_PREFIX:=lib
	SHARED_LIB_SUFFIX:=.so
	STATIC_LIB_PREFIX:=lib
	STATIC_LIB_SUFFIX:=.a
	EXE_SUFFIX:=
endif

ifeq ($(findstring MINGW,$(PLATFORM)),MINGW)
	LUA_INCLUDE_DIR?= -I./lua52/include
	LUA_LIBRARY_DIR?= -L./lua52
	LUA_LIBRARY?= -llua52
	LAC_LDFLAGS+= -L.
	LAC_LIBS+= -lmingw32
	SHARED_LIB_PREFIX:=
	SHARED_LIB_SUFFIX:=.dll
	STATIC_LIB_PREFIX:=
	STATIC_LIB_SUFFIX:=.lib
	EXE_SUFFIX:=.exe
endif

all: $(DEMO_TARGETS) $(SHARED_LIB) $(STATIC_LIB)

$(SHARED_LIB): $(OBJ_FILES)
	$(CC) $(LAC_LDFLAGS) $(LDFLAGS) -shared -o $@ $^ $(LAC_LIBS)

$(STATIC_LIB): $(OBJ_FILES)
	$(AR) rcs $@ $^
  
$(DEMO_TARGETS): demos/demo_%$(EXE_SUFFIX): obj/demo_%.o $(STATIC_LIB)
	$(CC) $(LAC_LDFLAGS) $(LDFLAGS) -o $@ $^ $(LAC_LIBS)
 
obj/%.o: src/%.c | obj
	$(CC) $(LAC_CPPFLAGS) $(LAC_CFLAGS) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

obj/%.o: demos/%.c | obj
	$(CC) $(LAC_CPPFLAGS) $(LAC_CFLAGS) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<
	
obj:
	mkdir obj
	
clean:
	$(RM) $(OBJ_FILES) $(DEMO_TARGETS) $(SHARED_LIB) $(STATIC_LIB)
