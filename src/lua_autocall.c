#include <stdlib.h>
#include <string.h>

#include "lua_autohashtable.h"
#include "lua_autostack.h"

#include "lua_autocall.h"

#define MAX_ARG_NUM 10

typedef struct {
  char* name;
  lua_autofunc ac_func;
  void* func;
  lua_autotype type_id;
  int num_args;
  lua_autotype arg_types[MAX_ARG_NUM];
} func_entry;

static lua_autohashtable* func_table;

void lua_autocall_open(void) {
  func_table = lua_autohashtable_new(1024);
}

static void func_entry_delete(func_entry* fe) {
  free(fe->name);
  free(fe);
}

void lua_autocall_close(void) {
  lua_autohashtable_map(func_table, (void(*)(void*))func_entry_delete);
  lua_autohashtable_delete(func_table);
}

static int total_arg_size(func_entry* fe) {
  
  int total = 0;
  for(int i = 0; i < fe->num_args; i++) {
    total += lua_autotype_size(fe->arg_types[i]);
  }
  return total;
  
}

#define ret_stack_size 128
#define arg_stack_size 1024

static char ret_stack[ret_stack_size];
static void* ret_stack_ptr = ret_stack;

static char arg_stack[arg_stack_size];
static void* arg_stack_ptr = arg_stack;

static int ret_stack_space() {
  return (void*)ret_stack - ret_stack_ptr + ret_stack_size;
}

static int arg_stack_space() {
  return (void*)arg_stack - arg_stack_ptr + arg_stack_size;
}

static void lua_autocall_entry(lua_State* L, func_entry* fe) {
  
  int ret_data_size = lua_autotype_size(fe->type_id);
  int arg_data_size = total_arg_size(fe);
  
  int ret_using_heap = 0; int arg_using_heap = 0;
  void* ret_data = ret_stack_ptr;
  void* arg_data = arg_stack_ptr;
  
  if (ret_data_size > ret_stack_space()) {
    ret_using_heap = 1; ret_data = malloc(ret_data_size);
  }
  
  if (arg_data_size > arg_stack_space()) {
    arg_using_heap = 1; arg_data = malloc(arg_data_size);
  }
  
  /* Pop args in reverse order but place in memory in forward order */
  
  void* arg_top = arg_data + arg_data_size;
  
  for(int j = fe->num_args-1; j >= 0; j--) { 
    arg_top -= lua_autotype_size(fe->arg_types[j]);
    lua_autopop_typeid(L, fe->arg_types[j], arg_top);
  }
  
  arg_data += arg_data_size;
  ret_data += ret_data_size;
  
  /* If not using heap update stack pointers */
  if (!ret_using_heap) { ret_stack_ptr = ret_data; }
  if (!arg_using_heap) { arg_stack_ptr = arg_data; }
  
  arg_data -= arg_data_size;
  ret_data -= ret_data_size;
  
  fe->ac_func(ret_data, arg_data);
  lua_autopush_typeid(L, fe->type_id, ret_data);
  
  /* Either free heap data or reduce stack pointers */
  if (ret_using_heap) { free(ret_data); } else { ret_stack_ptr -= ret_data_size; } 
  if (arg_using_heap) { free(arg_data); } else { arg_stack_ptr -= arg_data_size; }
  
}

void lua_autocall_name(lua_State* L, char* func_name) {

  func_entry* fe = lua_autohashtable_get(func_table, func_name);
  if (fe != NULL) {
    return lua_autocall_entry(L, fe);
  }
  
  lua_pushfstring(L, "lua_autocall: Function '%s' is not registered!", func_name);
  lua_error(L);  
}

void lua_autofunc_add_typeid(lua_State* L, lua_autofunc ac_func, char* name, lua_autotype ret_tid, int num_args, ...) {

  if (num_args >= MAX_ARG_NUM) {
    lua_pushfstring(L, "lua_autocall: Function has %i arguments - maximum supported is %i!", num_args, MAX_ARG_NUM);
    lua_error(L);  
  }
  
  func_entry* fe = malloc(sizeof(func_entry));
  fe->name = malloc(strlen(name) + 1);
  strcpy(fe->name, name);
  fe->ac_func = ac_func;
  fe->type_id = ret_tid;
  fe->num_args = num_args;
  
  va_list argl;
  va_start(argl, num_args);
  for(int i = 0; i < num_args; i++) {
    fe->arg_types[i] = va_arg(argl, lua_autotype);
  }
  
  lua_autohashtable_set(func_table, name, fe);

}