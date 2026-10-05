#include "board.h"

#include <iostream>
#include <sstream>

namespace {

const std::string PIECE_CHARS = "PNBRQKpnbrqk";

}  // namespace

void Board::put_piece(Piece p, Square s) {
  pieces[p] |= bb(s);
  occupied[color_of(p)] |= bb(s);
  mailbox[s] = p;
}

void Board::remove_piece(Square s) {
  Piece p = mailbox[s];
  if (p == NO_PIECE) return;
  pieces[p] &= ~bb(s);
  occupied[color_of(p)] &= ~bb(s);
  mailbox[s] = NO_PIECE;
}

bool Board::set_fen(const std::string& fen) {
  for (auto& b : pieces) b = 0;
  occupied[WHITE] = occupied[BLACK] = 0;
  for (auto& p : mailbox) p = NO_PIECE;

  std::istringstream ss(fen);
  std::string placement, side_str, castle_str, ep_str;
  if (!(ss >> placement >> side_str)) return false;
  ss >> castle_str >> ep_str;
  halfmove = 0;
  fullmove = 1;
  ss >> halfmove >> fullmove;

  int rank = 7, file = 0;
  for (char c : placement) {
    if (c == '/') {
      rank--;
      file = 0;
    } else if (c >= '1' && c <= '8') {
      file += c - '0';
    } else {
      auto idx = PIECE_CHARS.find(c);
      if (idx == std::string::npos || file > 7 || rank < 0) return false;
      put_piece(Piece(idx), make_square(file, rank));
      file++;
    }
  }

  side = side_str == "b" ? BLACK : WHITE;

  castling = 0;
  for (char c : castle_str) {
    if (c == 'K') castling |= WK;
    if (c == 'Q') castling |= WQ;
    if (c == 'k') castling |= BK;
    if (c == 'q') castling |= BQ;
  }

  ep = NO_SQUARE;
  if (ep_str.size() == 2) ep = make_square(ep_str[0] - 'a', ep_str[1] - '1');

  return true;
}

std::string Board::fen() const {
  std::string out;
  for (int rank = 7; rank >= 0; rank--) {
    int empty = 0;
    for (int file = 0; file < 8; file++) {
      Piece p = mailbox[make_square(file, rank)];
      if (p == NO_PIECE) {
        empty++;
        continue;
      }
      if (empty) out += char('0' + empty), empty = 0;
      out += PIECE_CHARS[p];
    }
    if (empty) out += char('0' + empty);
    if (rank) out += '/';
  }

  out += side == WHITE ? " w " : " b ";

  std::string c;
  if (castling & WK) c += 'K';
  if (castling & WQ) c += 'Q';
  if (castling & BK) c += 'k';
  if (castling & BQ) c += 'q';
  out += c.empty() ? "-" : c;

  out += ' ';
  out += ep == NO_SQUARE ? "-" : square_to_string(ep);
  out += ' ' + std::to_string(halfmove) + ' ' + std::to_string(fullmove);
  return out;
}

void Board::print() const {
  for (int rank = 7; rank >= 0; rank--) {
    std::cout << rank + 1 << "  ";
    for (int file = 0; file < 8; file++) {
      Piece p = mailbox[make_square(file, rank)];
      std::cout << (p == NO_PIECE ? '.' : PIECE_CHARS[p]) << ' ';
    }
    std::cout << '\n';
  }
  std::cout << "\n   a b c d e f g h\n\nFen: " << fen() << '\n';
}
