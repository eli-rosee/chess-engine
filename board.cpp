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
    bitboard_array[static_cast<int>(piece_type::WHITE_PAWN)] = define_bitboard({"a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2"}, piece_type::WHITE_PAWN);
    bitboard_array[static_cast<int>(piece_type::WHITE_KNIGHT)] = define_bitboard({"b1", "g1"}, piece_type::WHITE_KNIGHT);
    bitboard_array[static_cast<int>(piece_type::WHITE_BISHOP)] = define_bitboard({"c1", "f1"}, piece_type::WHITE_BISHOP);
    bitboard_array[static_cast<int>(piece_type::WHITE_ROOK)] = define_bitboard({"a1", "h1"}, piece_type::WHITE_ROOK);
    bitboard_array[static_cast<int>(piece_type::WHITE_QUEEN)] = define_bitboard({"d1"}, piece_type::WHITE_QUEEN);
    bitboard_array[static_cast<int>(piece_type::WHITE_KING)] = define_bitboard({"e1"}, piece_type::WHITE_KING);

    // Define all black bitboards
    bitboard_array[static_cast<int>(piece_type::BLACK_PAWN)] = define_bitboard({"a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7"}, piece_type::BLACK_PAWN);
    bitboard_array[static_cast<int>(piece_type::BLACK_KNIGHT)] = define_bitboard({"b8", "g8"}, piece_type::BLACK_KNIGHT);
    bitboard_array[static_cast<int>(piece_type::BLACK_BISHOP)] = define_bitboard({"c8", "f8"}, piece_type::BLACK_BISHOP);
    bitboard_array[static_cast<int>(piece_type::BLACK_ROOK)] = define_bitboard({"a8", "h8"}, piece_type::BLACK_ROOK);
    bitboard_array[static_cast<int>(piece_type::BLACK_QUEEN)] = define_bitboard({"d8"}, piece_type::BLACK_QUEEN);
    bitboard_array[static_cast<int>(piece_type::BLACK_KING)] = define_bitboard({"e8"}, piece_type::BLACK_KING);
}

// Board Destructor
board::~board() {}

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
        throw runtime_error("Square has incorrect notation: (notation_to_square)");
    }

    // Converts char to correct int for calculations
    int file_ascii = static_cast<int>(file) - 97;
    int rank_num = rank - '1';

    // Calculates the square number (0 - 63)
    return(rank_num * 8 + file_ascii);
}

string board::square_to_notation(int square) {

    // Checks if the chars represent correct chess notation
    if (square < 0 || square > 63) {
        throw runtime_error("Square is out of range (0-63) (square_to_notation)");
    }

    int ascii_num = 65 + (square % 8);
    int rank_num = square / 8 + 1;

    // Converts char to correct int for calculations
    char file = tolower(static_cast<char>(ascii_num));

    return (file + to_string(rank_num));

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
void board::print_bitboard(piece_type piece) {

    // Retrieves the name, bitboard, and string representation of the specified board enum
    string board_name = piece_to_string(piece);
    BitBoard_t print_board = bitboard_array[static_cast<int>(piece)];
    string string_board = interpret_bitboard(print_board);

    // Prints out the board name and string representation
    cout << board_name << endl << string_board;
}

// Prints the piece representation board
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
string board::interpret_bitboard(BitBoard_t bitboard) {
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

void board::print_move(move_struct m) {
    int first_square = m.from_square;
    int second_square = m.to_square;
    string promotion_str = "";
    if (m.promotion != promotion_type::NONE) {
        promotion_str = static_cast<char>(m.promotion);
    }

    string first_notation = square_to_notation(first_square);
    string second_notation = square_to_notation(second_square);
    cout << first_notation << second_notation << promotion_str << endl;
}

void board::make_move(move_struct m) {
    int first_square = m.from_square;
    int second_square = m.to_square;

    piece_type piece_to_move = board_array[first_square];
    bitboard_array[static_cast<int>(piece_to_move)] &= ~(1ULL << first_square);

    if(m.promotion != promotion_type::NONE) {
        bitboard_array[static_cast<int>(piece_to_move)] |= 1ULL << second_square;
    }
    else {
        handle_promotion(m);
    }
}

void board::handle_promotion(move_struct m) {
    int promotion_square = m.to_square;

    piece_type promotion_piece = promotion_to_piece_type(m.promotion, m.is_white);

    bitboard_array[static_cast<int>(promotion_piece)] |= 1ULL << promotion_square;
}

board::piece_type board::promotion_to_piece_type(promotion_type promotion_piece, bool is_white) {
    switch(promotion_piece) {
        case promotion_type::QUEEN:
            return is_white ? piece_type::WHITE_QUEEN : piece_type::BLACK_QUEEN;
        case promotion_type::ROOK:
            return is_white ? piece_type::WHITE_ROOK : piece_type::BLACK_ROOK;
        case promotion_type::BISHOP:
            return is_white ? piece_type::WHITE_BISHOP : piece_type::BLACK_BISHOP;
        case promotion_type::KNIGHT:
            return is_white ? piece_type::WHITE_KNIGHT : piece_type::BLACK_KNIGHT;
    }
    throw runtime_error("Logic error. None piece type somehow recieved in (promotion_to_piece_type)");
}

// Defines a board, loops through all enums, and prints their string representations
int main() {
    
    vector<board::move_struct> realistic_game = {
        {12, 28, board::promotion_type::NONE, true},
        {52, 36, board::promotion_type::NONE, false},
        {1, 18, board::promotion_type::NONE, true},
        {62, 45, board::promotion_type::NONE, false},
        {28, 36, board::promotion_type::NONE, true},
        {36, 28, board::promotion_type::NONE, false},
        {18, 36, board::promotion_type::NONE, true},
        {45, 36, board::promotion_type::NONE, false},
        {3, 27, board::promotion_type::NONE, true},
        {60, 61, board::promotion_type::NONE, false},
        {27, 36, board::promotion_type::NONE, true},
        {61, 52, board::promotion_type::NONE, false},
        {4, 5, board::promotion_type::NONE, true},
        {52, 44, board::promotion_type::NONE, false},
        {5, 4, board::promotion_type::NONE, true},
        {44, 36, board::promotion_type::NONE, false},
        {2, 20, board::promotion_type::NONE, true},
        {36, 28, board::promotion_type::NONE, false},
        {20, 28, board::promotion_type::NONE, true},
        {28, 20, board::promotion_type::NONE, false},
        {6, 21, board::promotion_type::NONE, true},
        {20, 12, board::promotion_type::NONE, false},
        {0, 8, board::promotion_type::NONE, true},
        {12, 20, board::promotion_type::NONE, false},
        {21, 20, board::promotion_type::NONE, true},
        {56, 48, board::promotion_type::NONE, false},
        {8, 16, board::promotion_type::NONE, true},
        {48, 40, board::promotion_type::NONE, false},
        {16, 24, board::promotion_type::NONE, true},
        {40, 32, board::promotion_type::NONE, false},
        {24, 32, board::promotion_type::NONE, true},
        {59, 51, board::promotion_type::NONE, false},
        {20, 28, board::promotion_type::NONE, true},
        {51, 43, board::promotion_type::NONE, false},
        {28, 36, board::promotion_type::NONE, true},
        {43, 35, board::promotion_type::NONE, false},
        {36, 44, board::promotion_type::NONE, true},
        {35, 27, board::promotion_type::NONE, false},
        {44, 52, board::promotion_type::NONE, true},
        {27, 19, board::promotion_type::NONE, false},
        {9, 17, board::promotion_type::NONE, true},
        {19, 11, board::promotion_type::NONE, false},
        {17, 25, board::promotion_type::NONE, true},
        {11, 3, board::promotion_type::NONE, false},
        {52, 60, board::promotion_type::QUEEN, true},
    };

    // Stores all bitboard enums
    vector<board::piece_type> all_pieces = {
        board::piece_type::WHITE_PAWN, board::piece_type::WHITE_KNIGHT, 
        board::piece_type::WHITE_BISHOP, board::piece_type::WHITE_ROOK, 
        board::piece_type::WHITE_QUEEN, board::piece_type::WHITE_KING, 
        board::piece_type::BLACK_PAWN, board::piece_type::BLACK_KNIGHT, 
        board::piece_type::BLACK_BISHOP, board::piece_type::BLACK_ROOK, 
        board::piece_type::BLACK_QUEEN, board::piece_type::BLACK_KING, 
    };

    // Defines a new board
    board chess_board = board();

    // Prints the piece representation board
    chess_board.print_pieces();

    cout << endl;

    // Loops through all bitboard enums and prints them
    for (auto curr_piece : all_pieces) {
        chess_board.print_bitboard(curr_piece);
        cout << endl;
    }

    for (auto move : realistic_game) {
        chess_board.make_move(move);
        chess_board.print_move(move);
        for (auto curr_piece : all_pieces) {
            chess_board.print_bitboard(curr_piece);
            cout << endl;
        }
    }

    return 0;
}
