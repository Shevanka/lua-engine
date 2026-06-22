#include <stdio.h>
#include <string.h>
#include "engine.h"

int main(int argc, char *argv[])
{
    LuaEngine engine;

    // Inisialisasi engine
    if (!engine_init(&engine))
    {
        return 1;
    }

    if (argc >= 2)
    {
        // Mode: jalankan file .lua dari argumen
        printf("[MAIN] Menjalankan script: %s\n", argv[1]);
        engine_run_file(&engine, argv[1]);
    }
    else
    {
        // Mode: REPL sederhana — ketik kode Lua langsung
        printf("[MAIN] Mode interaktif. Ketik 'exit' untuk keluar.\n");
        char input[1024];

        while (1)
        {
            printf("lua> ");
            fflush(stdout);

            if (!fgets(input, sizeof(input), stdin))
                break;

            // Hapus newline di akhir
            input[strcspn(input, "\n")] = '\0';

            if (strcmp(input, "exit") == 0)
                break;

            engine_run_string(&engine, input);
        }
    }

    engine_shutdown(&engine);
    return 0;
}