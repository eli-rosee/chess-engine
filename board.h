// board.h by Eli Rose

#ifndef BOARD_H
#define BOARD_H

#include <cstdint>
#include <string>
#include <vector>

using namespace std;

class board
{

    public:

        // Type definition for a bitboard (64 bits unsigned integer)
        typedef uint64_t BitBoard_t;

        enum class promotion_type : char {
            NONE = 0,
            QUEEN = 'q',
            ROOK = 'r',
            BISHOP = 'b',
            KNIGHT = 'n'
        };

        // Enum class definition for pieces (for piece lookup in array)
        enum class piece_type : unsigned char {
            EMPTY = 0,
            WHITE_PAWN = 1, WHITE_KNIGHT = 2, WHITE_BISHOP = 3,
            WHITE_ROOK = 4, WHITE_QUEEN = 5, WHITE_KING = 6,
            BLACK_PAWN = 9, BLACK_KNIGHT = 10, BLACK_BISHOP = 11,
            BLACK_ROOK = 12, BLACK_QUEEN = 13, BLACK_KING = 14
        };

        // Enum class definition for logic for retrieving bitboards dynamically
        enum class special_bitboard_type {
            WHITE_PIECES, BLACK_PIECES, ALL_PIECES, CASTLING_RIGHTS, EN_PASSANT_RIGHTS
        };

        // Enum class definition for moves struct
        struct move_struct {
            int from_square;
            int to_square;
            promotion_type promotion;
        };

        // Board constructor and destructor
        board();
        ~board();

        // Public facing print board method
        void print_bitboard(bitboard_type board);

        void print_pieces();

        void print_move(move_struct m);

    private:

        // White bitboards
        BitBoard_t white_pawns;
        BitBoard_t white_knights;
        BitBoard_t white_bishops;
        BitBoard_t white_rooks;
        BitBoard_t white_queens;
        BitBoard_t white_king;

        // Black bitboards
        BitBoard_t black_pawns;
        BitBoard_t black_knights;
        BitBoard_t black_bishops;
        BitBoard_t black_rooks;
        BitBoard_t black_queens;
        BitBoard_t black_king;

        // Conglomerate bitboards
        BitBoard_t white_pieces;
        BitBoard_t black_pieces;
        BitBoard_t all_pieces;

        // Special case chess logic bitboards
        BitBoard_t castling_rights;
        BitBoard_t en_passant_rights;

        // Defines the board array which stores piece types at each square
        piece_type board_array[64];

        // Defines bitbaord when given valid squares via chess notation
        BitBoard_t define_bitboard(const vector<string>& squares, piece_type piece);

        // Fetches int representation for valid chess notated squares
        int notation_to_square(string square);

        // Fetches string representation for int in range (0-63)
        string square_to_notation(int square);

        // Convert board enum to string name
        string board_to_string(bitboard_type board);

        // Convert piece enum to string name
        string piece_to_string(piece_type piece);

        // Convert board enum to bitboard value
        BitBoard_t get_bitboard(bitboard_type board);

        // Gets piece at specified square
        piece_type get_piece(int square);

        // Convert bitboard to visual string representation
        string interpret_bitboard(BitBoard_t bitboard);

        // Convert move to algebraic notation
        // void print_move(move_struct m);

        // Processes valid chess moves by updating bitboards
        void make_move(move_struct m);

        // Process move should be just breaking down of the long algebraic. A few key things need to be detected:
        //      1. If a castle has occured
        //      2. If an en passant has occured
        //      3. If a 
};

#endif
