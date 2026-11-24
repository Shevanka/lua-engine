# Lua Engine

A small scripting engine written in C that embeds **Lua 5.4**. The C host creates a
Lua state, exposes its own functions to Lua through an `Engine` table, and can either
run a `.lua` script or start an interactive REPL.

This project demonstrates how a native application (for example a game engine) lets
gameplay logic be written in a scripting language while core functionality stays in C.

---

## Features

- Embeds the Lua 5.4 interpreter through the C API
- Exposes C functions to Lua as `Engine.log`, `Engine.getTime`, `Engine.add` and `Engine.readFile`
- Runs a script file, or starts a REPL when no file is given
- Reports Lua runtime and syntax errors without crashing the host
- Includes an example text-based farming game written entirely in Lua

---

## How It Works

```text
            main.c
               │  engine_init()
               ▼
   engine.c ── luaL_newstate() + luaL_openlibs()
               │  engine_register_bindings()
               ▼
  bindings.c ── creates global table "Engine" with C functions
               │
               ▼
  scripts/*.lua ── call Engine.log(), Engine.add(), ... like normal Lua functions
```

Each binding follows the Lua C API convention: read arguments from the Lua stack,
push results back onto the stack, and return the number of results.

```c
static int binding_get_time(lua_State *L)
{
    lua_pushinteger(L, (lua_Integer)time(NULL));
    return 1; // one value returned to Lua
}
```

---

## Lua API

| Function | Returns | Description |
| :--- | :--- | :--- |
| `Engine.log(message)` | nothing | Prints `message` with a `[LOG]` prefix |
| `Engine.getTime()` | integer | Current Unix timestamp |
| `Engine.add(a, b)` | number | Adds two numbers; integer + integer stays an integer |
| `Engine.readFile(path)` | string or `nil` | Whole file contents, or `nil` if the file cannot be opened |

The full Lua standard library (`print`, `math`, `string`, `io`, ...) is also available.

---

## Requirements

- GCC
- Lua 5.4 development headers and library
- `make`

On Ubuntu/Debian (or WSL on Windows):

```bash
sudo apt install build-essential liblua5.4-dev
```

---

## Build and Run

```bash
git clone https://github.com/Shevanka/lua-engine.git
cd lua-engine
make
```

Run a script:

```bash
./lua-engine scripts/hello.lua
# or
make run SCRIPT=scripts/hello.lua
```

Start the interactive REPL (type `exit` to quit):

```bash
./lua-engine
lua> print(Engine.add(10, 32))
42
lua> exit
```

Remove the binary:

```bash
make clean
```

---

## Example Scripts

### `scripts/hello.lua`

Calls every binding once. Expected output:

```text
[ENGINE] Bindings berhasil didaftarkan.
[ENGINE] Lua engine berhasil diinisialisasi.
[MAIN] Menjalankan script: scripts/hello.lua
[LOG] Halo dari Lua script!
[LOG] Unix timestamp sekarang: 1795525227
[LOG] Hasil 10 + 32 = 42
[LOG] Isi file berhasil dibaca.
Ini print bawaan Lua: 12.0
[ENGINE] Lua engine dimatikan.
```

### `scripts/farm_world.lua`

A menu-driven mini farming game that shows Lua tables, functions and loops:

- view and move the player position
- view the inventory and check item amounts
- print the 5×5 world map and hit tiles (dirt / tree)

```text
=== MINI FARM WORLD ===
1. Lihat posisi player
2. Jalan ke koordinat
3. Lihat inventory
4. Cek jumlah item
5. Lihat map
6. Pukul tile
7. Keluar
```

---

## Project Structure

```text
lua-engine/
├── src/
│   ├── main.c        # Entry point: script mode or REPL
│   ├── engine.c/.h   # Lua state lifecycle and script execution
│   └── bindings.c/.h # C functions exposed to Lua
├── scripts/
│   ├── hello.lua     # Binding demo
│   └── farm_world.lua# Mini farming game
├── Makefile
└── LICENSE
```

---

## Adding a New Binding

1. Write a function with the signature `static int name(lua_State *L)` in `src/bindings.c`.
2. Register it inside `engine_register_bindings()`:

   ```c
   lua_pushcfunction(L, binding_name);
   lua_setfield(L, -2, "name"); // Engine.name
   ```

3. Rebuild with `make` and call `Engine.name(...)` from any script.

---

## License

[MIT](LICENSE)
