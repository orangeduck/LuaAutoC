#ifndef luaA_stack_h
#define luaA_stack_h

#include "lua.h"
#include "luaA_type.h"

void luaA_stack_open(void);
void luaA_stack_close(void);

#define luaA_push(L, type, c_in) luaA_push_typeid(L, luaA_type_id(type), c_in)
int luaA_push_typeid(lua_State* L, luaA_Type type_id, void* c_in);

#define luaA_to(L, type, c_out, index) luaA_to_typeid(L, luaA_type_id(type), c_out, index)
void luaA_to_typeid(lua_State* L, luaA_Type type_id, void* c_out, int index);

typedef int (*luaA_Pushfunc)(lua_State*, void*);
typedef void (*luaA_Tofunc)(lua_State*, void*, int);

#define luaA_stack_func(type, push_func, to_func) luaA_stack_func_typeid(luaA_type_id(type), push_func, to_func);
void luaA_stack_func_typeid(luaA_Type type_id, luaA_Pushfunc push_func, luaA_Tofunc to_func);

#define luaA_stack_push_func(type, func) luaA_stack_push_func_typeid(luaA_type_id(type), func)
void luaA_stack_push_func_typeid(luaA_Type type_id, luaA_Pushfunc func);

#define luaA_stack_to_func(type, func) luaA_stack_to_func_typeid(luaA_type_id(type), func)
void luaA_stack_to_func_typeid(luaA_Type type_id, luaA_Tofunc func);


int luaA_push_char(lua_State* L, void* c_in);
void luaA_to_char(lua_State* L, void* c_out, int index);
int luaA_push_signed_char(lua_State* L, void* c_in);
void luaA_to_signed_char(lua_State* L, void* c_out, int index);
int luaA_push_unsigned_char(lua_State* L, void* c_in);
void luaA_to_unsigned_char(lua_State* L, void* c_out, int index);
int luaA_push_short(lua_State* L, void* c_in);
void luaA_to_short(lua_State* L, void* c_out, int index);
int luaA_push_unsigned_short(lua_State* L, void* c_in);
void luaA_to_unsigned_short(lua_State* L, void* c_out, int index);
int luaA_push_int(lua_State* L, void* c_in);
void luaA_to_int(lua_State* L, void* c_out, int index);
int luaA_push_unsigned_int(lua_State* L, void* c_in);
void luaA_to_unsigned_int(lua_State* L, void* c_out, int index);
int luaA_push_long(lua_State* L, void* c_in);
void luaA_to_long(lua_State* L, void* c_out, int index);
int luaA_push_unsigned_long(lua_State* L, void* c_in);
void luaA_to_unsigned_long(lua_State* L, void* c_out, int index);
int luaA_push_long_long(lua_State* L, void* c_in);
void luaA_to_long_long(lua_State* L, void* c_out, int index);
int luaA_push_unsigned_long_long(lua_State* L, void* c_in);
void luaA_to_unsigned_long_long(lua_State* L, void* c_out, int index);
int luaA_push_float(lua_State* L, void* c_in);
void luaA_to_float(lua_State* L, void* c_out, int index);
int luaA_push_double(lua_State* L, void* c_in);
void luaA_to_double(lua_State* L, void* c_out, int index);
int luaA_push_long_double(lua_State* L, void* c_in);
void luaA_to_long_double(lua_State* L, void* c_out, int index);

int luaA_push_char_ptr(lua_State* L, void* c_in);
void luaA_to_char_ptr(lua_State* L, void* c_out, int index);
int luaA_push_const_char_ptr(lua_State* L, void* c_in);
void luaA_to_const_char_ptr(lua_State* L, void* c_out, int index);

int luaA_push_void(lua_State* L, void* c_in);

#endif