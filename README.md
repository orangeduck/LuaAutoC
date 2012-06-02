lua_autoc
=========

Version 0.6

Introduction
------------

lua_autoc automatically wraps C functions and structs at runtime so that they can be called from the lua/C API.

* Don't fancy the idea of hand wrapping every function and struct in your codebase?
* Don't like the look of the monster that is SWIG?
* Want a way for developers to register extra functionality at runtime?

lua_autoc is here to help.

PyAutoC
-------

lua_autoc is based upon my library [PyAutoC](https://github.com/orangeduck/PyAutoC) which provides similar functionality but for the Python/C API. It is largely just a renaming of what I did there, but some of it has been adapated to better fit the semantics of the lua API. Most notably rather than using PyObjects and reference counting the functions are designed for pushing and popping on the lua stack and interacting in that way.

Although I love Python this version of the library is probably more useful. Python already has a huge array of tools for interacting with C code. This library is also better suited to embedding, which Python somewhat frowns upon over extending, but lua has a very strong culture of.


Basic Usage 1
-------------

```c
#include <stdio.h>

#include "lua.h"
#include "lauxlib.h"
#include "lua_autoc.h"

static float add_numbers(int first, float second) {
  return first + second;
}

int main(int argc, char **argv) {
  
  lua_State* L = luaL_newstate();
  lua_autoc_open();
  
  lua_autofunc_add_args2(L, add_numbers, float, int, float);
  
  lua_pushinteger(L, 5);
  lua_pushnumber(L, 6.13);
  lua_autocall(L, add_numbers);
  
  printf("Result: %f\n", lua_tonumber(L, -1));
  
  lua_autoc_close();
  lua_close(L);
  
  return 0;
  
}
```
	
lua_autoc will call `add\_numbers` with the lua values on the stack. It will then push the return value as a lua object back onto the stack. No editing of the original function required.

	
Basic Usage 2
-------------

```c
#include <stdio.h>

#include "lua.h"
#include "lauxlib.h"
#include "lua_autoc.h"

typedef struct {
  float x, y, z;
} vector3;

int main(int argc, char **argv) {
	
  lua_State* L = luaL_newstate();
  lua_autoc_open();
	
  lua_autostruct_add(L, vector3);
  lua_autostruct_addmember(L, vector3, x, float);
  lua_autostruct_addmember(L, vector3, y, float);
  lua_autostruct_addmember(L, vector3, z, float);

  vector3 position = {1.0f, 2.11f, 3.16f};
  
  lua_autostruct_push_member(L, vector3, &position, y);
  
  printf("Y: %f\n", lua_tonumber(L, -1));
  
  lua_autoc_close();
  lua_close(L);
	
  return 0;
}
```
	
Structs work similarly to their functional counterparts. They can be accessed at runtime and do automatic conversion of types. The provide the ability to push members onto the stack and pop objects off and store them in members.
 

Type Conversions
----------------

To call functions or access struct members which have non-primitive types it is possible to register your own conversion functions.

```c
typedef struct {
  int x, y;
} pair;

static void lua_autopush_pair(lua_State* L, void* c_in) {
  pair p = *(pair*)c_in;
  lua_pushinteger(L, p.x);
  lua_pushinteger(L, p.y);
}

static void lua_autopop_pair(lua_State* L, void* c_out) {
  pair* p = (pair*)c_out;
  p->y = lua_tointeger(L, -1); lua_pop(L, 1);
  p->x = lua_tointeger(L, -1); lua_pop(L, 1);
}

lua_autostack_func(pair, lua_autopush_pair, lua_autopop_pair);
```

Now it is possible to call any functions with `pair` as an argument or return type and lua_autoc will handle any conversions automatically. You can also use the registered functions directly in your code in a fairly convenient and natural way using the `lua_autopush` and `lua_autopop` macros.

```c
pair p = {1, 2};
lua_autopush(L, pair, &p);
```

Alternatively, when you register structs with lua_autoc, if no conversion functions are known, it will attempt to automatically convert them. One word of warning - be careful with circular references. The conversion is recursive and given the chance will happily run forever!

```c

typedef struct {
  char* first_name;
  char* second_name;
  float coolness;
} person_details;

lua_autostruct_add(L, person_details);
lua_autostruct_addmember(L, person_details, first_name, char*);
lua_autostruct_addmember(L, person_details, second_name, char*);
lua_autostruct_addmember(L, person_details, coolness, float);

person_details my_details = {"Daniel", "Holden", 125212.213};

lua_autopush(L, person_details, &my_details);

lua_getfield(L, -1, "first_name");
printf("First Name: %s\n", lua_tostring(L, -1));
lua_pop(L, 1);

lua_getfield(L, -1, "second_name");
printf("Second Name: %s\n", lua_tostring(L, -1));
lua_pop(L, 1);

lua_pop(L, 1);

```

Using C headers
--------------------

I've included a basic python script which will autogenerate lua_autoc code for structs and functions from C headers.

```
$ python autogen.py ../Corange/include/assets/sound.h

lua_autostruct_add(sound);
lua_autostruct_addmember(sound, data, char*);
lua_autostruct_addmember(sound, length, int);

lua_autofunc_add_args1(wav_load_file, sound*, char*);
lua_autofunc_add_args1_void(sound_delete, void, sound*);
```

Extended Usage 1
----------------

You can use lua_autoc to very quickly and easily create lua C modules for a bunch of functions such as might be done via SWIG or similar.

```c
#include <stdio.h>
#include <stdlib.h>

#include "lua.h"
#include "lauxlib.h"
#include "lua_autoc.h"

static float add_numbers(int first, float second) {
  return first + second;
}

static void hello_world(char* person) {
	printf("Hello %s!", person);
}

static int autocall(lua_State* L) {
  lua_autocall_name(L, lua_tostring(L, 1));
  lua_remove(L, -2);
  return 1;
}

int main(int argc, char **argv) {
	
  lua_State* L = luaL_newstate();
  lua_autoc_open();
  
  lua_autofunc_add_args2(L, add_numbers, float, int, float);
  lua_autofunc_add_args1_void(L, hello_world, void, char*);
  
  lua_pushcfunction(L, autocall);
  lua_setglobal(L, "autocall");
  
  luaL_dostring(L, "autocall(\"add_numbers\", 1, 5.2)");
  luaL_dostring(L, "autocall(\"hello_world\", \"Daniel\")");
  
  lua_autoc_close();
  lua_close(L);
	
  return 0;
}
```

Once you have this basic interface of autocall it is easy to intergrate more complicated and transparent APIs with some more complicated lua and metaclasses.


Runtime?
--------

When normally building a lua/C extension all accessible functions must be statically declared in a methods table and compiled. If a developer wants to add more functions to the lua bindings he must add more methods to the table. Using lua_autoc, users and developers can register new functions, structs and type conversions as the program is running. This means developers can use and extend your lua API without ever touching the vanilla lua/C API!

It also means that the job of wrapping is much easier - you can use strings and dynamic elements directly from lua. For example...


Extended Usage 2
----------------

Coming soon...
	
Managing Behaviour
------------------

Coming soon...

FAQ
---

* How do unions work?

  They work the same way as structs. All the lua_autostruct functions should be fine to use on them. Like in C though, accessing them "incorrectly" in lua will result in the raw data being interpreted differently. lua_autoc doesn't do any clever checking for you.
  
* How do enums work?

  Enums work like any other type and the best way to deal with them is to write an explicit conversion function. There is no real way to know what storage type compilers will pick for an enum, it could be a unsigned char, signed int, long or anything else. If though, you are sure what storage type the compiler is using for a particular enum, it might be easier to just use that as the registered type and get a conversion for free.

* Does this work on Linux/Mac/Windows?
  
  Should work fine on Linux. I imagine it will be simple to port to Mac but I don't have one to test on. It also compiles fine on Windows providing you use MinGW or Cygwin.
  
  I've done some experiments getting lua_autoc to compile in Visual Studio and the port is fairly simple but there are a couple of annoying aspects. If someone is interested I'll be more than happy to share my developments but for now I would rather keep the code in the repo clean.
  
  To begin with there are two main options, either translate the source files into ANSI C or use the C++ compiler. Converting to ANSI C turned out to be too much of an effort and usage overall requires a C99 or C++ compiler anyway, to allow for some form of nested functions. Going with C++ appears to be the best way. Unfortunately this requires you rename all the lua_autoc file extensions to .cpp. secondly Visual Studio disallows nested functions by default but there is a simple way around this by wrapping them in a struct/class and declaring them static. This means some more edits are required for the Function Registration Macros but again nothing huge. Contact me for more info.

* Why are the function registration macros so verbose?
  
  Unfortunately this is unavoidable without writing complex assembly code. Just remember that the argument count must be specified in the name and also if the function returns void. All the macros in lua_autoc throw nice readable errors (for example, trying to register a struct member that does not exist), so don't worry to much about messing the system with a typo - in general it wont let you.

```c
lua_autofunc_add_args2(add_numbers, float, int, float);
lua_autofunc_add_args3_void(add_numbers_message, void, char*, int, float);
```

* Is lua_autoc slow?
  
  For most uses lua_autoc has to lookup runtime information in a hashtable. For calling functions it has to duplicate some of the process involved in managing the stack. Perhaps for a very large codebase there might be some overhead in performance and memory but for any normal sized one, this is minimal. If you are concerned about performance you can still wrap your functions manually but perhaps if you are using a scripting language like lua it isn't much bother.

* Is this just macro hacks? Can I really use it with my production code?

  There are certainly some macro tricks going on, but most of them are pretty simple and nothing to gruesome - they are just there to save you typing. If you are worried send me an email and I'll explain the internals so that you can decide for yourself.
  
  