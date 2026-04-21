#include "board.h"
#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

board::board() {
    whitePawns = 0b0000000011111111000000000000000000000000000000000000000000000000;
    boards_hash["whitePawns"] = whitePawns;
}

board::~board() {}

int board::print_piece(string piece) {
    BitBoard_t print_board = get_bitboard(piece);
    cout << print_board << endl;
    return 1;
}

board::BitBoard_t board::get_bitboard(string piece) {
    if (boards_hash.find(piece) != boards_hash.end()) {
        return boards_hash[piece];
    }
    else {
        throw runtime_error("Unknown Piece called for: " + piece);
    }
}

int main() {
    board chess_board = board();
    string piece = "whitePawns";
    chess_board.print_piece(piece);
}