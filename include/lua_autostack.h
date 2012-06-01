#ifndef lua_autostack_h
#define lua_autostack_h

#include "lua.h"
#include "lua_autotype.h"

void lua_autostack_open(void);
void lua_autostack_close(void);

#define lua_autopush(L, type, c_val) lua_autopush_typeid(L, lua_typeid(type), c_in)
void lua_autopush_typeid(lua_State* L, lua_autotype type_id, void* c_in);

#define lua_autopop(L, type, py_val, c_out) lua_autopop_typeid(L, lua_typeid(type), c_out)
void lua_autopop_typeid(lua_State* L, lua_autotype type_id, void* c_out);

typedef void (*lua_autopush_func)(lua_State*, void*);
typedef void (*lua_autopop_func)(lua_State*, void*);

#define lua_autostack_func(type, push_func, pop_func) lua_autostack_func_typeid(lua_typeid(type), push_func, pop_func);
void lua_autostack_func_typeid(lua_autotype type_id, lua_autopush_func push_func, lua_autopop_func pop_func);

#define lua_autostack_push_func(type, func) lua_autostack_push_func_typeid(lua_typeid(type), func)
void lua_autostack_push_func_typeid(lua_autotype type_id, lua_autopush_func func);

#define lua_autostack_pop_func(type, func) lua_autostack_pop_func_typeid(lua_typeid(type), func)
void lua_autostack_pop_func_typeid(lua_autotype type_id, lua_autopop_func func);


void lua_autopush_prim_char(lua_State* L, void* c_in);
void lua_autopop_prim_char(lua_State* L, void* c_out);
void lua_autopush_prim_signed_char(lua_State* L, void* c_in);
void lua_autopop_prim_signed_char(lua_State* L, void* c_out);
void lua_autopush_prim_unsigned_char(lua_State* L, void* c_in);
void lua_autopop_prim_unsigned_char(lua_State* L, void* c_out);
void lua_autopush_prim_short(lua_State* L, void* c_in);
void lua_autopop_prim_short(lua_State* L, void* c_out);
void lua_autopush_prim_unsigned_short(lua_State* L, void* c_in);
void lua_autopop_prim_unsigned_short(lua_State* L, void* c_out);
void lua_autopush_prim_int(lua_State* L, void* c_in);
void lua_autopop_prim_int(lua_State* L, void* c_out);
void lua_autopush_prim_unsigned_int(lua_State* L, void* c_in);
void lua_autopop_prim_unsigned_int(lua_State* L, void* c_out);
void lua_autopush_prim_long(lua_State* L, void* c_in);
void lua_autopop_prim_long(lua_State* L, void* c_out);
void lua_autopush_prim_unsigned_long(lua_State* L, void* c_in);
void lua_autopop_prim_unsigned_long(lua_State* L, void* c_out);
void lua_autopush_prim_long_long(lua_State* L, void* c_in);
void lua_autopop_prim_long_long(lua_State* L, void* c_out);
void lua_autopush_prim_unsigned_long_long(lua_State* L, void* c_in);
void lua_autopop_prim_unsigned_long_long(lua_State* L, void* c_out);
void lua_autopush_prim_float(lua_State* L, void* c_in);
void lua_autopop_prim_float(lua_State* L, void* c_out);
void lua_autopush_prim_double(lua_State* L, void* c_in);
void lua_autopop_prim_double(lua_State* L, void* c_out);
void lua_autopush_prim_long_double(lua_State* L, void* c_in);
void lua_autopop_prim_long_double(lua_State* L, void* c_out);

/* These return a copy of a string which the user is responsible for freeing */
void lua_autopush_prim_char_ptr(lua_State* L, void* c_in);
void lua_autopop_prim_char_ptr(lua_State* L, void* c_out);
void lua_autopush_prim_const_char_ptr(lua_State* L, void* c_in);
void lua_autopop_prim_const_char_ptr(lua_State* L, void* c_out);

void lua_autopush_prim_void(lua_State* L, void* c_in);

#endif