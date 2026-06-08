#pragma once
#include "pieces.h"
#include <string>

using namespace std;

class Board
{
    Piece *board[8][8];

    bool turn; // false = white turn and true =black turn

    bool moved;
    bool captured;
    bool check;
    int check_coords;
    bool game_ended;
    string winner;

    bool are_coords_on_board(int r, int c);
    bool is_turn_valid(int piece_r, int piece_c);
    bool is_same_type(int r1, int c1, int r2, int c2);

    bool pseudo_move(int r1, int c1, int r2, int c2);
    void place(int r1, int c1, int r2, int c2);
    void delete_piece(Piece *p);
    void promotion();

    void king_finder(Shade s, int &r, int &c);
    void blockage(int r1, int c1, int &result_r, int &result_c, int dy, int dx);
    bool on_check(int king_r, int king_c);
    bool checkmate(int king_r, int king_c);

    void generate_valid_moves(int r, int c);

    void reset_pieces(Shade s); // this will reset moves array of one color type
    void flip_turn();

public:
    Board();
    Piece *get_piece(int i, int j);
    void set_piece(int old_r, int old_c, int new_r, int new_c);
    int *get_valid_moves(int r, int c);

    // getters
    bool get_check() const;
    int get_check_coords() const;
    bool get_moved() const;
    bool get_captured() const;
    bool get_game_ended() const;
    string get_winner() const;

    ~Board();
};