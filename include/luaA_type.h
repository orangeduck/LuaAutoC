#ifndef luaA_type_h
#define luaA_type_h

void luaA_type_open(void);
void luaA_type_close(void);

typedef int luaA_Type;

#define luaA_type_assert(type) (sizeof(void*) - sizeof(struct{type* t;}))
#define luaA_type_id(type) luaA_type_add(#type, sizeof(type) + luaA_type_assert(type))

luaA_Type luaA_type_add(char* type, int size);
luaA_Type luaA_type_find(char* type);

char* luaA_type_name(luaA_Type id);
int luaA_type_size(luaA_Type id);

#endif