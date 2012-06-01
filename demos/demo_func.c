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