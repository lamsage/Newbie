#include <stdio.h>
#include <string.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <stdarg.h>

lua_State *L;
/*
void error(lua_State *L, const char *fmt, ...) {
	va_list argp;
	va_start(argp, fmt);
	vfprintf(stderr, argp);
	va_end(argp);
	lua_close(L);
	exit(EXIT_FAILURE);
}
*/
double f(double x, double y) {
	double z; 
	lua_getglobal(L, "f");
	lua_pushnumber(L, x);
	lua_pushnumber(L, y);
	lua_pcall(L, 2, 1, 0);
/*
	if(lua_pcall(L, 2, 1, 0) != 0)
		error(L, "error running function 'f': %s", lua_tostring(L, -1));
	if(!lua_sinumber(L, -1))
		error(L, "function 'f' must return a number");
*/
	z = lua_tonumber(L, -1);
	lua_pop(L, 1);
	return z;
}
int main(void)
{
	L = luaL_newstate();
	char buff[256]= "dofile(test.lua)";
	int error;
	luaL_openlibs(L);
	error = luaL_loadbuffer(L, buff, strlen(buff), "line") ||
			lua_pcall(L, 0, 0, 0);
	if(error) {
		fprintf(stderr, "%s", lua_tostring(L, -1));
	}
	printf("%f",f(1.0,2.00));
	/*
	while(fgets(buff, sizeof(buff), stdin) != NULL) {
		error = luaL_loadbuffer(L, buff, strlen(buff), "line") ||
				lua_pcall(L, 0, 0, 0);
		if(error) {
			fprintf(stderr, "%s", lua_tostring(L, -1));
			lua_pop(L, 1);
		}
	}
	*/
	lua_close(L);
	return 0;
}
