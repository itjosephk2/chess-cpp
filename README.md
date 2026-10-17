# Chess

A chess engine written in C++ from scratch, as a way to learn the language. The
board is a flattened 8×8 array (`square = row * cols + col`), which makes it
good practice for how matrices and tensors are laid out in memory.

- `engine/` — C++20 chess engine (will speak UCI)
- `web/` — browser UI (Vite + TypeScript, chessground, chess.js)

## Engine

### Layout

```
engine/
  CMakeLists.txt
  src/
    board.h       constants (board size, pieces) and board function declarations
    board.cpp     the model: setup, moves, square conversion (never prints)
    display.h     terminal view declarations
    display.cpp   the view: prints the board to the terminal
    main.cpp      the game loop
```

Each `.h` says what exists, its `.cpp` says how it works, and any file that
needs those functions includes the `.h`. Keeping `main` separate means tests
can use the board code without starting a game. Keeping printing out of
`board.cpp` means the board code works with any view: the terminal now, the
web UI later.

### Build and run

With CMake:

```sh
cd engine
cmake -B build -G Ninja
cmake --build build
./build/engine
```

Or compile directly, without CMake. Every `.cpp` file is listed, and the
compiler links them into one program:

```sh
cd engine
mkdir -p build
c++ -std=c++20 -Wall -Wextra src/main.cpp src/board.cpp src/display.cpp -o build/engine
./build/engine
```

On Windows the program is `build\engine.exe`.

### What it does so far

- Board stored as a `char` array of 64 squares, using FEN letters (uppercase = white, lowercase = black)
- Sets up the starting position and prints the board
- Game loop: type moves like `e2e4`, or `quit` to exit
- Checks that input names real squares, and only lets you move your own pieces
- Converts between square names and board indexes in both directions:
  - `parse_square`: `"e2"` → `12` (flatten)
  - `square_to_row` / `square_to_col`: `12` → row `1`, column `4` (unflatten)
  - `square_name`: `12` → `"e2"`

No chess rules yet: any piece can move to any square that isn't one of your own pieces.

## Web

```sh
cd web
npm install
npm run dev
```

Currently plays against a random mover (`web/src/engine.ts`) until the engine is compiled to WASM.

## Roadmap

0. Board representation, FEN parsing, UCI loop *(in progress: board, game loop, square conversion, and the board / display split done)*
1. Move generation (bitboards) + `make_move` / `unmake_move`
2. `perft` command, verified against known node counts
3. Search: negamax + alpha-beta, iterative deepening, time management
4. Evaluation: material + piece-square tables
5. Build to WASM with Emscripten, run in a Web Worker, swap out `RandomEngine`
6. Test strength changes with fastchess

### Next up

- Unit tests in `engine/tests/`, starting with a round-trip check that every square survives `square_name` → `parse_square`
- Knight moves, using offsets with edge checks so moves don't wrap around the board
