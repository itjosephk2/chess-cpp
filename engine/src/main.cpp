#include <iostream>

void reset_board(int rows, int cols, char board[], char white_pieces_rank[], char black_pieces_rank[], char white_pawn, char black_pawn);
void print_board(int rows, int cols, char board[]);
void print_letter_rank(int cols);

int main() {
  // Board
  constexpr int rows = 8;
  constexpr int cols = 8;
  char board[rows * cols];
  for (int i = 0; i < rows * cols; i++) {
    board[i] = '.';
  }

  // pieces
  char white_pawn = 'P';
  char white_rook = 'R';
  char white_knight = 'N';
  char white_bishop = 'B';
  char white_queen = 'Q';
  char white_king = 'K';
  char white_pieces_rank[cols] = {white_rook, white_knight, white_bishop, white_queen, white_king, white_bishop, white_knight, white_rook};

  char black_pawn = 'p';
  char black_rook = 'r';
  char black_knight = 'n';
  char black_bishop = 'b';
  char black_queen = 'q';
  char black_king = 'k';
  char black_pieces_rank[cols] = {black_rook, black_knight, black_bishop, black_queen, black_king, black_bishop, black_knight, black_rook};

  // reset Board
  reset_board(rows, cols, board, white_pieces_rank, black_pieces_rank, white_pawn, black_pawn);

  // Printing Board
  print_board(rows, cols, board);

  // print letter rank
  print_letter_rank(cols);
  

  std::cout << "\n";

  return 0;
}

// print the ches board
void print_board(int rows, int cols, char board[]) {
  for (int i = 0; i < rows; i++) {
    std::cout << rows - i << ' ';
    for (int j = 0; j < cols; j++) {
      std::cout << board[((rows - 1) - i) * cols + j] << ' ';
    }
    std::cout << "\n";
  }
}

// print letters rank
void print_letter_rank(int cols) {
  std::cout << "  ";
  for (int j = 0; j < cols; j++) {
    std::cout << char('a' + j) << ' ';
  }
}

void reset_board(int rows, int cols, char board[], char white_pieces_rank[], char black_pieces_rank[], char white_pawn, char black_pawn) {
  // Setting up the board
  // white pawns
  for (int i = cols; i < cols * 2; i++) {
    board[i] = white_pawn;
  }

  // black pawns
  for (int i = cols * (rows - 2); i < cols * (rows - 1); i++) {
    board[i] = black_pawn;
  }

  // white pieces
  for (int i = 0; i < cols; i++) {
    board[i] = white_pieces_rank[i];
  }

  // black pieces
  for (int i = (rows - 1) * cols; i < rows * cols; i++) {
    board[i] = black_pieces_rank[i - (cols * (rows - 1))];
  }


}