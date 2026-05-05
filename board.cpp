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
board::BitBoard_t board::get_bitboard(bitboard_type board) {
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
void board::print_bitboard(bitboard_type board) {

    // Retrieves the name, bitboard, and string representation of the specified board enum
    string board_name = board_to_string(board);
    BitBoard_t print_board = get_bitboard(board);
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
    
}

// Defines a board, loops through all enums, and prints their string representations
int main() {
    
    vector<board::move_struct> test_moves = {
    // ===== OPENING MOVES =====
    // White e2-e4 (pawn push 2 squares)
    {12, 28, board::promotion_type::NONE},
    
    // Black e7-e5 (pawn push 2 squares)
    {52, 36, board::promotion_type::NONE},
    
    // White knight b1-c3
    {1, 18, board::promotion_type::NONE},
    
    // Black knight g8-f6
    {62, 45, board::promotion_type::NONE},
    
    // ===== CAPTURES =====
    // White pawn e4 captures black pawn on d5 (if it exists)
    {28, 35, board::promotion_type::NONE},
    
    // White knight captures pawn
    {18, 36, board::promotion_type::NONE},
    
    // ===== CASTLING =====
    // White kingside castling (e1-g1)
    {4, 6, board::promotion_type::NONE},
    
    // White queenside castling (e1-c1)
    {4, 2, board::promotion_type::NONE},
    
    // Black kingside castling (e8-g8)
    {60, 62, board::promotion_type::NONE},
    
    // Black queenside castling (e8-c8)
    {60, 58, board::promotion_type::NONE},
    
    // ===== PAWN PROMOTIONS =====
    // White pawn on e7 promotes to queen (e7-e8=Q)
    {52, 60, board::promotion_type::QUEEN},
    
    // White pawn on a7 promotes to rook (a7-a8=R)
    {48, 56, board::promotion_type::ROOK},
    
    // White pawn on h7 promotes to knight (h7-h8=N)
    {55, 63, board::promotion_type::KNIGHT},
    
    // White pawn on c7 promotes to bishop (c7-c8=B)
    {50, 58, board::promotion_type::BISHOP},
    
    // Black pawn on e2 promotes to queen (e2-e1=Q)
    {12, 4, board::promotion_type::QUEEN},
    
    // Black pawn on a2 promotes to rook (a2-a1=R)
    {8, 0, board::promotion_type::ROOK},
    
    // ===== PIECE MOVES =====
    // White rook a1 to a4
    {0, 24, board::promotion_type::NONE},
    
    // White bishop c1 to e3
    {2, 20, board::promotion_type::NONE},
    
    // White queen d1 to d4
    {3, 27, board::promotion_type::NONE},
    
    // White king e1 to d2
    {4, 11, board::promotion_type::NONE},
    
    // Black rook a8 to a5
    {56, 37, board::promotion_type::NONE},
    
    // Black bishop c8 to f5
    {58, 37, board::promotion_type::NONE},
    
    // ===== PAWN MOVES =====
    // White pawn a2 advance (a2-a3)
    {8, 16, board::promotion_type::NONE},
    
    // White pawn a2 push 2 squares (a2-a4)
    {8, 24, board::promotion_type::NONE},
    
    // Black pawn h7 advance (h7-h6)
    {55, 47, board::promotion_type::NONE},
    
    // Black pawn h7 push 2 squares (h7-h5)
    {55, 39, board::promotion_type::NONE},
    
    // ===== KNIGHT MOVES =====
    // Knight from b1 to d2
    {1, 11, board::promotion_type::NONE},
    
    // Knight from g1 to f3
    {6, 21, board::promotion_type::NONE},
    
    // ===== EDGE CASES FOR TESTING =====
    // Pawn on rank 7 (white) - one square forward
    {48, 56, board::promotion_type::NONE},
    
    // Pawn on rank 2 (black) - one square forward
    {9, 1, board::promotion_type::NONE},

    };

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

    for (auto move : test_moves) {
        chess_board.print_move(move);
    }

    return 0;
}
