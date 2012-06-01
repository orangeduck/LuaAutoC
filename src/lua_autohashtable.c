#include <stdlib.h>
#include <string.h>

#include "lua_autohashtable.h"

static int hash(const char* s, int size) {
  int h = 0;
  while (*s) h = h * 101 + *s++;
  return abs(h) % size;
}

static lua_autobucket* lua_autobucket_new(const char* string, void* item) {
  
  lua_autobucket* b = malloc(sizeof(lua_autobucket));
  b->item = item;
  
  b->string = malloc(strlen(string) + 1);
  strcpy(b->string, string);
  
  b->next = NULL;
  b->prev = NULL;
  
  return b;
}

static void lua_autobucket_delete(lua_autobucket* b) {
  if(b->next != NULL) { lua_autobucket_delete(b->next); }
  free(b->string);
  free(b);
}

lua_autohashtable* lua_autohashtable_new(int size) {

  lua_autohashtable* ht = malloc(sizeof(lua_autohashtable));
  
  ht->size = size;
  ht->buckets = malloc( sizeof(lua_autobucket*) * ht->size );
  
  for(int i = 0; i < size; i++) { ht->buckets[i] = NULL; }
  
  return ht;
}

void lua_autohashtable_delete(lua_autohashtable* ht) {
  for(int i=0; i< ht->size; i++) {
    if (ht->buckets[i] != NULL) {
      lua_autobucket_delete(ht->buckets[i]);
    }
  }
  free(ht->buckets);
  free(ht);
}

int lua_autohashtable_contains(lua_autohashtable* ht, const char* string) {

  if (lua_autohashtable_get(ht, string) == NULL) {
    return 0;
  } else {
    return 1;
  }

}

void* lua_autohashtable_get(lua_autohashtable* ht, const char* string) {

  int index = hash(string, ht->size);
  lua_autobucket* b = ht->buckets[index];
  
  if (b == NULL) {
    return NULL;
  }
  
  while(1){
    if (strcmp(b->string, string) == 0){ return b->item; }
    if (b->next == NULL) { return NULL; }
    else {b = b->next; }
  }
  
  return NULL;

}

void lua_autohashtable_set(lua_autohashtable* ht, const char* string, void* item) {

  int index = hash(string, ht->size);
  lua_autobucket* b = ht->buckets[index];
  
  if (b == NULL) {
    lua_autobucket* new_bucket = lua_autobucket_new(string, item);
    ht->buckets[index] = new_bucket;
    return;
  }
  
  while(1) {
    
    if( strcmp(b->string, string) == 0) {
      b->item = item;
      return;
    }
  
    if( b->next == NULL) {    
      lua_autobucket* new_bucket = lua_autobucket_new(string, item);
      b->next = new_bucket;
      new_bucket->prev = b;
      return;
    }
  
    b = b->next;
  }

}

char* lua_autohashtable_find(lua_autohashtable* ht, void* item) {

  for(int i = 0; i < ht->size; i++) {
    lua_autobucket* b = ht->buckets[i];
    while (b != NULL) {
      if (b->item == item) { return b->string; }
      b = b->next;
    }
  }
  
  return NULL; 
}

void lua_autohashtable_map(lua_autohashtable* ht, void (*func)(void*)) {

  for(int i = 0; i < ht->size; i++) {
    lua_autobucket* b = ht->buckets[i];
    while (b != NULL) {
      func(b->item);
      b = b->next;
    }
  }
}

