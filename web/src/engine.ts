import { Chess } from 'chess.js';

// Anything that can pick a move for a position. Moves are UCI strings
// like "e2e4" or "e7e8q", the same format a UCI engine prints after "bestmove".
export interface Engine {
  bestMove(fen: string): Promise<string>;
}

// Placeholder opponent until the C++ engine is compiled to WASM and
// wrapped in a Web Worker that speaks UCI.
export class RandomEngine implements Engine {
  async bestMove(fen: string): Promise<string> {
    const moves = new Chess(fen).moves({ verbose: true });
    const m = moves[Math.floor(Math.random() * moves.length)];
    return m.from + m.to + (m.promotion ?? '');
  }
}
