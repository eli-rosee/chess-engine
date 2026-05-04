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

        // Enum class definition for pieces (for piece lookup in array)
        enum class piece_type {
            EMPTY = 0,
            WHITE_PAWN, WHITE_KNIGHT, WHITE_BISHOP, WHITE_ROOK, WHITE_QUEEN, WHITE_KING,
            BLACK_PAWN, BLACK_KNIGHT, BLACK_BISHOP, BLACK_ROOK, BLACK_QUEEN, BLACK_KING
        };

        // Enum class definition for logic for retrieving bitboards dynamically
        enum class bitboard_type {
            WHITE_PAWNS, WHITE_KNIGHTS, WHITE_BISHOPS, WHITE_ROOKS, WHITE_QUEENS, WHITE_KING,
            BLACK_PAWNS, BLACK_KNIGHTS, BLACK_BISHOPS, BLACK_ROOKS, BLACK_QUEENS, BLACK_KING,
            WHITE_PIECES, BLACK_PIECES, ALL_PIECES, CASTLING_RIGHTS, EN_PASSANT_RIGHTS
        };

        // Board constructor and destructor
        board();
        ~board();

        // Public facing print board method
        void print_bitboard(bitboard_type board);

        void print_pieces();

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

        // Processes valid chess moves by updating bitboards
        void process_move(string move);

        // Need to know whose turn it is. Need to be able to process when two pieces can go to the same place.
        // Need to know move num?
};

#endif
