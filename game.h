#pragma once
#include "board.h"
#include "raylib.h"

class Game
{   //size and color config
    int width;
    int height;
    Color color1,color2;
    Color color_threat;
    Color color_dot;

    //board and cells on board
    Board b;
    int cells_per_row;
    int cells_per_column; // could be one variable
    int cell_height;
    int cell_width;

    //for pieces png
    Texture2D textures[2][6]; // at first row all white piece texture and at second all black piece
    void process_icons();
    void unload_icons();

    //for sound
    bool move_sound;
    bool captured_sound;
    bool check_sound;
    bool checkmate_sound;
    Sound sounds[4];
    void unload_sounds();
    void process_sounds();
    void make_sound();

    //display
    int *valid_moves;
    int total_moves;
    void display_validmoves();
    void display_piece(int cell_x, int cell_y, int i, int j);
    void display_board();
    

    //for input
    int input1;
    int input2;
    int extract_input();
    void input_taker();
    void input_decision_maker();

    //win screen
    bool win_screen_displayed;
    void win_screen(string message);
    
    
    public:
    Game(const int w, const int h,Color c1,Color c2,Color t,Color d);
    void gameloop();
};
