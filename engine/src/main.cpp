#include <iostream>

int main() {
  // Board
  int rows = 8;
  int cols = 8;
  char board[64];
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

  char black_pawn = 'p';
  char black_rook = 'r';
  char black_knight = 'n';
  char black_bishop = 'b';
  char black_queen = 'q';
  char black_king = 'k';

  // Setting up the board
  // white pawns
  for (int i = 8; i < 16; i++) {
    board[i] = white_pawn;
  }

  // black pawns
  for (int i = 48; i < 56; i++) {
    board[i] = black_pawn;
  }

  // Printing Board
  for (int i = 0; i < rows; i++) {
    std::cout << 8 - i << ' ';
    for(int j = 0; j < cols; j++) {  
      std::cout << board[(7 - i) * 8 + j] << ' '; 
    }
    std::cout << "\n";
  }
  std::cout << "  a b c d e f g h\n";

  return 0;
}
