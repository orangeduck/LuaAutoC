#include "../lautoc.h"

typedef enum {
  DIAMONDS,
  HEARTS,
  CLUBS,
  SPADES,
  INVALID = -1
} cards;

int main(int argc, char **argv) {
	
  lua_State* L = luaL_newstate();
  
  luaA_open(L);

  luaA_enum(L, cards);
  luaA_enum_value(L, cards, DIAMONDS);
  luaA_enum_value(L, cards, HEARTS);
  luaA_enum_value(L, cards, CLUBS);
  luaA_enum_value(L, cards, SPADES);
  luaA_enum_value(L, cards, INVALID);
  luaA_enum_value_name(L, cards, SPADES, "ESPADIA");

  cards test = INVALID;
  
  luaA_push(L, cards, &test);
  lua_pop(L, 1);
  
  lua_pushstring(L, "INVALID");
  luaA_to(L, cards, &test, -1);
  printf("INVALID read back as %i\n", test); 
  lua_pop(L, 1);
  
  luaA_close(L);
  lua_close(L);
	
  return 0;
}
