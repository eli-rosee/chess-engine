// board.h

#ifndef BOARD_H
#define BOARD_H

#include <cstdint>
#include <string>
#include <unordered_map>

using namespace std;

class board
{

    public:

        board();
        ~board();

        int print_piece(string piece);

        typedef uint64_t BitBoard_t;

    private:
        BitBoard_t whitePawns;
        BitBoard_t whiteKnights;
        BitBoard_t whiteBishops;
        BitBoard_t whiteRooks;
        BitBoard_t whiteQueens;
        BitBoard_t whiteKing;

        BitBoard_t blackPawns;
        BitBoard_t blackKnights;
        BitBoard_t blackBishops;
        BitBoard_t blackRooks;
        BitBoard_t blackQueens;
        BitBoard_t blackKing;

        unordered_map<string, BitBoard_t> boards_hash;

        BitBoard_t get_bitboard(string piece);
};

#endif