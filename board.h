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

        // Board constructor and destructor
        board();
        ~board();

        void print_pieces();

        // Enum class definition for pieces (for piece lookup in array)
        enum class piece_type : char {
            WHITE_PAWN = 0,
            WHITE_KNIGHT = 1,
            WHITE_BISHOP = 2,
            WHITE_ROOK = 3,
            WHITE_QUEEN = 4,
            WHITE_KING = 5,
            BLACK_PAWN = 6,
            BLACK_KNIGHT = 7,
            BLACK_BISHOP = 8,
            BLACK_ROOK = 9,
            BLACK_QUEEN = 10,
            BLACK_KING = 11,
            EMPTY = 12
        };

        // Public facing print board method
        void print_bitboard(piece_type piece);

        enum class promotion_type : char {
            NONE = 0,
            QUEEN = 'q',
            ROOK = 'r',
            BISHOP = 'b',
            KNIGHT = 'n'
        };

        // Enum class definition for moves struct
        struct move_struct {
            int from_square;
            int to_square;
            promotion_type promotion;
            bool is_white;
        };

        void print_move(move_struct m);

        // Type definition for a bitboard (64 bits unsigned integer)
        typedef uint64_t BitBoard_t;

        // Processes valid chess moves by updating bitboards
        void make_move(move_struct m);

    private:

        struct castling_rights {
            bool white_kingside : 1;
            bool white_queenside : 1;
            bool black_kingside : 1;
            bool black_queenside : 1;
        };

        const static int NUM_PIECE_TYPES = 12;

        BitBoard_t bitboard_array[NUM_PIECE_TYPES];
        piece_type board_array[64];

        // Defines bitbaord when given valid squares via chess notation
        BitBoard_t define_bitboard(const vector<string>& squares, piece_type piece);

        // Fetches int representation for valid chess notated squares
        int notation_to_square(string square);

        // Fetches string representation for int in range (0-63)
        string square_to_notation(int square);

        // Convert board enum to string name
        string board_to_string(piece_type piece);

        // Convert piece enum to string name
        string piece_to_string(piece_type piece);

        // Convert bitboard to visual string representation
        string interpret_bitboard(BitBoard_t bitboard);

        // Convert move to algebraic notation
        // void print_move(move_struct m);


        void handle_promotion(move_struct m);

        piece_type promotion_to_piece_type(promotion_type promotion_piece, bool is_white);

        // Process move should be just breaking down of the long algebraic. A few key things need to be detected:
        //      1. If a castle has occured
        //      2. If an en passant has occured
        //      3. If a 
};

#endif
