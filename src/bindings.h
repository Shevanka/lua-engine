#ifndef BINDINGS_H
#define BINDINGS_H

#include "engine.h"

// Daftarkan semua fungsi C ke Lua
void engine_register_bindings(LuaEngine *engine);

#endif