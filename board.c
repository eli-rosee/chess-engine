#include "board.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <chrono>

using namespace std;

board::board() {

    whitePawns = 0x000FFFFFFFFFFFFFF;
    whiteKnights = 0x0FFFFFFFFFFFFFFFF;
    whiteBishops = 0x0FFFFFFFFFFFFFFFF;
    whiteRooks = 0x0FFFFFFFFFFFFFFFF;
    whiteQueens = 0x0FFFFFFFFFFFFFFFF;
    whiteKing = 0x0FFFFFFFFFFFFFFFF;

    blackPawns = 0x0FFFFFFFFFFFFFFFF;
    blackKnights = 0x0FFFFFFFFFFFFFFFF;
    blackBishops = 0x0FFFFFFFFFFFFFFFF;
    blackRooks = 0x0FFFFFFFFFFFFFFFF;
    blackQueens = 0x0FFFFFFFFFFFFFFFF;
    blackKing = 0x0FFFFFFFFFFFFFFFF;

    fullBoard = 0x0FFFFFFFFFFFFFFFF;
    whitePieces = 0x0FFFFFFFFFFFFFFFF;
    blackPieces = 0x0FFFFFFFFFFFFFFFF;

    castlingRights = 0x0FFFFFFFFFFFFFFFF;
    enPassantRights = 0x0FFFFFFFFFFFFFFFF;
    
    boards_hash["whitePawns"] = whitePawns;
    boards_hash["whiteKnights"] = whiteKnights;
    boards_hash["whiteBishops"] = whiteBishops;
    boards_hash["whiteRooks"] = whiteRooks;
    boards_hash["whiteQueens"] = whiteQueens;
    boards_hash["whiteKing"] = whiteKing;

    boards_hash["blackPawns"] = whitePawns;
    boards_hash["blackKnights"] = whiteKnights;
    boards_hash["blackBishops"] = whiteBishops;
    boards_hash["blackRooks"] = whiteRooks;
    boards_hash["blackQueens"] = whiteQueens;
    boards_hash["blackKing"] = whiteKing;

    boards_hash["fullBoard"] = fullBoard;
    boards_hash["whitePieces"] = fullBoard;
    boards_hash["blackPieces"] = fullBoard;

    boards_hash["castlingRights"] = fullBoard;
    boards_hash["enPassantRights"] = fullBoard;

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
        edge += 1;
        int bit = bitboard % 2;
        bitboard >>= 1;

        if (bit == 1) { 
            string_board = " 1" + string_board;
        }
        else {
            string_board = " 0" + string_board;
        }

        if (edge == 8) {
            string_board = '\n' + string_board;
            edge = 0;
        }
    }

    return string_board;
}

int main() {
    auto start = chrono::high_resolution_clock::now();

    ["whitePawns", "whiteKnights", "whiteBishops", "whiteRooks", "whiteQueens", "whiteKing"]

    "blackPawns"
    ["blackKnights"]
    ["blackBishops"]
    ["blackRooks"] = whiteRooks;
    ["blackQueens"] = whiteQueens;
    ["blackKing"] = whiteKing;

    ["fullBoard"] = fullBoard;
    ["whitePieces"] = fullBoard;
    ["blackPieces"] = fullBoard;

    ["castlingRights"] = fullBoard;
    ["enPassantRights"] = fullBoard;

    board chess_board = board();
    string piece = "whitePawns";
    chess_board.print_piece(piece);

    auto end = chrono::high_resolution_clock::now();
    auto total_time = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << total_time.count() << "ms" << endl;
}