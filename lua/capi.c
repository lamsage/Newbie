#include <math.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

static int hello_sin(lua_State *L){
		double d = luaL_checknumber(L, 1);
		lua_pushnumber(L, sin(d));
		return 1;
}
static int l_map(lua_State *L) {
		int i ,n;
		luaL_checktype(L, 1, LUA_TTABLE);
		luaL_checktype(L, 2, LUA_TFUNCTION);

		n = lua_rawlen(L, 1);
		for(i = 1; i <= n; i++) {
			lua_pushvalue(L, 2);
			lua_rawgeti(L, 1, i);
			lua_call(L, 1, 1);
			lua_rawseti(L, 1, i);
		}
		return 0;
}

static const struct luaL_Reg hello_lib[] = {
		{"hello_sin" , hello_sin},
		{"l_map" , l_map},
		{NULL, NULL}
};

int luaopen_hello_lib(lua_State *L){
		luaL_newlib(L, hello_lib);
		//luaL_register(L, "hello_lib",hello_lib); // lua 5.1
		return 1;
}
