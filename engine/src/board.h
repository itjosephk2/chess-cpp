#pragma once
#include <string>

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

// Function declarations: 
void reset_board(char board[]);
bool play_move(char board[], std::string move, bool white_to_move);
void make_move(char board[], int from, int to);
int parse_square(char file, char rank);
bool is_valid_move(std::string move);
bool is_white_piece(char piece);
bool is_black_piece(char piece);
int square_to_col(int square);
int square_to_row(int square);
std::string square_name(int square);
