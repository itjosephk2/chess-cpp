#pragma once

// The view: shows the board in the terminal. Kept separate from board.h so
// the board code (the model) never prints anything, and can be reused by a
// different view later, like the web UI.
void print_board(char board[]);
void print_letter_rank();
