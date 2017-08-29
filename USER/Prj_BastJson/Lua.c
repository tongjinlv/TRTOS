/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
http://www.trtos.com/
**************************************************************************************/
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include "luaconf.h"
void exit();
static int average(lua_State *L)
{
return 2;
}

static int Lsleep(lua_State *L){

  return 1;
}
  
static int Lmyputs0(lua_State *L)
{
	char *buf;
	int len;

	buf=(char *)lua_tostring(L,1);
	len=lua_tonumber(L, 2);
	buf[len]=0;
	//DeBug(buf,4);
	lua_pushnumber(L, 1);
	return 1;
}


void Task_Lua(void *Tags)
	
{
	
	const char buffer[] = {"Lmyputs0(1,\"Hello,I am lua!\")"};
	lua_State *L;
	L= luaL_newstate();
	luaL_openlibs(L);
	luaopen_base(L);
	lua_register(L, "average", average);     
	lua_register(L, "Lsleep", Lsleep);
	lua_register(L, "Lmyputs0", Lmyputs0);   
	luaL_dostring(L, buffer);
	while(1)
	{
		//luaL_dostring(L, buffer);
		Tos_TaskDelay(100);
		DeBug("ddddddddddddddddd=%d",6,4);
	}
	lua_close(L);
}
int main()
{
	Task_Lua(0);
}