#include "lua_autoc.h"

void lua_autoc_open(void) {
  lua_autotype_open();
  lua_autostack_open();
  lua_autostruct_open();
  lua_autocall_open();
}

void lua_autoc_close(void) {
  lua_autocall_close();
  lua_autostruct_close();
  lua_autostack_close();
  lua_autotype_close();
}