#ifndef lua_autostruct_h
#define lua_autostruct_h

#include "lua_autotype.h"

void lua_autostruct_open(void);
void lua_autostruct_close(void);

#define lua_autostruct_push_member(L, type, cstruct, member) lua_autostruct_push_member_typeid(L, lua_typeid(type), cstruct, member)
void lua_autostruct_push_member_typeid(lua_State* L, lua_autotype type, void* cstruct, char* member);

#define lua_autostruct_pop_member(L, type, cstruct, member) lua_autostruct_pop_member_typeid(L, lua_typeid(type), cstruct, member)
void lua_autostruct_pop_member_typeid(lua_State* L, lua_autotype type, void* cstruct, char* member);

#define lua_autostruct_has_member(L, type, member) lua_autostruct_has_member_typeid(L, lua_typeid(type), member)
int lua_autostruct_has_member_typeid(lua_State* L, lua_autotype type,  char* member);

#define lua_autostruct_add(L, type) lua_autostruct_add_typid(L, lua_typeid(type))
void lua_autostruct_add_typid(lua_State* L, lua_autotype type);

#define lua_autostruct_addmember(L, type, member, member_type) lua_autostruct_addmember_typeid(L, lua_typeid(type), #member, lua_typeid(member_type), ((long)&(((type*)0)->member)))
void lua_autostruct_addmember_typeid(lua_State* L, lua_autotype type, char* member, lua_autotype member_type, int offset);

#define lua_autostruct_added(L, type) lua_autostruct_added_typeid(L, lua_typeid(type))
int lua_autostruct_added_typeid(lua_State* L, lua_autotype type);

#define lua_autostruct_push(L, type, c_in) lua_autostruct_push_typeid(L, lua_typeid(type), c_in)
void lua_autostruct_push_typeid(lua_State* L, lua_autotype type, void* c_in);

#define lua_autostruct_pop(L, type, c_out) lua_autostruct_pop_typeid(L, lua_typeid(type), pyobj, c_out)
void lua_autostruct_pop_typeid(lua_State* L, lua_autotype type, void* c_out);

#endif