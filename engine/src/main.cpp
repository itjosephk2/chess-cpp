#include <iostream>
#include <string>

// Function declarations: tell the compiler these functions exist, so main()
// can call them before their full definitions appear further down the file.
void reset_board(char board[]);
void print_board(char board[]);
void print_letter_rank();
void make_move(char board[], int from, int to);
int parse_square(char file, char rank);
void play_move(char board[], std::string move);
bool is_valid_move(std::string move);


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


  std::cout << "\n\n";

  // Game loop: ask for a move, play it, show the board, repeat until "quit".
  // This will later become the engine's UCI loop, which reads commands the
  // same way.
  bool isGame = true;
  while (isGame) {

    std::cout << "Your Move: ";
    std::string move;
    std::cin >> move;  // waits for the user to type a word and press Enter
    // Check for quit first, so "quit" is never treated as a move.
    if (move == "quit") {
      isGame = false;
    }
    else {
      play_move(board, move);
      std::cout << "\n";
      print_board(board);
      std::cout << "\n";
    }
    
  }
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
  int square = 0;

  // square = column + row * cols
  square = ((file - 'a') + (cols * (rank - '1')));
  // Test Code: uncomment to print each part of the calculation
  // std::cout << "file: " << (file - 'a') << "\n";
  // std::cout << "Rank: " << (cols * (rank - '1')) << "\n";
  // std::cout << "number of columns: " << cols << "\n";
  // std::cout << "Rank we are on: " << (rank - '1') << "\n";
  // std::cout << "square: " << file << rank << " = " << square; 
  return square;  
}

// Plays a move given as text, e.g. "e2e4" (from-square then to-square).
// Text moves come from outside the program, so they are checked first;
// invalid text is ignored. make_move does the actual moving.
// A string can be indexed like an array: move[0] is 'e', move[1] is '2', ...
void play_move(char board[], std::string move) {
  if (is_valid_move(move)) {
    int from = parse_square(move[0], move[1]);
    int to = parse_square(move[2], move[3]);
    make_move(board, from, to);
  }
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