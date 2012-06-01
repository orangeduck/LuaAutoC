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

static void show_result_clear(pair p, person_details pd) {
  printf("Pair: (%i, %i)\n", p.x, p.y);
  printf("Person name: %s\n", pd.first_name);
  
  /* All lua to c String will be duplicates */
  /* Otherwise lua frees them as they leave the stack */
  free(pd.first_name);
  free(pd.second_name);
}

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
  lua_autopush(L, person_details, &my_details);
  
  lua_autofunc_add_args2_void(L, show_result_clear, void, pair, person_details);
  lua_autocall(L, show_result_clear);
  
  lua_autoc_close();
  lua_close(L);
	
	return 0;
}
