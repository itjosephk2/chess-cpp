#include <iostream>
#include "board.h"
#include "display.h"

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
