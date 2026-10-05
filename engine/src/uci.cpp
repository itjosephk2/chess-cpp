#include "uci.h"

#include <iostream>
#include <sstream>
#include <string>

#include "board.h"

namespace {

// position [startpos | fen <fen>] [moves <m1> <m2> ...]
void handle_position(Board& board, std::istringstream& ss) {
  std::string token, fen;
  ss >> token;

  if (token == "startpos") {
    fen = START_FEN;
    ss >> token;  // consume "moves" if present
  } else if (token == "fen") {
    while (ss >> token && token != "moves") fen += token + ' ';
  } else {
    return;
  }

  board.set_fen(fen);

  // TODO: once move generation exists, find each move in the legal move
  // list (match from/to/promotion) and apply it with make_move().
  while (ss >> token) {
    std::cout << "info string ignoring move " << token << " (make_move not implemented)\n";
  }
}

// go [depth N] [movetime N] [wtime N btime N ...]
void handle_go(Board& /*board*/, std::istringstream& /*ss*/) {
  // TODO: generate legal moves, search, and print the best one.
  std::cout << "bestmove 0000\n";
}

}  // namespace

void uci_loop() {
  Board board;
  std::string line, cmd;

  while (std::getline(std::cin, line)) {
    std::istringstream ss(line);
    cmd.clear();
    ss >> cmd;

    if (cmd == "uci") {
      std::cout << "id name Engine\n"
                << "id author Your Name\n"
                << "uciok\n";
    } else if (cmd == "isready") {
      std::cout << "readyok\n";
    } else if (cmd == "ucinewgame") {
      board.set_fen(START_FEN);
    } else if (cmd == "position") {
      handle_position(board, ss);
    } else if (cmd == "go") {
      handle_go(board, ss);
    } else if (cmd == "d") {
      board.print();  // non-standard debug command, like Stockfish
    } else if (cmd == "quit") {
      break;
    } else if (!cmd.empty()) {
      std::cout << "info string unknown command: " << cmd << '\n';
    }
    std::cout.flush();
  }
}
