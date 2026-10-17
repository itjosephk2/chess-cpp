#include <iostream>
#include <string>
#include "board.h"

// Prints the board, rank 8 at the top, with rank numbers down the left.
// Arrays are not copied when passed to a function: board here is the same
// array as in main, so changes made through it would affect main's board.
void print_board(char board[]) {
  // i counts screen lines (0 = top), so (rows - 1) - i flips it into the
  // board row (rows - 1 = top row).
  for (int i = 0; i < rows; i++) {
    std::cout << rows - i << ' ';  // rank label: rows down to 1
    for (int j = 0; j < cols; j++) {
      std::cout << board[((rows - 1) - i) * cols + j] << ' ';
    }
    std::cout << "\n";
  }
}

// Prints the file letters under the board (a b c ...).
// Letters are stored in order, so 'a' + j is the j-th letter after 'a'.
// char(...) makes cout print it as a letter instead of a number.
void print_letter_rank() {
  std::cout << "  ";  // line up under the squares, past the rank labels
  for (int j = 0; j < cols; j++) {
    std::cout << char('a' + j) << ' ';
  }
}

// Clears the board and puts every piece on its starting square.
// Each row r covers squares r * cols up to (but not including) (r + 1) * cols.
void reset_board(char board[]) {
  // Clear every square.
  for (int i = 0; i < rows * cols; i++) {
    board[i] = '.';
  }

  // White pawns: row 1 (rank 2).
  for (int i = cols; i < cols * 2; i++) {
    board[i] = white_pawn;
  }

  // Black pawns: second-to-last row (rank 7).
  for (int i = cols * (rows - 2); i < cols * (rows - 1); i++) {
    board[i] = black_pawn;
  }

  // White pieces: row 0 (rank 1), where board square i matches rank slot i.
  for (int i = 0; i < cols; i++) {
    board[i] = white_pieces_rank[i];
  }

  // Black pieces: last row (rank 8). Subtract the row's first square to get
  // the slot 0..cols-1 in black_pieces_rank.
  for (int i = (rows - 1) * cols; i < rows * cols; i++) {
    board[i] = black_pieces_rank[i - (cols * (rows - 1))];
  }
}

// Moves whatever piece is on 'from' to 'to'. Anything already on 'to' is
// overwritten, so captures work automatically. Does not check if the move
// is legal.
void make_move(char board[], int from, int to) {
  // Save the piece first, so it's not lost when 'from' is emptied.
  char piece = board[from];
  board[from] = '.';
  board[to] = piece;
}

// Turns a square name like ('e', '2') into its board index (12).
// Characters are stored as numbers in order, so subtracting gives the
// distance: file - 'a' is the column (a = 0 ... h = 7) and rank - '1' is
// the row (rank 1 = row 0). Note '1' is the character (stored as 49), not
// the number 1.
int parse_square(char file, char rank) {
  // square = column + row * cols
  int square = (file - 'a') + cols * (rank - '1');

  // Test code: uncomment to print each part of the calculation.
  // std::cout << "file: " << (file - 'a') << "\n";
  // std::cout << "Rank: " << (cols * (rank - '1')) << "\n";
  // std::cout << "number of columns: " << cols << "\n";
  // std::cout << "Rank we are on: " << (rank - '1') << "\n";
  // std::cout << "square: " << file << rank << " = " << square;
  return square;
}

// Plays a move given as text, e.g. "e2e4" (from-square then to-square), for
// the player whose turn it is. Returns true if the move was played, false if
// it was refused, so the caller knows whether to switch turns.
// Text moves come from outside the program, so they are checked first.
// make_move does the actual moving.
// A string can be indexed like an array: move[0] is 'e', move[1] is '2', ...
bool play_move(char board[], std::string move, bool white_to_move) {
  if (is_valid_move(move)) {
    int from = parse_square(move[0], move[1]);
    int to = parse_square(move[2], move[3]);

    // Only move your own pieces, and never onto your own piece.
    // - from: must hold one of your pieces. An empty square ('.') is neither
    //   white nor black, so moving from an empty square is refused too.
    // - to: must NOT hold one of your pieces. Empty squares and enemy pieces
    //   (captures) are allowed. This also refuses moving to the same square
    //   (e.g. "e2e2"), since that square holds your own piece.
    if (white_to_move) {
      if (is_white_piece(board[from]) && !is_white_piece(board[to])) {
        make_move(board, from, to);
        return true;
      }
    }
    else {
      if (is_black_piece(board[from]) && !is_black_piece(board[to])) {
        make_move(board, from, to);
        return true;
      }
    }
  }
  return false;
}

// Returns true if the text names two real squares on the board, e.g. "e2e4".
// This only checks the text, not whether the move is legal in chess.
// Without it, bad input like "e2" would read past the end of the string, and
// "z9z9" or "i2e4" would give square numbers off the board (or wrap round to
// the next row), so make_move would write to the wrong place.
// Uses rows and cols, so it still works if the board size changes.
bool is_valid_move(std::string move) {
  // Must be exactly 4 characters. Check this first: the checks below read
  // move[0] to move[3], which would be out of bounds on a shorter string.
  if (move.size() != 4) {
    return false;
  }
  // Files (move[0] and move[2]): column must be 0 up to cols - 1.
  if (move[0] - 'a' < 0 || move[0] - 'a' >= cols) {
    return false;
  }
  if (move[2] - 'a' < 0 || move[2] - 'a' >= cols) {
    return false;
  }
  // Ranks (move[1] and move[3]): row must be 0 up to rows - 1.
  if (move[1] - '1' < 0 || move[1] - '1' >= rows) {
    return false;
  }
  if (move[3] - '1' < 0 || move[3] - '1' >= rows) {
    return false;
  }
  return true;
}

// True if the piece is one of white's (uppercase). False for black pieces
// and for an empty square ('.').
bool is_white_piece(char piece) {
  return piece == white_pawn || piece == white_rook || piece == white_bishop ||
         piece == white_knight || piece == white_queen || piece == white_king;
}

// True if the piece is one of black's (lowercase). False for white pieces
// and for an empty square ('.').
bool is_black_piece(char piece) {
  return piece == black_pawn || piece == black_rook || piece == black_bishop ||
         piece == black_knight || piece == black_queen || piece == black_king;
}

// Returns the column (0 = file a ... cols - 1 = last file) of a board index.
// % gives the remainder: how far past the start of its row the square is.
// A clean divide (remainder 0) means the square is on file a, and the
// remainder counts up to cols - 1, then wraps back to 0 on the next row.
// E.g. 12 % 8 = 4, so square 12 is on column 4 (file e).
// Returns a number, not a letter, so it can be used in maths (e.g. edge checks).
int square_to_col(int square) {
  return square % cols;
}

// Returns the row (0 = rank 1 ... rows - 1 = last rank) of a board index.
// Each row is cols squares long in the flat array, so dividing by cols counts
// how many full rows come before the square, which is the row it's on.
// Integer division drops the remainder. E.g. 12 / 8 = 1, so square 12 is on
// row 1 (rank 2).
// Together with square_to_col, this undoes the flattening in parse_square:
// square_to_row(s) * cols + square_to_col(s) == s.
int square_to_row(int square) {
  return square / cols;
}

// Turns a board index into its name, e.g. 12 -> "e2". The reverse of
// parse_square. Uses square_to_row and square_to_col for the numbers, then
// turns them into characters by adding them to 'a' and '1' (parse_square
// subtracts them instead). Adding to '1', not '0', turns row 0 into rank '1'.
// char(...) is needed because char + int gives an int (e.g. 'a' + 4 = 101).
// The string is built with += because file + rank would add the two
// characters as numbers ('e' + '2' = 151) instead of joining them.
std::string square_name(int square) {
  int row = square_to_row(square);
  int col = square_to_col(square);

  char file = char('a' + col);
  char rank = char('1' + row);

  std::string name = "";
  name += file;
  name += rank;

  return name;
}
