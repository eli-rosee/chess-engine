// board.cpp by Eli Rose

#include "board.h"
#include <iostream>
#include <stdexcept>

using namespace std;

// Board Constructor
board::board() {

    // Populate the piece type array with empty values
    for (int i = 0; i < 64; i++) {
        board_array[i] = piece_type::EMPTY;
    }

    // Define all white bitboards
    white_pawns = define_bitboard({"a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2"}, piece_type::WHITE_PAWN);
    white_knights = define_bitboard({"b1", "g1"}, piece_type::WHITE_KNIGHT);
    white_bishops = define_bitboard({"c1", "f1"}, piece_type::WHITE_BISHOP);
    white_rooks = define_bitboard({"a1", "h1"}, piece_type::WHITE_ROOK);
    white_queens = define_bitboard({"d1"}, piece_type::WHITE_QUEEN);
    white_king = define_bitboard({"e1"}, piece_type::WHITE_KING);

    // Define all black bitboards
    black_pawns = define_bitboard({"a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7"}, piece_type::BLACK_PAWN);
    black_knights = define_bitboard({"b8", "g8"}, piece_type::BLACK_KNIGHT);
    black_bishops = define_bitboard({"c8", "f8"}, piece_type::BLACK_BISHOP);
    black_rooks = define_bitboard({"a8", "h8"}, piece_type::BLACK_ROOK);
    black_queens = define_bitboard({"d8"}, piece_type::BLACK_QUEEN);
    black_king = define_bitboard({"e8"}, piece_type::BLACK_KING);

    // Define all conglomerate bitboards
    white_pieces = white_pawns | white_knights | white_bishops | white_rooks | white_queens | white_king;
    black_pieces = black_pawns | black_knights | black_bishops | black_rooks | black_queens | black_king;
    all_pieces = white_pieces | black_pieces;

    // Define special logic case bitboards
    castling_rights = white_king | white_rooks | black_king | black_rooks;
    en_passant_rights = 0;
}

// Board Destructor
board::~board() {}

// Returns string associated with each enum bitboard
string board::board_to_string(bitboard_type board_type) {
    switch(board_type) {
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
        case bitboard_type::EN_PASSANT_RIGHTS: return "en_passant_rights";
        default:
            throw runtime_error("Unknown Board Type (board_to_string)");
    }
}

// Returns bitboard associated with each enum bitboard
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
        case bitboard_type::EN_PASSANT_RIGHTS: return en_passant_rights;
        default:
            throw runtime_error("Unknown Board Type (get_bitboard)");
    }
}

// Returns string associated with each enum bitboard
string board::piece_to_string(piece_type piece) {
    switch(piece) {
        case piece_type::EMPTY: return "  ";
        case piece_type::WHITE_PAWN: return "WP";
        case piece_type::WHITE_KNIGHT: return "WN";
        case piece_type::WHITE_BISHOP: return "WB";
        case piece_type::WHITE_ROOK: return "WR";
        case piece_type::WHITE_QUEEN: return "WQ";
        case piece_type::WHITE_KING: return "WK";
        case piece_type::BLACK_PAWN: return "BP";
        case piece_type::BLACK_KNIGHT: return "BN";
        case piece_type::BLACK_BISHOP: return "BB";
        case piece_type::BLACK_ROOK: return "BR";
        case piece_type::BLACK_QUEEN: return "BQ";
        case piece_type::BLACK_KING: return "BK";
        default:
            throw runtime_error("Unknown Piece Type (piece_to_string)");
    }
}

// Given a valid 2 char chess notation, converts it to int (0 - 63)
int board::notation_to_square(string square) {
    // Checks if the square is the correct length
    if(square.length() != 2) {
        throw runtime_error("Square has incorrect size: " + square);
    }

    // Separates file and rank into char vars
    char file = square[0];
    char rank = square[1];

    // Checks if the chars represent correct chess notation
    if (!((file >= 'a' && file <= 'h') && (rank >= '1' && rank <= '8'))) {
        throw runtime_error("Square has incorrect notation: " + square);
    }

    // Converts char to correct int for calculations
    int file_ascii = static_cast<int>(file) - 97;
    int rank_num = rank - '1';

    // Calculates the square number (0 - 63)
    return(rank_num * 8 + file_ascii);
}

// Defines bitbaord when given valid squares via chess notation
board::BitBoard_t board::define_bitboard(const vector<string>& squares, piece_type piece) {
    BitBoard_t board = 0;
    
    // Loops through all squares in the vector squares
    for(int i = 0; i < squares.size(); i++) {
        string square = squares[i];
        
        // Fetches the int square representation from the square string
        int square_index = notation_to_square(square);

        // Sets the array index equal to the piece type there
        board_array[square_index] = piece;

        // Set the bit at the specific square index to 1
        board |= (1ULL << square_index);
    }

    return board;
}

// Calls various private functions to print the correct representation of the stored chess board
void board::print_bitboard(board::bitboard_type board) {

    // Retrieves the name, bitboard, and string representation of the specified board enum
    string board_name = board_to_string(board);
    BitBoard_t print_board = get_bitboard(board);
    string string_board = interpret_bitboard(print_board);

    // Prints out the board name and string representation
    cout << board_name << endl << string_board;
}

void board::print_pieces() {
    for (int i = 0; i < 64; i++) {
        if (i % 8 == 0) {
            cout << endl;
        }

        piece_type piece = board_array[i];
        string square_piece = piece_to_string(piece);
        cout << square_piece << " ";
    }
    cout << endl;
}

// Converts the bitboard stored integer into a string representation
string board::interpret_bitboard(board::BitBoard_t bitboard) {
    string string_board = "";
    int edge = 0;

    // Convert bitboard to binary string representation
    for (int i = 0; i < 64; i++) {

        int bit = bitboard % 2;
        bitboard >>= 1;
        
        if (bit == 1) { 
            string_board += " 1";
        }
        else {
            string_board += " 0";
        }
        
        // Add newline every 8 bits (end of rank)
        edge += 1;
        if (edge == 8) {
            string_board += '\n';
            edge = 0;
        }
    }

    return string_board;
}

// Defines a board, loops through all enums, and prints their string representations
int main() {

    // Stores all bitboard enums
    vector<board::bitboard_type> allBoards = {
        board::bitboard_type::WHITE_PAWNS, board::bitboard_type::WHITE_KNIGHTS, 
        board::bitboard_type::WHITE_BISHOPS, board::bitboard_type::WHITE_ROOKS, 
        board::bitboard_type::WHITE_QUEENS, board::bitboard_type::WHITE_KING, 
        board::bitboard_type::BLACK_PAWNS, board::bitboard_type::BLACK_KNIGHTS, 
        board::bitboard_type::BLACK_BISHOPS, board::bitboard_type::BLACK_ROOKS, 
        board::bitboard_type::BLACK_QUEENS, board::bitboard_type::BLACK_KING, 
        board::bitboard_type::WHITE_PIECES, board::bitboard_type::BLACK_PIECES, 
        board::bitboard_type::ALL_PIECES, board::bitboard_type::CASTLING_RIGHTS, 
        board::bitboard_type::EN_PASSANT_RIGHTS
    };

    // Defines a new board
    board chess_board = board();

    // Prints the piece representation board
    chess_board.print_pieces();
    cout << endl;

    // Loops through all bitboard enums and prints them
    for (auto curr_board : allBoards) {
        chess_board.print_bitboard(curr_board);
        cout << endl;
    }

    return 0;
}
