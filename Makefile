CC     = gcc
CFLAGS = -Wall -Wextra -I/usr/include/lua5.4
LIBS   = -llua5.4 -lm

SRC    = src/main.c src/engine.c src/bindings.c
HDR    = src/engine.h src/bindings.h
OUT    = lua-engine

.PHONY: all run clean

all: $(OUT)

# Rebuild only when a source or header file changes
$(OUT): $(SRC) $(HDR)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LIBS)

# make run                          -> interactive REPL
# make run SCRIPT=scripts/hello.lua -> run a script
run: $(OUT)
	./$(OUT) $(SCRIPT)

clean:
	rm -f $(OUT)
