#include <stdio.h>
#include <time.h>
#include "bindings.h"

// -------------------------------------------------------
// Fungsi C yang bisa dipanggil dari Lua
// -------------------------------------------------------

// Engine.log("pesan") -> void
// Fungsi print kustom dengan prefix [LOG]
static int binding_log(lua_State *L)
{
    // Ambil argumen pertama sebagai string
    const char *pesan = luaL_checkstring(L, 1);
    printf("[LOG] %s\n", pesan);
    return 0; // Jumlah return value ke Lua
}

// Engine.getTime() -> number (unix timestamp)
static int binding_get_time(lua_State *L)
{
    lua_pushinteger(L, (lua_Integer)time(NULL));
    return 1; // Satu nilai dikembalikan ke Lua
}

// Engine.add(a, b) -> number
// Contoh fungsi matematika dari C
static int binding_add(lua_State *L)
{
    double a = luaL_checknumber(L, 1);
    double b = luaL_checknumber(L, 2);
    lua_pushnumber(L, a + b);
    return 1;
}

// Engine.readFile(path) -> string | nil
// Baca isi file dari C, kembalikan ke Lua
static int binding_read_file(lua_State *L)
{
    const char *path = luaL_checkstring(L, 1);
    FILE *f = fopen(path, "r");
    if (!f)
    {
        lua_pushnil(L); // Kembalikan nil jika gagal
        return 1;
    }

    // Baca seluruh isi file
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    char *buffer = (char *)malloc(size + 1);
    fread(buffer, 1, size, f);
    buffer[size] = '\0';
    fclose(f);

    lua_pushstring(L, buffer); // Kembalikan isi file ke Lua
    free(buffer);
    return 1;
}

// -------------------------------------------------------
// Daftarkan semua binding ke tabel global "Engine" di Lua
// -------------------------------------------------------
void engine_register_bindings(LuaEngine *engine)
{
    lua_State *L = engine->L;

    // Buat tabel global bernama "Engine"
    lua_newtable(L);

    // Daftarkan tiap fungsi ke dalam tabel
    lua_pushcfunction(L, binding_log);
    lua_setfield(L, -2, "log"); // Engine.log

    lua_pushcfunction(L, binding_get_time);
    lua_setfield(L, -2, "getTime"); // Engine.getTime

    lua_pushcfunction(L, binding_add);
    lua_setfield(L, -2, "add"); // Engine.add

    lua_pushcfunction(L, binding_read_file);
    lua_setfield(L, -2, "readFile"); // Engine.readFile

    // Set tabel ke global Lua dengan nama "Engine"
    lua_setglobal(L, "Engine");

    printf("[ENGINE] Bindings berhasil didaftarkan.\n");
}