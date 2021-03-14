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

#ifndef TDENGINE_QSCRIPT_H
#define TDENGINE_QSCRIPT_H

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <openssl/sha.h>

lua_State* CreateLuaEnv();
void qDestroyLuaEnv(lua_State *state);

#endif //TDENGINE_QSCRIPT_H 
