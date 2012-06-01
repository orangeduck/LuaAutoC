#include <stdio.h>
#include <stdlib.h>

#include "lua.h"
#include "lauxlib.h"
#include "lua_autoc.h"

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

typedef struct {
  char* first_name;
  char* second_name;
  float coolness;
} person_details;

int main(int argc, char **argv) {
	
  lua_State* L = luaL_newstate();
  lua_autoc_open();
	
	lua_autostack_func(pair, lua_autopush_pair, lua_autopop_pair);
	
  lua_autostruct_add(L, person_details);
  lua_autostruct_addmember(L, person_details, first_name, char*);
  lua_autostruct_addmember(L, person_details, second_name, char*);
  lua_autostruct_addmember(L, person_details, coolness, float);

  pair p = {1, 2};
  person_details my_details = {"Daniel", "Holden", 125212.213};
  
  lua_autopush(L, pair, &p);
  printf("Pair: (%s, %s)\n", lua_tostring(L, -2), lua_tostring(L, -1));
  lua_pop(L, 2);
  
  lua_autopush(L, person_details, &my_details);
  
  lua_getfield(L, -1, "first_name");
  printf("First Name: %s\n", lua_tostring(L, -1));
  lua_pop(L, 1);
  
  lua_getfield(L, -1, "second_name");
  printf("Second Name: %s\n", lua_tostring(L, -1));
  lua_pop(L, 1);
  
  lua_pop(L, 1);
  
  
  lua_autoc_close();
  lua_close(L);
	
	return 0;
}
