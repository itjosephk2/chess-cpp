#include <iostream>
#include "board.h"

int main() {
  // The board: one char per square. Square 0 is a1, 1 is b1, ... 7 is h1,
  // 8 is a2, ... 63 is h8. So square = row * cols + col, with row 0 = rank 1.
  // It lives in main (not global) because it changes during the game, and is
  // passed to the functions that need it.
  char board[rows * cols];

  reset_board(board);
  print_board(board);
  print_letter_rank();
  std::cout << "\n\n";

  // Game loop: ask for a move, play it, show the board, repeat until "quit".
  // This will later become the engine's UCI loop, which reads commands the
  // same way.
  bool is_game = true;
  bool white_to_move = true;  // white moves first
  while (is_game) {
    // Show whose turn it is, then ask for their move.
    if (white_to_move) {
      std::cout << "White to move\n";
    }
    else {
      std::cout << "Black to move\n";
    }
    std::cout << "Your Move: ";
    std::string move;
    std::cin >> move;  // waits for the user to type a word and press Enter

    // Check for quit first, so "quit" is never treated as a move.
    if (move == "quit") {
      is_game = false;
    }
    else {
      // play_move returns true only if the move was actually played.
      bool move_played = play_move(board, move, white_to_move);

      if (move_played) {
        std::cout << "\n";
        print_board(board);
        print_letter_rank();
        std::cout << "\n\n";

        // Next player's turn. ! flips true to false and false to true.
        // Only done after a played move, so a refused move keeps the same
        // player's turn.
        white_to_move = !white_to_move;
      }
      else {
        // Bad text, an empty square, the other player's piece, or moving
        // onto your own piece.
        std::cout << "Invalid move\n\n";
      }
    }
  }
  return 0;
}
