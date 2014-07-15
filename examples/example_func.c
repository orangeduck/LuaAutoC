#include "../lautoc.h"

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