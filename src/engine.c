#include <stdio.h>
#include <stdlib.h>
#include "engine.h"
#include "bindings.h"

// Inisialisasi Lua state dan buka standard library
int engine_init(LuaEngine *engine)
{
    engine->L = luaL_newstate(); // Buat Lua state baru
    if (!engine->L)
    {
        fprintf(stderr, "[ENGINE] Gagal membuat Lua state.\n");
        return 0;
    }

    luaL_openlibs(engine->L);         // Buka stdlib Lua (print, math, dsb)
    engine_register_bindings(engine); // Daftarkan fungsi C kustom ke Lua
    engine->running = 1;

    printf("[ENGINE] Lua engine berhasil diinisialisasi.\n");
    return 1;
}

// Shutdown: tutup Lua state dan bebaskan memori
void engine_shutdown(LuaEngine *engine)
{
    if (engine->L)
    {
        lua_close(engine->L);
        engine->L = NULL;
    }
    engine->running = 0;
    printf("[ENGINE] Lua engine dimatikan.\n");
}

// Jalankan file .lua — laporkan error jika gagal
int engine_run_file(LuaEngine *engine, const char *filepath)
{
    int status = luaL_dofile(engine->L, filepath);
    if (status != LUA_OK)
    {
        // Ambil pesan error dari stack Lua
        fprintf(stderr, "[SCRIPT ERROR] %s\n", lua_tostring(engine->L, -1));
        lua_pop(engine->L, 1); // Bersihkan error dari stack
        return 0;
    }
    return 1;
}

// Jalankan kode Lua dari string (berguna untuk REPL atau eval)
int engine_run_string(LuaEngine *engine, const char *code)
{
    int status = luaL_dostring(engine->L, code);
    if (status != LUA_OK)
    {
        fprintf(stderr, "[EVAL ERROR] %s\n", lua_tostring(engine->L, -1));
        lua_pop(engine->L, 1);
        return 0;
    }
    return 1;
}