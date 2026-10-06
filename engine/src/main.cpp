#include <iostream>

// Function declarations: tell the compiler these functions exist, so main()
// can call them before their full definitions appear further down the file.
void reset_board(char board[]);
void print_board(char board[]);
void print_letter_rank();


// Board size. constexpr = a constant known at compile time, so it can be used
// as an array size. Global constants are fine: nothing can change them.
constexpr int rows = 8;
constexpr int cols = 8;


// Pieces: uppercase = white, lowercase = black (the same convention FEN uses).
constexpr char white_pawn = 'P';
constexpr char white_rook = 'R';
constexpr char white_knight = 'N';
constexpr char white_bishop = 'B';
constexpr char white_queen = 'Q';
constexpr char white_king = 'K';
// White's back rank from file a to file h.
constexpr char white_pieces_rank[cols] = {white_rook, white_knight, white_bishop, white_queen, white_king, white_bishop, white_knight, white_rook};

constexpr char black_pawn = 'p';
constexpr char black_rook = 'r';
constexpr char black_knight = 'n';
constexpr char black_bishop = 'b';
constexpr char black_queen = 'q';
constexpr char black_king = 'k';
// Black's back rank from file a to file h.
constexpr char black_pieces_rank[cols] = {black_rook, black_knight, black_bishop, black_queen, black_king, black_bishop, black_knight, black_rook};

int main() {
  // The board: one char per square. Square 0 is a1, 1 is b1, ... 7 is h1,
  // 8 is a2, ... 63 is h8. So square = row * cols + col, with row 0 = rank 1.
  // It lives in main (not global) because it changes during the game, and is
  // passed to the functions that need it.
  char board[rows * cols];

  // reset Board
  reset_board(board);

  // Printing Board
  print_board(board);

  // print letter rank
  print_letter_rank();


  std::cout << "\n";

  return 0;
}

// print the ches board
// Arrays are not copied when passed to a function: board here is the same
// array as in main, so changes made through it would affect main's board.
void print_board(char board[]) {
  // Print from the top of the board (rank 8) down to rank 1.
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

// print letters rank
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
  // clearing the board
  for (int i = 0; i < rows * cols; i++) {
    board[i] = '.';
  }

  // Setting up the board
  // white pawns: row 1 (rank 2)
  for (int i = cols; i < cols * 2; i++) {
    board[i] = white_pawn;
  }

  // black pawns: second-to-last row (rank 7)
  for (int i = cols * (rows - 2); i < cols * (rows - 1); i++) {
    board[i] = black_pawn;
  }

  // white pieces: row 0 (rank 1), where board square i matches rank slot i
  for (int i = 0; i < cols; i++) {
    board[i] = white_pieces_rank[i];
  }

  // black pieces: last row (rank 8). Subtract the row's first square to get
  // the slot 0..cols-1 in black_pieces_rank.
  for (int i = (rows - 1) * cols; i < rows * cols; i++) {
    board[i] = black_pieces_rank[i - (cols * (rows - 1))];
  }


}
