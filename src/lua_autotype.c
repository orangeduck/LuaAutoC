#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "lua_autotype.h"

typedef char* type_name;
typedef int type_size;

static type_name* type_names;
static type_size* type_sizes;

static int num_types = 0;
static int num_reserved_types = 128;

void lua_autotype_open(void) {
  
  type_names = malloc(sizeof(type_name) * num_reserved_types);
  type_sizes = malloc(sizeof(type_size) * num_reserved_types);
}

void lua_autotype_close(void) {
  
  for(int i = 0; i < num_types; i++) {
    free(type_names[i]);
  }
  
  free(type_names);
  free(type_sizes);
}

lua_autotype lua_autotype_push(char* type, int size) {
  
  for(int i = 0; i < num_types; i++) {
    if (strcmp(type, type_names[i]) == 0) return i;
  }
  
  if (num_types >= num_reserved_types) {
    num_reserved_types += 128;
    type_names = realloc(type_names, sizeof(type_name) * num_reserved_types);
    type_sizes = realloc(type_sizes, sizeof(type_size) * num_reserved_types);
  }
  
  type_names[num_types] = malloc(strlen(type)+1);
  strcpy(type_names[num_types], type);
  type_sizes[num_types] = size;
  num_types++;
  
  return num_types-1;
}

lua_autotype lua_autotype_find(char* type) {

  for(int i = 0; i < num_types; i++) {
    if (strcmp(type, type_names[i]) == 0) return i;
  }
  
  return -1;
}

char* lua_autotype_name(lua_autotype id) {
  if (id == -1) return "Unknown Type";
  return type_names[id];
}

int lua_autotype_size(lua_autotype id) {
  if (id == -1) return -1;
  return type_sizes[id];
}
