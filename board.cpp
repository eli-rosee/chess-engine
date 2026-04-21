#include "board.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <chrono>

using namespace std;

board::board() {
    whitePawns = 0b0000000000000000000000000000000000000000000000001111111100000000;
    
    boards_hash["whitePawns"] = whitePawns;
}

board::~board() {}

int board::print_piece(string piece) {
    BitBoard_t print_board = get_bitboard(piece);
    string string_board = interpret_bitboard(print_board);
    cout << string_board << endl << endl;
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

string board::interpret_bitboard(board::BitBoard_t bitboard) {
    string string_board = "";
    int edge = 0;

    while (bitboard > 0) {
        int bit = bitboard % 2;
        bitboard >>= 1;
        edge += 1;

        if (bit == 1) { 
            string_board = "1" + string_board;
        }
        else {
            string_board = "0" + string_board;
        }

        if (edge == 8) {
            string_board = '\n' + string_board;
            edge = 0;
        }
    }

    while (string_board.length() < 63) {
        string_board = "0" + string_board;
        edge += 1;

        if (edge == 8) {
            string_board = '\n' + string_board;
            edge = 0;
        }
    }

    return string_board;
}

int main() {
    auto start = chrono::high_resolution_clock::now();

    board chess_board = board();
    string piece = "whitePawns";
    chess_board.print_piece(piece);

    auto end = chrono::high_resolution_clock::now();
    auto total_time = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << total_time.count() << "ms" << endl;
}