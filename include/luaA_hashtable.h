#ifndef luaA_hashtable_h
#define luaA_hashtable_h

typedef struct luaA_Bucket {
  void* item;
  char* string;
  struct luaA_Bucket* next;
  struct luaA_Bucket* prev;
} luaA_Bucket;

typedef struct {
  luaA_Bucket** buckets;
  int size;
} luaA_Hashtable;

luaA_Hashtable* luaA_hashtable_new(int table_size);
void luaA_hashtable_delete(luaA_Hashtable* ht);

int luaA_hashtable_contains(luaA_Hashtable* ht, const char* string);
void* luaA_hashtable_get(luaA_Hashtable* ht, const char* string);
void luaA_hashtable_set(luaA_Hashtable* ht, const char* string, void* item);

char* luaA_hashtable_find(luaA_Hashtable* ht, void* item);

void luaA_hashtable_map(luaA_Hashtable* ht, void (*func)(void*));

#endif