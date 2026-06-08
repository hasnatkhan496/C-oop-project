#include "game.h"

//for pieces_png
void Game::process_icons() {
  textures[0][0] = LoadTexture("../pieces_png/white_pawn.png");
  textures[0][1] = LoadTexture("../pieces_png/white_horse.png");
  textures[0][2] = LoadTexture("../pieces_png/white_bishop.png");
  textures[0][3] = LoadTexture("../pieces_png/white_rook.png");
  textures[0][4] = LoadTexture("../pieces_png/white_queen.png");
  textures[0][5] = LoadTexture("../pieces_png/white_king.png");

  textures[1][0] = LoadTexture("../pieces_png/black_pawn.png");
  textures[1][1] = LoadTexture("../pieces_png/black_horse.png");
  textures[1][2] = LoadTexture("../pieces_png/black_bishop.png");
  textures[1][3] = LoadTexture("../pieces_png/black_rook.png");
  textures[1][4] = LoadTexture("../pieces_png/black_queen.png");
  textures[1][5] = LoadTexture("../pieces_png/black_king.png");
}
void Game::unload_icons() {
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 6; j++) {
      UnloadTexture(textures[i][j]);
    }
  }
}

//for sound
void Game::process_sounds()
{
  sounds[0]=LoadSound("../sounds/move.ogg");
  sounds[1]=LoadSound("../sounds/captured.ogg");
  sounds[2]=LoadSound("../sounds/check.ogg");
  sounds[3]=LoadSound("../sounds/checkmate.ogg");
  
}
void Game::unload_sounds()
{
  for(int i=0;i<4;i++)
  {
    UnloadSound(sounds[i]);
  }
}
void Game::make_sound()
{
  //checkmate sound highest priority -> movesound lowest priority
  //one sound at a time

  if(checkmate_sound)
  {
    PlaySound(sounds[3]);
    checkmate_sound=false;
  }
  else if(check_sound)
  {
    PlaySound(sounds[2]);
    check_sound=false;
  }
  else if(captured_sound)
  {
    PlaySound(sounds[1]);
    captured_sound=false;
  }
  else if(move_sound)
  {
    PlaySound(sounds[0]);
    move_sound=false;
  }
  

}

//display
void Game::display_validmoves()
{
    for(int i=0;i<total_moves;i++)
    {
        int g_r=get_row(valid_moves[i]);
        int g_c=get_column(valid_moves[i]);

        int dot_x=cell_width*g_c+cell_width/2;
        int dot_y=cell_height*g_r+cell_height/2;

        DrawCircle(dot_x,dot_y,cell_width/7,Fade(color_dot, 0.4f));
    }
}
void Game::display_piece(int cell_x, int cell_y, int i, int j) {
  Piece *p = b.get_piece(i, j);

  if (p != nullptr) {
    int t_r = get_row(p->piece_png());
    int t_c = get_column(p->piece_png());

    float cell_size = cell_width * cell_height;
    float icon_size = 148* 148; // 128px resolution
    int shift_x=(148-cell_width)/8;
    int shift_y=(148-cell_width)/8;
    double scaling_factor = cell_size/icon_size;
    DrawTextureEx(textures[t_r][t_c],
                  (Vector2){cell_x+shift_x, cell_y +shift_y},  0.0f, scaling_factor+0.1, WHITE);
}
}
void Game::display_board() {

  int cell_x;
  int cell_y;
  Color c;

  for (int i = 0; i <cells_per_column ; i++) {
    for (int j = 0; j <cells_per_row ; j++) {
      cell_x =  j * cell_width;
      cell_y =  i * cell_height;

      //selecting color
      if(b.get_check()==true&&i==get_row(b.get_check_coords())&&j==get_column(b.get_check_coords()))
      {
        c=color_threat;
      }
      else if((i+j)%2==0)
      {
        c=color1;
      }
      else
      {
        c=color2;
      }
      

      DrawRectangle(cell_x, cell_y, cell_width, cell_height,c);
      display_piece(cell_x, cell_y, i, j);
    }
  }
}

//for input
int Game::extract_input()
{
    float mouseX = GetMousePosition().x;
    float mouseY = GetMousePosition().y;
    
    mouseX=mouseX;
    mouseY=mouseY;

    float c=mouseX/cell_width;
    float r=mouseY/cell_height;

    if (r<0||r>=8||c<0||c>=8)// r and c could be in -ve but in points and values 7.8 is valid r or c so >=8
    {
        return -1;
    }
    return static_cast<int>(r)*10+static_cast<int>(c);
}
void Game::input_decision_maker()
{
    if(input1!=-1&&input2!=-1)
    {
        b.set_piece(get_row(input1),get_column(input1),get_row(input2),get_column(input2));
        input1=-1;
        input2=-1;
        valid_moves=nullptr;
        //do move then reset input 1 and 2 to -1
        move_sound=b.get_moved();
        captured_sound=b.get_captured();
        check_sound=b.get_check();
        checkmate_sound=b.get_game_ended();

    }
    else if(input1!=-1&&input2==-1) // if any  piece is selected
    {
      
        if(valid_moves==nullptr)
        {
          valid_moves=b.get_valid_moves(get_row(input1),get_column(input1)); //this if return null ptr if invalid location
        }


        if(valid_moves!=nullptr)
        {
        total_moves=b.get_piece(get_row(input1),get_column(input1))->get_moves_count();
        display_validmoves();
        }
        else
        {
          input1=-1; 
        }

      }
    

}
void Game::input_taker()
{
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)&&input1!=-1)
    {
        input2=extract_input(); 
        if(input2==-1)
        {
            input1=-1;
        }

    }
    else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        input1=extract_input(); 
        input2=-1;
        
    }
}

//winscreen
void Game::win_screen(string message)
{
    DrawRectangle(0,0,width,height,Fade(BLACK, 0.65f));//making full screen dull

  
    float boxWidth  = width/2;
    float boxHeight = height/5;

    float boxX = (width  - boxWidth)  / 2;
    float boxY = (height - boxHeight) / 2;

  
    DrawRectangleRounded(Rectangle{ boxX, boxY, boxWidth, boxHeight },0.15f,20,Color{35, 35, 45, 255});

    DrawRectangleRoundedLines(Rectangle{ boxX, boxY, boxWidth, boxHeight },0.15f,20,GOLD);//golden outline

    const char* title = "VICTORY";

    int titleSize = 42;
    int titleWidth = MeasureText(title, titleSize);

    DrawText(title,width/2 - titleWidth/2,boxY + 30,titleSize,GOLD);

    int textSize = 30;
    int textWidth = MeasureText(message.c_str(), textSize);

    DrawText(message.c_str(),width/2 - textWidth/2,boxY + 105,textSize,RAYWHITE);


    const char* hint = "Press ENTER to continue";

    int hintSize = 20;
    int hintWidth = MeasureText(hint, hintSize);

    DrawText(hint,width/2 - hintWidth/2,boxY + boxHeight/2+60,hintSize,Fade(LIGHTGRAY, 0.8f));
  
}

//public
Game::Game(const int w, const int h,Color c1,Color c2,Color t,Color d) 
{  
  width = w;
  height = h;
  color1=c1;
  color2=c2;
  color_threat=t;
  color_dot=d;

  cells_per_row = 8;
  cells_per_column = 8;
  cell_width = width / cells_per_row;
  cell_height = height / cells_per_column;

  valid_moves=nullptr;
  total_moves=0;
  
  input1 = -1;
  input2 = -1;

  move_sound=false;
  captured_sound=false;
  check_sound=false;
  checkmate_sound=false;

  win_screen_displayed=false;

  InitWindow(width, height, "Chess");
  InitAudioDevice();
  process_icons();
  process_sounds();
}

void Game::gameloop() {

  while (!WindowShouldClose()) {

    BeginDrawing();
    ClearBackground(DARKGRAY);
    display_board();
    

    input_decision_maker();

    input_taker();

    make_sound();

    if(b.get_game_ended()==true&&win_screen_displayed==false)
    {
      string message = b.get_winner()+" Wins!!";
        
      win_screen(message);
      if(IsKeyPressed(KEY_ENTER))
      {
        win_screen_displayed=true;
      }

    }
    


    EndDrawing();
  }

  unload_icons();
  unload_sounds();
  CloseWindow();
}