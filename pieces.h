#pragma once

// helper functions///
/*through out the project i will us these function
to get index from number
*/
int get_column(int num);
int get_row(int num);

enum Shade
{
    White,
    Black,
};

class Pawn;
class Rook;
class Bishop;
class Horse;
class Queen;
class King;

class Piece
{
    Shade sh;

    int *moves; // we will have double digit number right digit will represent column and left will represnt row(we will use %)
    int size;
    int total_moves;

protected:
    bool moved;

public:
    Piece(Shade s);
    Shade get_color();
    void change_moved_state();

    //operation on int* moves
    void add_move(int m); // will be used to add moves in *moves array
    bool search(int r,int c);
    void reset_moves();
    
    //getters
    int *get_moves() const;
    int get_moves_count() const;

    //polmorphic functions    
    virtual int piece_png() = 0; // this will return the coordinatie of texture in texture array game.class
    virtual bool is_valid(Piece *board[8][8], int r1, int c1, int r2, int c2) = 0;

    virtual ~Piece();
};

class Pawn : public Piece
{

public:
    Pawn(Shade s);
    int piece_png() override;
    bool is_valid(Piece *board[8][8], int r1, int c1, int r2, int c2) override;
};

class Horse : public Piece
{

public:
    Horse(Shade s);
    int piece_png() override;
    bool is_valid(Piece *board[8][8], int r1, int c1, int r2, int c2) override;
};

class Bishop : public Piece
{

public:
    Bishop(Shade s);
    int piece_png() override;
    bool is_valid(Piece *board[8][8], int r1, int c1, int r2, int c2) override;
};

class Rook : public Piece
{

public:
    Rook(Shade s);
    int piece_png() override;
    bool is_valid(Piece *board[8][8], int r1, int c1, int r2, int c2) override;
};

class Queen : public Piece
{

public:
    Queen(Shade s);
    int piece_png() override;
    bool is_valid(Piece *board[8][8], int r1, int c1, int r2, int c2) override;
};

class King : public Piece
{

public:
    King(Shade s);
    int piece_png() override;
    bool is_valid(Piece *board[8][8], int r1, int c1, int r2, int c2) override;
};