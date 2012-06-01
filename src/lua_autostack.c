#include <stdlib.h>
#include <string.h>

#include "lua.h"

#include "lua_autostruct.h"
#include "lua_autohashtable.h"

#include "lua_autostack.h"

static lua_autohashtable* push_table;
static lua_autohashtable* pop_table;

void lua_autostack_open(void) {
  
  push_table = lua_autohashtable_new(256);
  pop_table = lua_autohashtable_new(256);
  
  lua_autostack_func(char, lua_autopush_prim_char, lua_autopop_prim_char);
  lua_autostack_func(signed char, lua_autopush_prim_signed_char, lua_autopop_prim_signed_char);
  lua_autostack_func(unsigned char, lua_autopush_prim_unsigned_char, lua_autopop_prim_unsigned_char);
  lua_autostack_func(short, lua_autopush_prim_short, lua_autopop_prim_short);
  lua_autostack_func(unsigned short, lua_autopush_prim_unsigned_short, lua_autopop_prim_unsigned_short);
  lua_autostack_func(int, lua_autopush_prim_int, lua_autopop_prim_int);
  lua_autostack_func(unsigned int, lua_autopush_prim_unsigned_int, lua_autopop_prim_unsigned_int);
  lua_autostack_func(long, lua_autopush_prim_long, lua_autopop_prim_long);
  lua_autostack_func(unsigned long, lua_autopush_prim_unsigned_long, lua_autopop_prim_unsigned_long);
  lua_autostack_func(long long, lua_autopush_prim_long_long, lua_autopop_prim_long_long);
  lua_autostack_func(unsigned long long, lua_autopush_prim_unsigned_long_long, lua_autopop_prim_unsigned_long_long);
  lua_autostack_func(float, lua_autopush_prim_float, lua_autopop_prim_float);
  lua_autostack_func(double, lua_autopush_prim_double, lua_autopop_prim_double);
  lua_autostack_func(long double, lua_autopush_prim_long_double, lua_autopop_prim_long_double);
  
  lua_autostack_func(char*, lua_autopush_prim_char_ptr, lua_autopop_prim_char_ptr);
  lua_autostack_func(const char*, lua_autopush_prim_const_char_ptr, lua_autopop_prim_const_char_ptr);
  
  lua_autostack_push_func(void, lua_autopush_prim_void);
  
}

void lua_autostack_close(void) {
  
  lua_autohashtable_delete(push_table);
  lua_autohashtable_delete(pop_table);
  
}

void lua_autopush_typeid(lua_State* L, lua_autotype type_id, void* c_in) {
  
  lua_autopush_func push_func = lua_autohashtable_get(push_table, lua_autotype_name(type_id));
  if (push_func != NULL) {
    return push_func(L, c_in);
  }
  
  if (lua_autostruct_added_typeid(L, type_id)) {
    return lua_autostruct_push_typeid(L, type_id, c_in);
  }
  
  lua_pushfstring(L, "lua_autostack: conversion to lua object from type '%s' not registered!", lua_autotype_name(type_id));
  lua_error(L);
}

void lua_autopop_typeid(lua_State* L, lua_autotype type_id, void* c_out) {
  
  lua_autopop_func pop_func = lua_autohashtable_get(pop_table, lua_autotype_name(type_id));
  if (pop_func != NULL) {
    return pop_func(L, c_out);
  }
  
  if (lua_autostruct_added_typeid(L, type_id)) {
    return lua_autostruct_pop_typeid(L, type_id, c_out);
  }
  
  lua_pushfstring(L, "lua_autostack: conversion from lua object from type '%s' not registered!", lua_autotype_name(type_id));
  lua_error(L);  
}

void lua_autostack_func_typeid(lua_autotype type_id, lua_autopush_func push_func, lua_autopop_func pop_func) {
  
  lua_autohashtable_set(push_table, lua_autotype_name(type_id), push_func);
  lua_autohashtable_set(pop_table, lua_autotype_name(type_id), pop_func);
  
}

void lua_autostack_push_func_typeid(lua_autotype type_id, lua_autopush_func func) {
  lua_autohashtable_set(push_table, lua_autotype_name(type_id), func); 
}

void lua_autostack_pop_func_typeid(lua_autotype type_id, lua_autopop_func func) {
  lua_autohashtable_set(pop_table, lua_autotype_name(type_id), func);
}

void lua_autopush_prim_char(lua_State* L, void* c_in) {
  lua_pushinteger(L, *(char*)c_in);
}

void lua_autopop_prim_char(lua_State* L, void* c_out) {
  *(char*)c_out = lua_tointeger(L, -1);
  lua_pop(L, 1);
}

void lua_autopush_prim_signed_char(lua_State* L, void* c_in) {
  lua_pushinteger(L, *(signed char*)c_in);
}

void lua_autopop_prim_signed_char(lua_State* L, void* c_out) {
  *(signed char*)c_out = lua_tointeger(L, -1);
  lua_pop(L, 1);
}

void lua_autopush_prim_unsigned_char(lua_State* L, void* c_in) {
  lua_pushinteger(L, *(unsigned char*)c_in);
}

void lua_autopop_prim_unsigned_char(lua_State* L, void* c_out) {
  *(unsigned char*)c_out = lua_tointeger(L, -1);
  lua_pop(L, 1);
}

void lua_autopush_prim_short(lua_State* L, void* c_in) {
  lua_pushinteger(L, *(short*)c_in);
}

void lua_autopop_prim_short(lua_State* L, void* c_out) {
  *(short*)c_out = lua_tointeger(L, -1);
  lua_pop(L, 1);
}

void lua_autopush_prim_unsigned_short(lua_State* L, void* c_in) {
  lua_pushinteger(L, *(unsigned short*)c_in);
}

void lua_autopop_prim_unsigned_short(lua_State* L, void* c_out) {
  *(unsigned short*)c_out = lua_tointeger(L, -1);
  lua_pop(L, 1);
}

void lua_autopush_prim_int(lua_State* L, void* c_in) {
  lua_pushinteger(L, *(int*)c_in);
}

void lua_autopop_prim_int(lua_State* L, void* c_out) {
  *(int*)c_out = lua_tointeger(L, -1);
  lua_pop(L, 1);
}

void lua_autopush_prim_unsigned_int(lua_State* L, void* c_in) {
  lua_pushinteger(L, *(unsigned int*)c_in);
}

void lua_autopop_prim_unsigned_int(lua_State* L, void* c_out) {
  *(unsigned int*)c_out = lua_tointeger(L, -1);
  lua_pop(L, 1);
}

void lua_autopush_prim_long(lua_State* L, void* c_in) {
  lua_pushinteger(L, *(long*)c_in);
}

void lua_autopop_prim_long(lua_State* L, void* c_out) {
  *(long*)c_out = lua_tointeger(L, -1);
  lua_pop(L, 1);
}

void lua_autopush_prim_unsigned_long(lua_State* L, void* c_in) {
  lua_pushinteger(L, *(unsigned long*)c_in);
}

void lua_autopop_prim_unsigned_long(lua_State* L, void* c_out) {
  *(unsigned long*)c_out = lua_tointeger(L, -1);
  lua_pop(L, 1);
}

void lua_autopush_prim_long_long(lua_State* L, void* c_in) {
  lua_pushinteger(L, *(long long*)c_in);
}

void lua_autopop_prim_long_long(lua_State* L, void* c_out) {
  *(long long*)c_out = lua_tointeger(L, -1);
  lua_pop(L, 1);
}

void lua_autopush_prim_unsigned_long_long(lua_State* L, void* c_in) {
  lua_pushinteger(L, *(unsigned long long*)c_in);
}

void lua_autopop_prim_unsigned_long_long(lua_State* L, void* c_out) {
  *(unsigned long long*)c_out = lua_tointeger(L, -1);
  lua_pop(L, 1);
}

void lua_autopush_prim_float(lua_State* L, void* c_in) {
  lua_pushnumber(L, *(float*)c_in);
}

void lua_autopop_prim_float(lua_State* L, void* c_out) {
  *(float*)c_out = lua_tonumber(L, -1);
  lua_pop(L, 1);
}

void lua_autopush_prim_double(lua_State* L, void* c_in) {
  lua_pushnumber(L, *(double*)c_in);
}

void lua_autopop_prim_double(lua_State* L, void* c_out) {
  *(double*)c_out = lua_tonumber(L, -1);
  lua_pop(L, 1);
}

void lua_autopush_prim_long_double(lua_State* L, void* c_in) {
  lua_pushnumber(L, *(long double*)c_in);
}

void lua_autopop_prim_long_double(lua_State* L, void* c_out) {
  *(long double*)c_out = lua_tonumber(L, -1);
  lua_pop(L, 1);
}

void lua_autopush_prim_char_ptr(lua_State* L, void* c_in) {
  lua_pushstring(L, *(char**)c_in);
}

void lua_autopop_prim_char_ptr(lua_State* L, void* c_out) {
  const char* ref = lua_tostring(L, -1);
  *(char**)c_out = malloc(strlen(ref) + 1);
  strcpy(*(char**)c_out, ref);
  lua_pop(L, 1);
}

void lua_autopush_prim_const_char_ptr(lua_State* L, void* c_in) {
  lua_pushstring(L, *(const char**)c_in);
}

void lua_autopop_prim_const_char_ptr(lua_State* L, void* c_out) {
  const char* ref = lua_tostring(L, -1);
  *(char**)c_out = malloc(strlen(ref) + 1);
  strcpy(*(char**)c_out, ref);
  lua_pop(L, 1);
}

void lua_autopush_prim_void(lua_State* L, void* c_in) {
  lua_pushnil(L);
}

