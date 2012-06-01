#ifndef lua_autocall_h
#define lua_autocall_h

#include "lua.h"
#include "lua_autotype.h"
#include "lua_autocall_macros.h"

void lua_autocall_open(void);
void lua_autocall_close(void);

#define lua_autocall(L, func) lua_autocall_name(L, #func)
void lua_autocall_name(lua_State* L, char* func_name);

#define lua_autofunc_add_args0(L, func, ret_t) lua_autofunc_add_args0_macro(L, func, ret_t)
#define lua_autofunc_add_args0_void(L, func, ret_t) lua_autofunc_add_args0_void_macro(L, func, ret_t)
#define lua_autofunc_add_args1(L, func, ret_t, arg0_t) lua_autofunc_add_args1_macro(L, func, ret_t, arg0_t) 
#define lua_autofunc_add_args1_void(L, func, ret_t, arg0_t) lua_autofunc_add_args1_void_macro(L, func, ret_t, arg0_t) 
#define lua_autofunc_add_args2(L, func, ret_t, arg0_t, arg1_t) lua_autofunc_add_args2_macro(L, func, ret_t, arg0_t, arg1_t)
#define lua_autofunc_add_args2_void(L, func, ret_t, arg0_t, arg1_t) lua_autofunc_add_args2_void_macro(L, func, ret_t, arg0_t, arg1_t)
#define lua_autofunc_add_args3(L, func, ret_t, arg0_t, arg1_t, arg2_t) lua_autofunc_add_args3_macro(L, func, ret_t, arg0_t, arg1_t, arg2_t)
#define lua_autofunc_add_args3_void(L, func, ret_t, arg0_t, arg1_t, arg2_t) lua_autofunc_add_args3_void_macro(L, func, ret_t, arg0_t, arg1_t, arg2_t)
#define lua_autofunc_add_args4(L, func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t) lua_autofunc_add_args4_macro(L, func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t)
#define lua_autofunc_add_args4_void(L, func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t) lua_autofunc_add_args4_void_macro(L, func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t)
#define lua_autofunc_add_args5(L, func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t) lua_autofunc_add_args5_macro(L, func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t)
#define lua_autofunc_add_args5_void(L, func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t) lua_autofunc_add_args5_void_macro(L, func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t)
#define lua_autofunc_add_args6(L, func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t) lua_autofunc_add_args6_macro(L, func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t)
#define lua_autofunc_add_args6_void(L, func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t) lua_autofunc_add_args6_void_macro(L, func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t)
#define lua_autofunc_add_args7(L, func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t) lua_autofunc_add_args7_macro(L, func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t)
#define lua_autofunc_add_args7_void(L, func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t) lua_autofunc_add_args7_void_macro(L, func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t)
#define lua_autofunc_add_args8(L, func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t) lua_autofunc_add_args8_macro(L, func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t)
#define lua_autofunc_add_args8_void(L, func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t) lua_autofunc_add_args8_void_macro(L, func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t)
#define lua_autofunc_add_args9(L, func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t, arg8_t) lua_autofunc_add_args9_macro(L, func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t, arg8_t)
#define lua_autofunc_add_args9_void(L, func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t, arg8_t) lua_autofunc_add_args9_void_macro(L, func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t, arg8_t)
#define lua_autofunc_add_args10(L, func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t, arg8_t, arg9_t) lua_autofunc_add_args10_macro(L, func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t, arg8_t, arg9_t)
#define lua_autofunc_add_args10_void(L, func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t, arg8_t, arg9_t) lua_autofunc_add_args10_void_macro(L, func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t, arg8_t, arg9_t)

typedef void (*lua_autofunc)(void*,void*);

void lua_autofunc_add_typeid(lua_State* L, lua_autofunc ac_func, char* name, lua_autotype ret_tid, int num_args, ...);


#endif