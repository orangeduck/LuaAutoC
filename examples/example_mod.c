#include "../lautoc.h"

static int add_round(int x, float y) {
  return (int)(x + y);
}

static void greet_many(char* person, int times) {
  for (int i = 0; i < times; i++) {
    printf("Hello %s!\n", person);
  }
}

static int C(lua_State* L) {
  return luaA_call_name(L, lua_tostring(L, 1));
}

int main(int argc, char **argv) {
	
  lua_State* L = luaL_newstate();
  
  luaA_open(L);
  luaA_function(L, add_round, int, int, float);
  luaA_function(L, greet_many, void, char*, int);
  
  lua_register(L, "C", C);
  luaL_dostring(L, "C(\"greet_many\", \"Daniel\", C(\"add_round\", 1, 2.7))");
  
  luaA_close(L);
  lua_close(L);
	
  return 0;
}