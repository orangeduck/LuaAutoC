#include <stdio.h>
#include <stdlib.h>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "lua_autoc.h"

typedef struct {
  char* name;
  int num_wings;
} birdie;

static birdie test_birdie;
static birdie* get_instance_ptr(lua_State* L) {
  return &test_birdie;
}

static int birdie_index(lua_State* L) {
  const char* member = lua_tostring(L, -1);
  birdie* self = get_instance_ptr(L);
  lua_autostruct_push_membername(L, birdie, self, member);
  lua_remove(L, -2);
  lua_remove(L, -2);
  return 1;
}

static int birdie_setindex(lua_State* L) {
  const char* member = lua_tostring(L, -2);
  birdie* self = get_instance_ptr(L);
  lua_autostruct_pop_member(L, birdie, self, member);
  lua_pop(L, 2);
  return 0;
}

int main(int argc, char **argv) {
  
  test_birdie.name = "MrFlingly";
  test_birdie.num_wings = 2;
  
  lua_State* L = luaL_newstate();
  luaL_openlibs(L);
  lua_autoc_open();
  
  lua_autostruct_add(L, birdie);
  lua_autostruct_addmember(L, birdie, name, char*);
  lua_autostruct_addmember(L, birdie, num_wings, int);
  
  lua_pushcfunction(L, birdie_index);
  lua_setglobal(L, "birdie_index");
  
  lua_pushcfunction(L, birdie_setindex);
  lua_setglobal(L, "birdie_setindex");
  
  luaL_dostring(L, ""
    "Birdie = {}\n"
    "setmetatable(Birdie, Birdie)\n"
    "function Birdie:__index(i) return birdie_index(self, i) end\n"
    "function Birdie:__setindex(i, x) return birdie_setindex(self, i, x) end\n"
    "function Birdie.__call()\n"
    "  local self = {}\n"
    "  setmetatable(self, Birdie)\n"
    "  return self\n"
    "end\n"
    "\n"
    "bird = Birdie()\n"
    "print(bird.name)\n"
    "print(bird.num_wings)\n"
    "\n"
    );
  
  lua_autoc_close();
  lua_close(L);
  
  return 0;
  
}