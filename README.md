# Chess

- `engine/` — C++20 UCI chess engine
- `web/` — browser UI (Vite + TypeScript, chessground, chess.js)

## Engine

```sh
cd engine
cmake -B build -G Ninja
cmake --build build
./build/engine
```

Then type UCI commands, e.g. `uci`, `position startpos`, `d`, `go`, `quit`.

## Web

```sh
cd web
npm install
npm run dev
```

Currently plays against a random mover (`web/src/engine.ts`) until the engine is compiled to WASM.

## Roadmap

1. Move generation (bitboards) + `make_move` / `unmake_move`
2. `perft` command, verified against known node counts
3. Search: negamax + alpha-beta, iterative deepening, time management
4. Evaluation: material + piece-square tables
5. Build to WASM with Emscripten, run in a Web Worker, swap out `RandomEngine`
6. Test strength changes with fastchess
