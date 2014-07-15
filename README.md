LuaAutoC
========

Automagically use C Functions and Structs with the Lua API

Version 2.0.1

```c
#include "lautoc.h"

static int fib(int n) {
  if (n == 0) { return 1; }
  if (n == 1) { return 1; }
  return fib(n-1) + fib(n-2);
}

int main(int argc, char** argv) {
  
  lua_State* L = luaL_newstate();
  
  luaA_open(L);
  luaA_function(L, fib, int, int);
  
  lua_pushinteger(L, 25);
  luaA_call(L, fib);
  
  printf("Result: %i\n", (int)lua_tointeger(L, -1));
  
  lua_pop(L, 2);
  
  luaA_close(L);
  lua_close(L);
  
  return 0;
}
```

Features
--------

* Easy to integrate.
* Unobtrusive of existing code.
* Flexible, Extensible and Powerful.
* Provides dynamic runtime reflection.
* Friendly API.


Usage
-----

At its most basic, LuaAutoC can be used to call C functions from Lua. Arguments are automatically converted to C, the function is executed, and the return value is then automatically converted back and placed on top the Lua stack. Calling functions in this way does not pop arguments off the stack.

```c
#include "lautoc.h"

float power(float val, int pow) {
  float x = 1.0;
  for(int i = 0; i < pow; i++) {
    x *= val;
  }
  return x;
}

int main(int argc, char **argv) {
  
  lua_State* L = luaL_newstate();
  
  luaA_open(L);
  luaA_function(L, power, float, float, int);
  
  lua_pushnumber(L, 4.2);
  lua_pushinteger(L, 3);
  luaA_call(L, power);
  
  printf("Result: %f\n", lua_tonumber(L, -1));
  
  lua_settop(L, 0);
  
  luaA_close();
  lua_close(L);
  
  return 0;
}
```

LuaAutoC also provides functions to deal with structs. Their members can be pushed onto, or read from, the stack. All with automatic conversion of types between Lua and C.

```c
#include "lautoc.h"

typedef struct {
  float x, y, z;
} vector3;

int main(int argc, char **argv) {
	
  lua_State* L = luaL_newstate();
  
  luaA_open(L);
  luaA_struct(L, vector3);
  luaA_struct_member(L, vector3, x, float);
  luaA_struct_member(L, vector3, y, float);
  luaA_struct_member(L, vector3, z, float);
  
  vector3 position = {1.0f, 2.11f, 3.16f};
  
  luaA_struct_push_member(L, vector3, &position, y);
  
  printf("Y: %f\n", lua_tonumber(L, -1));
  
  lua_pop(L, 1);
  
  luaA_close();
  lua_close(L);
	
  return 0;
}
```

Enums are transformed into string - value mappings.

Again they need to be registered. For each string - value pair you can declare independently if it is case-sensitive or not. You can also register multiple strings for a single enum value, and any matching Lua string will be transformed into the enum value. Although for multiple values the last registered value will be used when transforming from C to Lua.

```c
#include "lautoc.h"

typedef enum {
  case_sensitive,
  case_insensitive,
  not_contiguous = 45,
} enum_val;

int main(int argc, char **argv) {
	
  lua_State* L = luaL_newstate();
  luaA_open(L);
	
  luaA_enum(L, enum_val);
  luaA_enum_value(L, enum_val, case_sensitive, true);
  luaA_enum_value(L, enum_val, case_insensitive, false);
  luaA_enum_value(L, enum_val, not_contiguous, false);
  luaA_enum_value_name(L, enum_val, case_sensitive, "alias_sensitive", true);

  enum_val test_enum = not_contiguous;
  luaA_push(L, enum_val, &test_enum);
  printf("not_contiguous pushed as %s\n", lua_tostring(L,-1));

  lua_pushstring(L, "alias_sensitive");
  luaA_to(L, enum_val, &test_enum, -1);
  printf("alias_sensitive read back as %d\n", test_enum); 

  luaA_close(L);
  lua_close(L);
	
  return 0;
}
```

To use LuaAutoC with non-native types it is possible to register your own conversion functions.

```c
typedef struct {
  int x, y;
} pair;

static int luaA_push_pair(lua_State* L, luaA_Type t, const void* c_in) {
  pair* p = (pair*)c_in;
  lua_pushinteger(L, p->x);
  lua_pushinteger(L, p->y);
  return 2;
}

static void luaA_to_pair(lua_State* L, luaA_Type t, void* c_out, int index) {
  pair* p = (pair*)c_out;
  p->y = lua_tointeger(L, index);
  p->x = lua_tointeger(L, index-1);
}
```

```c
luaA_convert(L, pair, luaA_push_pair, luaA_to_pair);
```

Conversion functions are automatically used in the calling of functions, or in the conversion of structs and their members. Registered conversions are also available directly for manipulation of the Lua stack using `luaA_push` and `luaA_to`.

```c
pair p = {1, 2};
luaA_push(L, pair, &p);
```

But writing conversion functions sucks, so when structs are registered with LuaAutoC, if no conversion functions are known, automatic conversion to a Lua table can be performed.

```c
typedef struct {
  int id;
  const char* name;
  float coolness;
} person_details;
```

```c
luaA_struct(L, person_details);
luaA_struct_member(L, person_details, id, int);
luaA_struct_member(L, person_details, name, const char*);
luaA_struct_member(L, person_details, coolness, float);

person_details my_details = {0, "Dan", 125212.213};
luaA_push(L, person_details, &my_details);

lua_getfield(L, -1, "id");
printf("Id: %i\n", (int)lua_tointeger(L, -1));
lua_pop(L, 1);

lua_getfield(L, -1, "name");
printf("Name: %s\n", lua_tostring(L, -1));
lua_pop(L, 1);

lua_pop(L, 1);
```

This is very useful, but a few words of warning.

* Be careful with circular references. The conversion is recursive and given the chance will happily run forever!
* Be careful of pointer types such as `char*`. An automatic conversion may assign a struct a new pointer value to a string on the Lua Stack likely to be garbage collected once the call is over. The actual required behaviour, of copying the value of the Lua string into the existing allocated memory, wont be performed by default!

* * *

LuaAutoC lets you call C functions by providing a string of their name. This makes a quick and dirty interface to your C library really easy to build.

```c
#include "lautoc.h"

static float add_numbers(int first, float second) {
  return first + second;
}

static void hello_world(char* person) {
  printf("Hello %s!", person);
}

static int C(lua_State* L) {
  return luaA_call_name(L, lua_tostring(L, 1));
}

int main(int argc, char **argv) {
	
  lua_State* L = luaL_newstate();
  luaA_open(L);
  
  luaA_function(L, add_numbers, float, 2, int, float);
  luaA_function_void(L, hello_world, 1, char*);
  
  lua_pushcfunction(L, C);
  lua_setglobal(L, "C");
  
  luaL_dostring(L, "C(\"add_numbers\", 1, 5.2)");
  luaL_dostring(L, "C(\"hello_world\", \"Daniel\")");
  
  luaA_close(L);
  lua_close(L);
	
  return 0;
}
```

* * *

Using LuaAutoC it is easy to wrap pointers to structs so that they act like object instances. All we need to do is set `__index` and `__newindex` in the metatable.

```lua
Birdie = {}
setmetatable(Birdie, Birdie)

function Birdie.__call()
  local self = {}
  setmetatable(self, Birdie)
  return self
end

Birdie.__index = birdie_index
Birdie.__newindex = birdie_newindex

bird = Birdie()
print(bird.name)
print(bird.num_wings)
```

Now we just define `birdie_index` and `birdie_newindex` in the C API as shown below.

Alternatively developers can define the whole metatable in C and hide the `birdie_newindex` and `birdie_index` functions altogether.

```c
typedef struct {
  char* name;
  int num_wings;
} birdie;

static int birdie_index(lua_State* L) {
  const char* membername = lua_tostring(L, -1);
  birdie* self = get_instance_ptr(L);
  return luaA_struct_push_member_name(L, birdie, self, membername);
}

static int birdie_newindex(lua_State* L) {
  const char* membername = lua_tostring(L, -2);
  birdie* self = get_instance_ptr(L);
  luaA_struct_to_member_name(L, birdie, self, membername, -1);
  return 0;
}
```

```c
luaA_struct(L, birdie);
luaA_struct_member(L, birdie, name, char*);
luaA_struct_member(L, birdie, num_wings, int);

lua_pushcfunction(L, birdie_index);
lua_setglobal(L, "birdie_index");

lua_pushcfunction(L, birdie_newindex);
lua_setglobal(L, "birdie_newindex");
```

A lot less work than writing a bunch of getters and setters!

The `get_instance_ptr` function is left for the user to implement and there are lots of options. The idea is that somehow the Lua table/instance should tell you how to get a pointer to the actual struct instance in C which it represents. A good option is to store C pointers in the Lua instance.

It is also possible to make the Lua metatable allocation and deallocation functions call some C functions which allocate and decallocate the structure you are emulating, storing the instance pointer to let you identify it later! Not only that. It isn't difficult to make methods available too!

The true power of Lua AutoC comes if you look a level deeper. If you use `luaA_struct_push_member_name_type` or `luaA_truct_to_member_name_type` you can even generalize the above code to work for arbitrary structs/classes/types which can be added to.

For this to work you need to get a `luaA_Type` value. This can be found by feeding a string into `luaA_type_find` which will lookup a string and see if a type has been registered with the same name. This means that if you give it a string of a previously registered data type E.G `"birdie"`, it will return a matching id. One trick is to feed it with the name of the instance's metatable. This means it is possible to create a new Lua object with defined `__index` and `__newindex`, it will automatically act like the corresponding C struct of the same name.

* * *

Often in C, the same types can have different meanings. For example an `int*` could either mean that a function wants an array of integers or that it outputs some integer. We can change the behaviour of Lua AutoC without changing the function signature by using typedefs and new conversion functions. Then on function registration you just use the newly defined type rather than the old one. Providing the types are true aliases there wont be any problems with converting types.

```c
static void print_int_list(int* list, int num_ints) {
  for(int i = 0; i < num_ints; i++) {
    printf("Int %i: %i\n", i, list[i]);
  }
}

typedef int* int_list;

static int list_space[512];
static void luaA_to_int_list(lau_State* L, luaA_Type t, void* c_out, int index) {
  for(int i = 1; i <= luaL_getn(L, index); i++) {
    lua_pushinteger(L, i);
    lua_gettable(L, index-1);
	  list_space[i] = lua_tointeger(L, index); lua_pop(L, 1);
  }
  *(int_list*)c_out = list_space;
}

luaA_converst_to(int_list, luaA_to_int_list);

luaA_function(print_int_list, void, int_list, int);
```

As you can probably see, automatic wrapping and type conversion becomes hard when memory management and pointers are involved.


Headers
-------

It isn't any fun writing out all the registration functions. I've included a basic Lua script which will auto-generate LuaAutoC code for structs and functions from some C header. It is fairly basic, not a C parser, and wont cover all situations, so expect to have to do some cleaning up for complicated headers.

```
$ lua autogen.lua ../Corange/include/assets/sound.h

luaA_struct(sound);
luaA_struct_member(sound, data, char*);
luaA_struct_member(sound, length, int);

luaA_function(wav_load_file, sound*, char*);
luaA_function(sound_delete, void, sound*);
```

Internals
---------

LuaAutoC works by storing meta-information about C types, structs, and functions in the Lua registry.

This allows it to automatically do conversions at runtime. In my opinion this is a far better approach than compile-time wrapping such as is available from programs such as SWIG. As all the type information is stored in the Lua registry this allows for the use reflection techniques to ensure you build a Lua API that really does match the concepts of your C program.

It also means that LuaAutoC is completely unintuitive and can be used without touching your original codebase, marking it up, or making anny changes to it. Finally, because it is a runtime system, this system can be changed and adapted by other developers. You can provide functions to developers that _generate_ bindings for their new functions, types, or structs. They might not ever have to touch the Lua stack!


FAQ
---

* How do unions work?

  They work the same way as structs. All the `luaA_struct` functions should be fine to use on them. Like in C though, accessing them "incorrectly" in Lua will result in the raw data being interpreted differently. Lua AutoC doesn't do any clever checking for you.  

* Nested Functions?
  
  By standard LuaAutoC makes uses of nested functions. Almost all compilers support these, but if non LuaAutoC can still be used at the cost of some repetition. Now functions must be "declared" outside of the program, and then "registered" in the runtime. See `demo_c99.c` for a clear example.
  
* Is LuaAutoC slow?
  
  For most uses LuaAutoC has to lookup runtime information in the Lua registry. For calling functions it has to duplicate some of the process involved in managing the stack. Perhaps for a very large codebase with many calls there might be some overhead in performance and memory, but for any normal sized one this is minimal. If you are concerned about performance you can still wrap your functions manually, but perhaps if you are using a scripting language like Lua it isn't worth it.

* Is this just macro hacks? Can I really use it in production code?

  There are certainly some macro tricks going on, but the backbone code is very simple. The macros just save typing. I use my similar library PyAutoC to wrap my game engine Corange (~10000 LOC, ~1000 functions) without any issues. If you are worried send me an email and I'll explain the internals so that you can decide for yourself. I've also written a short blog post about it [here](http://theorangeduck.com/page/autoc-tools).
  
  
