/*
 * Copyright (c) 2019 TAOS Data, Inc. <jhtao@taosdata.com>
 *
 * This program is free software: you can use, redistribute, and/or modify
 * it under the terms of the GNU Affero General Public License, version 3
 * or later ("AGPL"), as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "os.h"
#include "qScript.h"
#include "ttype.h"
#include "tstrbuild.h"
#include "tsha1.h"

void luaLoadLib(lua_State *lua, const char *libname, lua_CFunction luafunc) {
  lua_pushcfunction(lua, luafunc);
  lua_pushstring(lua, libname);
  lua_call(lua, 1, 0);
}
LUALIB_API int (luaopen_cjson) (lua_State *L);
LUALIB_API int (luaopen_struct) (lua_State *L);
LUALIB_API int (luaopen_cmsgpack) (lua_State *L);
LUALIB_API int (luaopen_bit) (lua_State *L);

static void luaLoadLibraries(lua_State *lua) {
  luaLoadLib(lua, "", luaopen_base);
  luaLoadLib(lua, LUA_TABLIBNAME, luaopen_table);
  luaLoadLib(lua, LUA_STRLIBNAME, luaopen_string);
  luaLoadLib(lua, LUA_MATHLIBNAME, luaopen_math);
  luaLoadLib(lua, LUA_DBLIBNAME, luaopen_debug);
  luaLoadLib(lua, "cjson", luaopen_cjson);
  luaLoadLib(lua, "struct", luaopen_struct);
  luaLoadLib(lua, "cmsgpack", luaopen_cmsgpack);
  luaLoadLib(lua, "bit", luaopen_bit);
}
static void luaRemoveUnsupportedFunctions(lua_State *lua) {
  lua_pushnil(lua);
  lua_setglobal(lua,"loadfile");
  lua_pushnil(lua);
  lua_setglobal(lua,"dofile");
}

void taosValueToLuaType(lua_State *lua, char *val, int32_t type) {
  //TODO(dengyihao): handle more data type
  if (IS_SIGNED_NUMERIC_TYPE(type) || type == TSDB_DATA_TYPE_BOOL) {
    int64_t v;
    GET_TYPED_DATA(v, int64_t, type, val);
    lua_pushnumber(lua, (lua_Number)v);  
  } else if (IS_UNSIGNED_NUMERIC_TYPE(type)) {
    uint64_t v;
    GET_TYPED_DATA(v, uint64_t, type, val);
    lua_pushnumber(lua,(lua_Number)v);  
  } else if (IS_FLOAT_TYPE(type)) {
    double v; 
    GET_TYPED_DATA(v, double, type, val);
    lua_newtable(lua);
    lua_pushstring(lua,"double");
    lua_pushnumber(lua,v); 
    lua_settable(lua,-3);
  } else if (type == TSDB_DATA_TYPE_BINARY) {
    lua_pushlstring(lua, val, varDataLen(val));       
  } else if (type == TSDB_DATA_TYPE_NCHAR) {
  } 
} 

void sha1hex(char *digest, const char *script, size_t len) {
  SHA1_CTX ctx;
  unsigned char hash[20];
  char *cset = "0123456789abcdef";
  int j;

  SHA1Init(&ctx);
  SHA1Update(&ctx,(unsigned char*)script,len);
  SHA1Final(hash,&ctx);

  for (j = 0; j < 20; j++) {
    digest[j*2] = cset[((hash[j]&0xF0)>>4)];
    digest[j*2+1] = cset[(hash[j]&0xF)];
  }
  digest[40] = '\0';
}

bool loadCreateFunction(lua_State *lua, const char *str) {
  char funcName[64];
  memcpy(funcName, "taos_",  5);
  sha1hex(funcName + strlen(str), str, strlen(str));
  
  /* construct lua script */
  SStringBuilder sb; memset(&sb, 0, sizeof(sb)); 
  taosStringBuilderEnsureCapacity(&sb, 64);
  taosStringBuilderAppend(&sb, "function ", 9);
  taosStringBuilderAppend(&sb, funcName, strlen(funcName));
  taosStringBuilderAppend(&sb, "() ", 3);
  taosStringBuilderAppend(&sb, str, strlen(str));
  taosStringBuilderAppend(&sb, "\nend", 4); 
  
  size_t len = 0;
  char* script = taosStringBuilderGetResult(&sb, &len);
  if (luaL_loadbuffer(lua, script, len, "@user_script")) {
    lua_pop(lua, 1);
    taosStringBuilderDestroy(&sb);
    return false;
  }  
  if (lua_pcall(lua, 0, 0, 0)) {
    lua_pop(lua, 1);
    taosStringBuilderDestroy(&sb);
    return false; 
  } 
  taosStringBuilderDestroy(&sb);
  return true;
}

int luaFuncCallCommand(lua_State *lua) {
  return 1; 
}

/*
*  Initialize the scripting environment.
*/  
lua_State* qCreateLuaEnv() {
  lua_State *lua = lua_open(); 
  luaLoadLibraries(lua);
  luaRemoveUnsupportedFunctions(lua);

  lua_newtable(lua);
  lua_pushstring(lua,"call");
  lua_pushcfunction(lua,luaallCommand);
  
  lua_setglobal(lua,"taos");

  {
    char *errh_func = "local dbg = debug\n"
                      "function __taos__err__handler(err)\n"
                      "  local i = dbg.getinfo(2,'nSl')\n"
                      "  if i and i.what == 'C' then\n"
                      "    i = dbg.getinfo(3,'nSl')\n"
                      "  end\n"
                      "  if i then\n"
                      "    return i.source .. ':' .. i.currentline .. ': ' .. err\n"
                      "  else\n"
                      "    return err\n"
                      "  end\n"
                      "end\n";
    luaL_loadbuffer(lua,errh_func,strlen(errh_func),"@err_handler_def");
    lua_pcall(lua,0,0,0);
  }
  
  return lua;
}

void qDestroyLuaEnv(lua_State *lua) {
  lua_close(lua); 
}

