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
