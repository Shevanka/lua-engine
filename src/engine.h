#ifndef ENGINE_H
#define ENGINE_H

#include <lua5.4/lua.h>
#include <lua5.4/lauxlib.h>
#include <lua5.4/lualib.h>

// State global Lua
typedef struct
{
    lua_State *L;
    int running;
} LuaEngine;

// Inisialisasi dan shutdown engine
int engine_init(LuaEngine *engine);
void engine_shutdown(LuaEngine *engine);

// Jalankan file .lua
int engine_run_file(LuaEngine *engine, const char *filepath);

// Jalankan string Lua langsung
int engine_run_string(LuaEngine *engine, const char *code);

#endif