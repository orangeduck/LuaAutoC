#include <stdlib.h>
#include <string.h>

#include "lua.h"
#include "lua_autohashtable.h"
#include "lua_autotype.h"
#include "lua_autostack.h"

#include "lua_autostruct.h"

typedef struct {
  lua_autotype type;
  int offset;
  char* name;
} struct_member_entry;

typedef struct {
  lua_autotype type_id;
  int num_members;
  int num_reserved_members;
  struct_member_entry** members;
} struct_entry;

static lua_autohashtable* struct_table;

void lua_autostruct_open(void) {
  struct_table = lua_autohashtable_new(256);
}

static void struct_entry_delete(struct_entry* se) {

  for(int i = 0; i < se->num_members; i++) {
    free(se->members[i]->name);
    free(se->members[i]);
  }
  
  free(se->members);
  free(se);
  
}

void lua_autostruct_close(void) {

  lua_autohashtable_map(struct_table, (void(*)(void*))struct_entry_delete);
  lua_autohashtable_delete(struct_table);

}

void lua_autostruct_push_member_typeid(lua_State* L, lua_autotype type, void* cstruct, char* member) {

  struct_entry* se = lua_autohashtable_get(struct_table, lua_autotype_name(type));
  if (se != NULL) {
  
    for(int j = 0; j < se->num_members; j++) {
    if (strcmp(se->members[j]->name, member) == 0) {
      struct_member_entry* sme = se->members[j];
      return lua_autopush_typeid(L, sme->type, cstruct+sme->offset);
    }
    }
    
    lua_pushfstring(L, "lua_autostruct: Member '%s' not registered for struct '%s'!", member, lua_autotype_name(type));
    lua_error(L);  
  }
  
  lua_pushfstring(L, "lua_autostruct: Struct '%s' not registered!", lua_autotype_name(type));
  lua_error(L);
}

void lua_autostruct_pop_member_typeid(lua_State* L, lua_autotype type, void* cstruct, char* member) {

  struct_entry* se = lua_autohashtable_get(struct_table, lua_autotype_name(type));
  if (se != NULL) {
    
    for(int j = 0; j < se->num_members; j++) {
    if (strcmp(se->members[j]->name, member) == 0) {
      struct_member_entry* sme = se->members[j];
      return lua_autopop_typeid(L, sme->type, cstruct+sme->offset);
    }
    }
    
    lua_pushfstring(L, "lua_autostruct: Member '%s' not registered for struct '%s'!", member, lua_autotype_name(type));
    lua_error(L);  
  }
  
  lua_pushfstring(L, "lua_autostruct: Struct '%s' not registered!", lua_autotype_name(type));
  lua_error(L);
}

int lua_autostruct_has_member_typeid(lua_State* L, lua_autotype type,  char* member) {

  struct_entry* se = lua_autohashtable_get(struct_table, lua_autotype_name(type));
  if (se != NULL) {
  
    for(int j = 0; j < se->num_members; j++) {
    if (strcmp(se->members[j]->name, member) == 0) {
      return 1;
    }
    }
    
    return 0;
  }
  
  lua_pushfstring(L, "lua_autostruct: Struct '%s' not registered!", lua_autotype_name(type));
  lua_error(L);
  return 0;
}

void lua_autostruct_add_typid(lua_State* L, lua_autotype type) {

  struct_entry* se = malloc(sizeof(struct_entry));
  se->type_id = type;
  se->num_members = 0;
  se->num_reserved_members = 32;
  se->members = malloc(sizeof(struct_member_entry*) * se->num_reserved_members);
  
  lua_autohashtable_set(struct_table, lua_autotype_name(type), se);

}

void lua_autostruct_addmember_typeid(lua_State* L, lua_autotype type, char* member, lua_autotype member_type, int offset) {

  struct_entry* se = lua_autohashtable_get(struct_table, lua_autotype_name(type));
  if (se != NULL) {
    
    if (se->num_members >= se->num_reserved_members) {
      se->num_reserved_members += 32;
      se->members = realloc(se->members, sizeof(struct_member_entry*) * se->num_reserved_members);
    }
    
    struct_member_entry* sme = malloc(sizeof(struct_member_entry));
    sme->type = member_type;
    sme->offset = offset;
    sme->name = malloc(strlen(member) + 1);
    strcpy(sme->name, member);
    
    se->members[se->num_members] = sme;
    se->num_members++;
    return;
    
  }
  
  lua_pushfstring(L, "lua_autostruct: Struct '%s' not registered!", lua_autotype_name(type));
  lua_error(L);
}

int lua_autostruct_added_typeid(lua_State* L, lua_autotype type) {

  struct_entry* se = lua_autohashtable_get(struct_table, lua_autotype_name(type));
  if (se == NULL) { return 0; } else { return 1; }

}

void lua_autostruct_push_typeid(lua_State* L, lua_autotype type, void* c_in) {

  struct_entry* se = lua_autohashtable_get(struct_table, lua_autotype_name(type));
  if (se != NULL) {
    
    lua_newtable(L);
    
    for(int j = 0; j < se->num_members; j++) {
      struct_member_entry* sme = se->members[j];
      lua_autostruct_push_member_typeid(L, type, c_in, sme->name);
      lua_setfield(L, -2, sme->name);
    }
    
    return;
  }
  
  lua_pushfstring(L, "lua_autostruct: Struct '%s' not registered!", lua_autotype_name(type));
  lua_error(L);

}

void lua_autostruct_pop_typeid(lua_State* L, lua_autotype type, void* c_out) {

  struct_entry* se = lua_autohashtable_get(struct_table, lua_autotype_name(type));
  if (se != NULL) {
  
    for(int j = 0; j < se->num_members; j++) {
      struct_member_entry* sme = se->members[j];
      lua_getfield(L, -1, sme->name);
      lua_autostruct_pop_member_typeid(L, type, c_out, sme->name);
    }
    
    lua_pop(L, 1);
    return;
  }
  
  lua_pushfstring(L, "lua_autostruct: Struct '%s' not registered!", lua_autotype_name(type));
  lua_error(L);

}
