#ifndef luaA_call_h
#define luaA_call_h

#include "lua.h"
#include "luaA_type.h"
#include "luaA_call_macros.h"

void luaA_call_open(void);
void luaA_call_close(void);

int luaA_call(lua_State* L, void* func_ptr);
int luaA_call_name(lua_State* L, const char* func_name);

#define luaA_func_add_args0(L, func, ret_t) luaA_func_add_args0_macro(L, func, ret_t)
#define luaA_func_add_args0_void(L, func, ret_t) luaA_func_add_args0_void_macro(L, func, ret_t)
#define luaA_func_add_args1(L, func, ret_t, arg0_t) luaA_func_add_args1_macro(L, func, ret_t, arg0_t) 
#define luaA_func_add_args1_void(L, func, ret_t, arg0_t) luaA_func_add_args1_void_macro(L, func, ret_t, arg0_t) 
#define luaA_func_add_args2(L, func, ret_t, arg0_t, arg1_t) luaA_func_add_args2_macro(L, func, ret_t, arg0_t, arg1_t)
#define luaA_func_add_args2_void(L, func, ret_t, arg0_t, arg1_t) luaA_func_add_args2_void_macro(L, func, ret_t, arg0_t, arg1_t)
#define luaA_func_add_args3(L, func, ret_t, arg0_t, arg1_t, arg2_t) luaA_func_add_args3_macro(L, func, ret_t, arg0_t, arg1_t, arg2_t)
#define luaA_func_add_args3_void(L, func, ret_t, arg0_t, arg1_t, arg2_t) luaA_func_add_args3_void_macro(L, func, ret_t, arg0_t, arg1_t, arg2_t)
#define luaA_func_add_args4(L, func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t) luaA_func_add_args4_macro(L, func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t)
#define luaA_func_add_args4_void(L, func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t) luaA_func_add_args4_void_macro(L, func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t)
#define luaA_func_add_args5(L, func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t) luaA_func_add_args5_macro(L, func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t)
#define luaA_func_add_args5_void(L, func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t) luaA_func_add_args5_void_macro(L, func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t)
#define luaA_func_add_args6(L, func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t) luaA_func_add_args6_macro(L, func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t)
#define luaA_func_add_args6_void(L, func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t) luaA_func_add_args6_void_macro(L, func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t)
#define luaA_func_add_args7(L, func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t) luaA_func_add_args7_macro(L, func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t)
#define luaA_func_add_args7_void(L, func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t) luaA_func_add_args7_void_macro(L, func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t)
#define luaA_func_add_args8(L, func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t) luaA_func_add_args8_macro(L, func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t)
#define luaA_func_add_args8_void(L, func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t) luaA_func_add_args8_void_macro(L, func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t)
#define luaA_func_add_args9(L, func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t, arg8_t) luaA_func_add_args9_macro(L, func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t, arg8_t)
#define luaA_func_add_args9_void(L, func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t, arg8_t) luaA_func_add_args9_void_macro(L, func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t, arg8_t)
#define luaA_func_add_args10(L, func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t, arg8_t, arg9_t) luaA_func_add_args10_macro(L, func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t, arg8_t, arg9_t)
#define luaA_func_add_args10_void(L, func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t, arg8_t, arg9_t) luaA_func_add_args10_void_macro(L, func, ret_t, arg0_t, arg1_t, arg2_t, arg3_t, arg4_t, arg5_t, arg6_t, arg7_t, arg8_t, arg9_t)

typedef void (*luaA_Func)(void*,void*);

void luaA_func_add_typeid(lua_State* L, void* src_func, luaA_Func auto_func, char* name, luaA_Type ret_tid, int num_args, ...);


#endif