#include "board.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <chrono>

using namespace std;

board::board() {

    white_pawns = define_bitboard(vector<string> {"a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2"});
    white_knights = define_bitboard(vector<string> {"b1", "g1"});
    white_bishops = define_bitboard(vector<string> {"c1", "f1"});
    white_rooks = define_bitboard(vector<string> {"a1", "h1"});
    white_queens = define_bitboard(vector<string> {"d1"});
    white_king = define_bitboard(vector<string> {"e1"});

    black_pawns = define_bitboard(vector<string> {"a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7"});
    black_knights = define_bitboard(vector<string> {"b8", "g8"});
    black_bishops = define_bitboard(vector<string> {"c8", "f8"});
    black_rooks = define_bitboard(vector<string> {"a8", "h8"});
    black_queens = define_bitboard(vector<string> {"d8"});
    black_king = define_bitboard(vector<string> {"e8"});

    white_pieces = white_pawns & white_knights & white_bishops & white_rooks & white_queens & white_king;
    blackPieces = black_pawns & black_knights & black_bishops & black_rooks & black_queens & black_king;

    all_pieces = white_pieces & blackPieces;

    castlingRights = white_king & white_rooks & black_king & black_rooks;
    enPassantRights = 0;
}

board::~board() {}

string board::board_to_string(bitboard_type board) {
    switch(board) {
        case bitboard_type::WHITE_PAWNS: return "white_pawns";
        case bitboard_type::WHITE_KNIGHTS: return "white_knights";
        case bitboard_type::WHITE_BISHOPS: return "white_bishops";
        case bitboard_type::WHITE_ROOKS: return "white_rooks";
        case bitboard_type::WHITE_QUEENS: return "white_queens";
        case bitboard_type::WHITE_KING: return "white_king";
        case bitboard_type::BLACK_PAWNS: return "black_pawns";
        case bitboard_type::BLACK_KNIGHTS: return "black_knights";
        case bitboard_type::BLACK_BISHOPS: return "black_bishops";
        case bitboard_type::BLACK_ROOKS: return "black_rooks";
        case bitboard_type::BLACK_QUEENS: return "black_queens";
        case bitboard_type::BLACK_KING: return "black_king";
        case bitboard_type::WHITE_PIECES: return "white_pieces";
        case bitboard_type::BLACK_PIECES: return "black_pieces";
        case bitboard_type::ALL_PIECES: return "all_pieces";
        case bitboard_type::CASTLING_RIGHTS: return "castling_rights";
        case bitboard_type::ENPASSANT_RIGHTS: return "enpassant_rights";
        default:
            throw runtime_error("Unknown Piece Type");
    }
}

int board::print_board(board::bitboard_type board) {
    BitBoard_t print_board = get_bitboard(board);
    string string_board = interpret_bitboard(print_board);
    cout << string_board << endl << endl;
    return 1;
}

board::BitBoard_t board::get_bitboard(board::bitboard_type board) {
    switch(board) {
        case bitboard_type::WHITE_PAWNS: return white_pawns;
        case bitboard_type::WHITE_KNIGHTS: return white_knights;
        case bitboard_type::WHITE_BISHOPS: return white_bishops;
        case bitboard_type::WHITE_ROOKS: return white_rooks;
        case bitboard_type::WHITE_QUEENS: return white_queens;
        case bitboard_type::WHITE_KING: return white_king;
        case bitboard_type::BLACK_PAWNS: return black_pawns;
        case bitboard_type::BLACK_KNIGHTS: return black_knights;
        case bitboard_type::BLACK_BISHOPS: return black_bishops;
        case bitboard_type::BLACK_ROOKS: return black_rooks;
        case bitboard_type::BLACK_QUEENS: return black_queens;
        case bitboard_type::BLACK_KING: return black_king;
        case bitboard_type::WHITE_PIECES: return white_pieces;
        case bitboard_type::BLACK_PIECES: return black_pieces;
        case bitboard_type::ALL_PIECES: return all_pieces;
        case bitboard_type::CASTLING_RIGHTS: return castling_rights;
        case bitboard_type::ENPASSANT_RIGHTS: return enpassant_rights;
        default:
            throw runtime_error("Unknown board type");
    }
}

board::BitBoard_t board::define_bitboard(const vector<string>& squares) {
    BitBoard_t board = 0;
    
    for(int i = 0; i < squares.size(); i++) {
        int file_ascii = 0;
        int rank_num = 0;

        string square = squares[i];
        
        if(square.length() != 2) {
            throw runtime_error("Square has incorrect size: " + square);
        }

        char file = square[0];
        char rank = square[1];

        if (!((file >= 'a' && file <= 'h') && (rank >= '1' && rank <= '8'))) {
            throw runtime_error("Square has incorrect notation: " + square);
        }
        else {
            file_ascii = static_cast<int>(file) - 97;
            rank_num = rank - '1';
        }

        int square_index = rank_num * 8 + file_ascii;

        // Set the bit at this position
        board |= (1ULL << square_index);
    }

    return board;
}

string board::interpret_bitboard(board::BitBoard_t bitboard) {
    string string_board = "";
    int edge = 0;

    for (int i = 0; i < 64; i++) {
        int bit = bitboard % 2;
        bitboard >>= 1;
        
        if (bit == 1) { 
            string_board = " 1" + string_board;
        }
        else {
            string_board = " 0" + string_board;
        }
        
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

    vector<board::bitboard_type> allBoards = {board::bitboard_type::WHITE_PAWNS};
    board chess_board = board();

    for (int i = 0; i < allBoards.size(); i++) {
        board::bitboard_type piece = allBoards[i];
        chess_board.print_piece(piece);
    }

    auto end = chrono::high_resolution_clock::now();
    auto total_time = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << total_time.count() << "ms" << endl;
}
