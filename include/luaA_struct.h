#ifndef luaA_struct_h
#define luaA_struct_h

#include "luaA_type.h"

void luaA_struct_open(void);
void luaA_struct_close(void);

#define luaA_struct_offset(type, member) ((long)&(((type*)0)->member))

#define luaA_struct_push_member(L, type, cstruct, member) luaA_struct_push_member_offset_typeid(L, luaA_type_id(type), cstruct, luaA_struct_offset(type, member))
int luaA_struct_push_member_offset_typeid(lua_State* L, luaA_Type type, void* cstruct, int offset);

#define luaA_struct_push_member_name(L, type, cstruct, member) luaA_struct_push_member_name_typeid(L, luaA_type_id(type), cstruct, member)
int luaA_struct_push_member_name_typeid(lua_State* L, luaA_Type type, void* cstruct, const char* member);

#define luaA_struct_to_member(L, type, cstruct, member, index) luaA_struct_to_member_offset_typeid(L, luaA_type_id(type), cstruct, luaA_struct_offset(type, member), index)
void luaA_struct_to_member_offset_typeid(lua_State* L, luaA_Type type, void* cstruct, int offset, int index);

#define luaA_struct_to_member_name(L, type, cstruct, member, index) luaA_struct_to_member_name_typeid(L, luaA_type_id(type), cstruct, member, index)
void luaA_struct_to_member_name_typeid(lua_State* L, luaA_Type type, void* cstruct, const char* member, int index);

#define luaA_struct_has_member(L, type, member) luaA_struct_has_member_offset_typeid(L, luaA_type_id(type), luaA_struct_offset(type, member))
int luaA_struct_has_member_offset_typeid(lua_State* L, luaA_Type type,  int offset);

#define luaA_struct_has_member_name(L, type, member) luaA_struct_has_member_name_typeid(L, luaA_type_id(type), member)
int luaA_struct_has_member_name_typeid(lua_State* L, luaA_Type type,  const char* member);


#define luaA_struct_add(L, type) luaA_struct_add_typeid(L, luaA_type_id(type))
void luaA_struct_add_typeid(lua_State* L, luaA_Type type);

#define luaA_struct_add_member(L, type, member, member_type) luaA_struct_add_member_typeid(L, luaA_type_id(type), #member, luaA_type_id(member_type), luaA_struct_offset(type, member))
void luaA_struct_add_member_typeid(lua_State* L, luaA_Type type, const char* member, luaA_Type member_type, int offset);

#define luaA_struct_is_added(L, type) luaA_struct_is_added_typeid(L, luaA_type_id(type))
int luaA_struct_is_added_typeid(lua_State* L, luaA_Type type);


#define luaA_struct_push(L, type, c_in) luaA_struct_push_typeid(L, luaA_type_id(type), c_in)
int luaA_struct_push_typeid(lua_State* L, luaA_Type type, void* c_in);

#define luaA_struct_to(L, type, c_out, index) luaA_struct_to_typeid(L, luaA_type_id(type), pyobj, c_out, index)
void luaA_struct_to_typeid(lua_State* L, luaA_Type type, void* c_out, int index);

#endif