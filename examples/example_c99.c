#include "../lautoc.h"

static float add_numbers(int first, float second) {
  return first + second;
}

luaA_function_declare(add_numbers, float, int, float);

int main(int argc, char **argv) {
  
  lua_State* L = luaL_newstate();
  
  luaA_open(L);
  luaA_function_register(L, add_numbers, float, int, float);
  
  lua_pushinteger(L, 5);
  lua_pushnumber(L, 6.13);
  luaA_call(L, add_numbers);
  
  printf("Result: %f\n", lua_tonumber(L, -1));
  
  lua_settop(L, 0);
  
  luaA_close(L);
  lua_close(L);
  
  return 0;
}