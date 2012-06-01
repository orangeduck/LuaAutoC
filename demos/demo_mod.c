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