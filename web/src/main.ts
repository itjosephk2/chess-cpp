import { Chessground } from 'chessground';
import type { Api } from 'chessground/api';
import type { Key } from 'chessground/types';
import { Chess, SQUARES } from 'chess.js';
import { RandomEngine, type Engine } from './engine';

import 'chessground/assets/chessground.base.css';
import 'chessground/assets/chessground.brown.css';
import 'chessground/assets/chessground.cburnett.css';
import './style.css';

const statusEl = document.getElementById('status')!;
const fenEl = document.getElementById('fen')!;

const engine: Engine = new RandomEngine();
let chess = new Chess();
let playerColor: 'white' | 'black' = 'white';

function legalDests(): Map<Key, Key[]> {
  const dests = new Map<Key, Key[]>();
  for (const sq of SQUARES) {
    const moves = chess.moves({ square: sq, verbose: true });
    if (moves.length) dests.set(sq, moves.map((m) => m.to));
  }
  return dests;
}

function turnColor(): 'white' | 'black' {
  return chess.turn() === 'w' ? 'white' : 'black';
}

function statusText(): string {
  if (chess.isCheckmate()) return `Checkmate, ${turnColor() === 'white' ? 'black' : 'white'} wins`;
  if (chess.isDraw()) return 'Draw';
  return `${turnColor()} to move${chess.inCheck() ? ' (check)' : ''}`;
}

function sync() {
  const yourTurn = turnColor() === playerColor && !chess.isGameOver();
  ground.set({
    fen: chess.fen(),
    turnColor: turnColor(),
    check: chess.inCheck(),
    movable: { color: yourTurn ? playerColor : undefined, dests: yourTurn ? legalDests() : new Map() },
  });
  statusEl.textContent = statusText();
  fenEl.textContent = chess.fen();
}

async function engineMove() {
  if (chess.isGameOver() || turnColor() === playerColor) return;
  const uci = await engine.bestMove(chess.fen());
  const move = chess.move({ from: uci.slice(0, 2), to: uci.slice(2, 4), promotion: uci[4] });
  ground.move(move.from as Key, move.to as Key);
  sync();
}

function onUserMove(from: Key, to: Key) {
  // Auto-queen for now; add a promotion picker later.
  chess.move({ from, to, promotion: 'q' });
  sync();
  setTimeout(engineMove, 200);
}

const ground: Api = Chessground(document.getElementById('board')!, {
  movable: { free: false, showDests: true, events: { after: onUserMove } },
  highlight: { lastMove: true, check: true },
});

document.getElementById('new-game')!.addEventListener('click', () => {
  chess = new Chess();
  ground.set({ lastMove: undefined });
  sync();
  engineMove();
});

document.getElementById('flip')!.addEventListener('click', () => {
  playerColor = playerColor === 'white' ? 'black' : 'white';
  ground.set({ orientation: playerColor });
  sync();
  engineMove();
});

sync();
