#pragma once

#include <cstdint>
#include <string>

using Bitboard = std::uint64_t;

enum Color : int { WHITE, BLACK };

enum PieceType : int { PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING };

// Piece = color * 6 + piece type. Indexes Board::pieces[].
enum Piece : int {
  W_PAWN, W_KNIGHT, W_BISHOP, W_ROOK, W_QUEEN, W_KING,
  B_PAWN, B_KNIGHT, B_BISHOP, B_ROOK, B_QUEEN, B_KING,
  NO_PIECE
};

// Squares are 0..63, a1 = 0, b1 = 1, ..., h8 = 63.
using Square = int;
constexpr Square NO_SQUARE = 64;

constexpr int file_of(Square s) { return s & 7; }
constexpr int rank_of(Square s) { return s >> 3; }
constexpr Square make_square(int file, int rank) { return rank * 8 + file; }
constexpr Bitboard bb(Square s) { return Bitboard{1} << s; }

constexpr Color color_of(Piece p) { return p < B_PAWN ? WHITE : BLACK; }
constexpr PieceType type_of(Piece p) { return PieceType(p % 6); }
constexpr Piece make_piece(Color c, PieceType t) { return Piece(c * 6 + t); }

// Castling rights bitmask.
enum Castling : int { WK = 1, WQ = 2, BK = 4, BQ = 8 };

// Move packed into 16 bits: from (6) | to (6) | flags (4).
using Move = std::uint16_t;
constexpr Move NULL_MOVE = 0;

enum MoveFlag : int {
  QUIET = 0, DOUBLE_PUSH = 1, KING_CASTLE = 2, QUEEN_CASTLE = 3,
  CAPTURE = 4, EP_CAPTURE = 5,
  PROMO_N = 8, PROMO_B = 9, PROMO_R = 10, PROMO_Q = 11,
  PROMO_CAPTURE_N = 12, PROMO_CAPTURE_B = 13, PROMO_CAPTURE_R = 14, PROMO_CAPTURE_Q = 15
};

constexpr Move make_move(Square from, Square to, int flag = QUIET) {
  return Move(from | (to << 6) | (flag << 12));
}
constexpr Square move_from(Move m) { return m & 63; }
constexpr Square move_to(Move m) { return (m >> 6) & 63; }
constexpr int move_flag(Move m) { return m >> 12; }

inline std::string square_to_string(Square s) {
  return {char('a' + file_of(s)), char('1' + rank_of(s))};
}
