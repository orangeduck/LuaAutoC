#ifndef lua_autotype_h
#define lua_autotype_h

void lua_autotype_open(void);
void lua_autotype_close(void);

typedef int lua_autotype;

#define lua_typeid(type) lua_autotype_push(#type, sizeof(type))

lua_autotype lua_autotype_push(char* type, int size);
lua_autotype lua_autotype_find(char* type);

char* lua_autotype_name(lua_autotype id);
int lua_autotype_size(lua_autotype id);

#endif