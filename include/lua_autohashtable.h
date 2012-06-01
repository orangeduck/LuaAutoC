#ifndef lua_autohashtable_h
#define lua_autohashtable_h

typedef struct lua_autobucket {
  void* item;
  char* string;
  struct lua_autobucket* next;
  struct lua_autobucket* prev;
} lua_autobucket;


typedef struct {
  lua_autobucket** buckets;
  int size;
} lua_autohashtable;


lua_autohashtable* lua_autohashtable_new(int table_size);
void lua_autohashtable_delete(lua_autohashtable* ht);

int lua_autohashtable_contains(lua_autohashtable* ht, char* string);
void* lua_autohashtable_get(lua_autohashtable* ht, char* string);
void lua_autohashtable_set(lua_autohashtable* ht, char* string, void* item);

char* lua_autohashtable_find(lua_autohashtable* ht, void* item);

void lua_autohashtable_map(lua_autohashtable* ht, void (*func)(void*));

#endif