// board.h

#ifndef BOARD_H
#define BOARD_H

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class board
{

    public:

        enum class bitboard_type {
            WHITE_PAWNS, WHITE_KNIGHTS, WHITE_BISHOPS, WHITE_ROOKS, WHITE_QUEENS, WHITE_KING,
            BLACK_PAWNS, BLACK_KNIGHTS, BLACK_BISHOPS, BLACK_ROOKS, BLACK_QUEENS, BLACK_KING,
            WHITE_PIECES, BLACK_PIECES, ALL_PIECES, CASTLING_RIGHTS, ENPASSANT_RIGHTS
        };

        board();
        ~board();

        int print_piece(bitboard_type board);

        typedef uint64_t BitBoard_t;

    private:
        BitBoard_t white_pawns;
        BitBoard_t white_knights;
        BitBoard_t white_bishops;
        BitBoard_t white_rooks;
        BitBoard_t white_queens;
        BitBoard_t white_king;

        BitBoard_t black_pawns;
        BitBoard_t black_knights;
        BitBoard_t black_bishops;
        BitBoard_t black_rooks;
        BitBoard_t black_queens;
        BitBoard_t black_king;

        BitBoard_t white_pieces;
        BitBoard_t black_pieces;

        BitBoard_t all_pieces;

        BitBoard_t castling_rights;
        BitBoard_t enPassant_rights;

        unordered_map<string, BitBoard_t> boards_hash;

        BitBoard_t get_bitboard(bitboard_type board);
        string interpret_bitboard(BitBoard_t bitboard);
        BitBoard_t define_bitboard(const vector<string>& squares);
};

#endif