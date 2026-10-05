#pragma once

#include <string>

#include "types.h"

constexpr const char* START_FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

struct Board {
  Bitboard pieces[12] = {};  // one bitboard per Piece
  Bitboard occupied[2] = {}; // per color
  Piece mailbox[64];         // piece on each square, NO_PIECE if empty

  Color side = WHITE;
  int castling = 0;          // Castling bitmask
  Square ep = NO_SQUARE;     // en passant target square
  int halfmove = 0;
  int fullmove = 1;

  Board() { set_fen(START_FEN); }

  // Returns false if the FEN could not be parsed.
  bool set_fen(const std::string& fen);
  std::string fen() const;
  void print() const;

  Bitboard all() const { return occupied[WHITE] | occupied[BLACK]; }

  void put_piece(Piece p, Square s);
  void remove_piece(Square s);
};
