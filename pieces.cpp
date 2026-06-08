#include "pieces.h"
#include <cmath>

//////Helper Functions/////
int get_column(int num)
{
  return num%10;
}
int get_row(int num)
{
  return (num/10)%10;
}

bool is_target_in_line_of_sight(Piece *board[8][8], int r1, int c1,int r2,int c2 ,int dx,int dy)
{

  if(dx==0&&dy==0)
  {
    return false;
  }

  //to go up in 2D array i should decrement and i want to put dy=1 for going upward
  int i=r1;
  int j=c1;

  while(true)
  {
    i+=dy;
    j+=dx;

    if(i<0||i>7||j<0||j>7)  //loop breaking condition
    {
      break;
    }

    if(i==r2&&j==c2)
    {
      return true;
    }
    if (board[i][j]!=nullptr)
    {
      break;
    }

  }

  return false;

}


/////////////////////
//////Piece class////
/////////////////////

Piece::Piece(Shade s) {

  sh = s;
  moved=false;

  size = 1;
  total_moves = 0;
  moves = new int[size];
}
Shade Piece::get_color() 
{
   return sh;
   }
void Piece::change_moved_state()
{
  moved=true;
}

void Piece::add_move(int m) {

  total_moves++;

  if (total_moves > size) // if array got filled
  {

    size = size * 2;
    int *new_moves = new int[size];

    for (int i = 0; i < total_moves - 1; i++) {
      new_moves[i] = moves[i];
    }

    delete[] moves;
    moves = new_moves;
    new_moves = nullptr;
  }

  moves[total_moves - 1] = m;
}
bool Piece::search(int r ,int c)
{
  int location=r*10+c;
  for(int i=0;i<total_moves;i++)
  {
    if(moves[i]==location)
    {
      return true;
    }
  }

return false;
}
void Piece:: reset_moves()
    {
        if(moves!=nullptr)
        {
            delete []moves;
        }

        size = 1;
        total_moves = 0;
        moves = new int[size];

    }

int* Piece::get_moves() const
{
  return moves;
}
int  Piece::get_moves_count() const
{
  return total_moves;
}

Piece::~Piece()
{
  
  if(moves!=nullptr)
  {
    delete []moves;
  }  
  moves=nullptr;
}


///////////////////
////////Pawn////////
/////////////////

Pawn::Pawn(Shade s) : Piece(s) {}
int Pawn::piece_png() { return static_cast<int>(get_color())*10+0; }
bool Pawn::is_valid(Piece *board[8][8],int r1,int c1,int r2,int c2) {
  {
    //already checked for same type
    int direction=(get_color()==White? -1:1);//white moves upward so -1

    int i=r1;
    for(int count=0;count<1+!moved;count++)
    {
      i+=direction;
      if(board[i][c1]==nullptr)
      {
        if(i==r2&&c1==c2)
        {
          return true;
        }
      }
      else 
        break;
    }

    if (board[r2][c2]!=nullptr&&r1+direction==r2)
    {
      if (c1!=0&&c1-1==c2)
      {
        return true;
      }
      else if (c1!=7&&c1+1==c2)
      {
        return true;
      }
    }
    return false;
  }
}
///////////////////////////
///////Horse/////////////
///////////////////////

Horse::Horse(Shade s) : Piece(s) {}
int Horse::piece_png() { return static_cast<int>(get_color())*10+1; }
bool Horse::is_valid(Piece *board[8][8],int r1,int c1,int r2,int c2) 
{
 //already done same type check
  if((r1+2==r2||r1-2==r2)&&(c1+1==c2||c1-1==c2))
  {
    return true;
 }//upper-lower L

  else if((r1+1==r2||r1-1==r2)&&(c1+2==c2||c1-2==c2))
  {
    return true;
  }//right-left L
 else 
 {
  return false;
 }


}

///////////////////////////////
//////////Bishop////////////////
/////////////////////////////
Bishop::Bishop(Shade s) : Piece(s) {}
int Bishop::piece_png() { return static_cast<int>(get_color())*10+2; }
bool Bishop::is_valid(Piece *board[8][8],int r1,int c1,int r2,int c2) 
{

  int dx=c2-c1;
  int dy=r2-r1;
 
  if(abs(dx)!=abs(dy))//this indicates that the required move should exist on diagonal
  {
    return false;
  }

  dx=(dx>0?1:-1);
  dy=(dy>0?1:-1);
  //this will detect in which diagonal should bishop move top right,bottom right,top left,bottom left


  return is_target_in_line_of_sight(board,r1,c1,r2,c2,dx,dy);

}

////////////////////////////////
////////////Rook///////////////
//////////////////////////////

Rook::Rook(Shade s) : Piece(s) {}
int Rook::piece_png() { return static_cast<int>(get_color())*10+3; }
bool Rook::is_valid(Piece *board[8][8],int r1,int c1,int r2,int c2) 
{
  int dx=c2-c1;
  int dy=r2-r1;
 
  if(dx!=0&&dy!=0)//to exist on verticle path or horitzontal path one of change should be 0
  {
    return false;
  }

  if (dx!=0)
  {
    dx=(dx>0?1:-1);
  }
  else if(dy!=0)
  {
    dy=(dy>0?1:-1);
  }

  return is_target_in_line_of_sight(board,r1,c1,r2,c2,dx,dy);


}

/////////////////////////////////
//////////Queen///////////////
///////////////////////////////

Queen::Queen(Shade s) : Piece(s) {}
int Queen::piece_png() { return static_cast<int>(get_color())*10+4; }
bool Queen::is_valid(Piece *board[8][8],int r1,int c1,int r2,int c2) 
{

  int dx=c2-c1;
  int dy=r2-r1;
 
  if((dx!=0&&dy!=0)&&abs(dx)!=abs(dy))//means dont exist on verticle horizontal and on any digonal path
  {
    return false;
  }

  //if dx or dy is 0 means rooks path else bishops path
  if (dx!=0) 
  {
    dx=(dx>0?1:-1);
  }
  if(dy!=0)
  {
    dy=(dy>0?1:-1);
  }

  return is_target_in_line_of_sight(board,r1,c1,r2,c2,dx,dy);

}

//////////////////////////
///////King////////////////
//////////////////////////

King::King(Shade s) : Piece(s) {}
int King::piece_png() { return static_cast<int>(get_color())*10+5; }
bool King::is_valid(Piece *board[8][8],int r1,int c1,int r2,int c2)  
{
  int dx=c2-c1;
  int dy=r2-r1;

  if(dx==0&&dy==0)
  {
    return false;
  }
  return !(abs(dx)>1||abs(dy)>1);

}
