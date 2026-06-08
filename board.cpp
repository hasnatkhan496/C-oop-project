#include "board.h"

/////Board Class///
bool Board::are_coords_on_board(int r, int c)
{
  if (r < 0 || r > 7 || c < 0 || c > 7)
  {
    return false;
  }
  return true;
}
bool Board::is_turn_valid(int piece_r, int piece_c)
{
  if (board[piece_r][piece_c] == nullptr)
    return false;
  else if (board[piece_r][piece_c]->get_color() == White && turn == false)
  {
    return true;
  }
  else if (board[piece_r][piece_c]->get_color() == Black && turn == true)
  {
    return true;
  }
  return false;
}
bool Board::is_same_type(int r1, int c1, int r2, int c2)
{
  return board[r2][c2] != nullptr && board[r1][c1]->get_color() == board[r2][c2]->get_color();
}

bool Board::pseudo_move(int r1, int c1, int r2, int c2)
{

  int king_coords[2];
  bool checked;
  Piece *temp;
  temp = board[r2][c2];

  if (is_same_type(r1, c1, r2, c2))
  {
    return false;
  }

  if (!board[r1][c1]->is_valid(board, r1, c1, r2, c2))
  {
    return false;
  }

  // doing and checking about threat
  place(r1, c1, r2, c2);
  king_finder(board[r2][c2]->get_color(), king_coords[0], king_coords[1]);
  checked = on_check(king_coords[0], king_coords[1]);

  // reversing move
  place(r2, c2, r1, c1);
  board[r2][c2] = temp;

  if (checked)
  {
    return false;
  }
  else
  {
    return true;
  }
}
void Board::place(int r1, int c1, int r2, int c2)
{
  board[r2][c2] = board[r1][c1];
  board[r1][c1] = nullptr;
}
void Board::delete_piece(Piece *p)
{
  if (p != nullptr)
  {
    delete p;
    p = nullptr;
  }
}
void Board::promotion()
{
  int r = 7 * turn; // white turn then 0th row and if black turn then 7th turn to check promotion
  for (int j = 0; j < 8; j++)
  {
    Piece *p = board[r][j];
    if (p != nullptr && p->piece_png() % 10 == 0) // if pawn and on the last respective row
    {
      delete p;
      p = nullptr;
      board[r][j] = new Queen(static_cast<Shade>(turn)); // make queen
      break;                                             // break because one promotion at a time is possibles
    }
  }
}

void Board::king_finder(Shade s, int &r, int &c)
{
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      if (board[i][j] != nullptr && board[i][j]->piece_png() % 10 == 5 && board[i][j]->get_color() == s)
      {
        r = i;
        c = j;
        return;
      }
    }
  }
}
void Board::blockage(int r1, int c1, int &result_r, int &result_c, int dy, int dx)
{

  if (dx == 0 && dy == 0)
  {
    return;
  }

  // to go up in 2D array i should decrement and i want to put dy=1 for going upward
  int i = r1;
  int j = c1;

  while (true)
  {

    if (!are_coords_on_board(i + dy, j + dx)) // loop breaking condition
    {
      break;
    }

    i += dy;
    j += dx;

    if (board[i][j] != nullptr)
    {
      break;
    }
  }

  result_r = i;
  result_c = j;
}
bool Board::on_check(int king_r, int king_c)
{

  int blocker_r;
  int blocker_c;

  for (int i = -1; i <= 1; i++)
  {
    for (int j = -1; j <= 1; j++)
    {
      if (i == 0 && j == 0)
      {
        continue;
      }

      blockage(king_r, king_c, blocker_r, blocker_c, i, j);

      if (board[blocker_r][blocker_c] != nullptr &&
          board[king_r][king_c]->get_color() != board[blocker_r][blocker_c]->get_color())
      {

        if (board[blocker_r][blocker_c]->is_valid(board, blocker_r, blocker_c, king_r, king_c))
        {
          return true;
        }
      }
    }
  }

  // horse nearby check
  int dx[] = {1, 1, -1, -1, 2, 2, -2, -2};
  int dy[] = {2, -2, 2, -2, 1, -1, 1, -1}; // written all possible combitnation to find horse in parallel
  for (int i = 0; i < 8; i++)
  {

    if (are_coords_on_board(king_r + dy[i], king_c + dx[i]) && board[king_r + dy[i]][king_c + dx[i]] != nullptr &&
        board[king_r][king_c]->get_color() != board[king_r + dy[i]][king_c + dx[i]]->get_color())
    {

      if (board[king_r + dy[i]][king_c + dx[i]]->is_valid(board, king_r + dy[i], king_c + dx[i], king_r, king_c))
      {
        return true;
      }
    }
  }

  return false;
}
bool Board::checkmate(int king_r, int king_c)
{
  Shade color = board[king_r][king_c]->get_color();

  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      if (board[i][j] == nullptr || board[i][j]->get_color() != color)
      {
        continue;
      }

      for (int r = 0; r < 8; r++)
      {
        for (int c = 0; c < 8; c++)
        {
          if (pseudo_move(i, j, r, c) == true) // performing all possible moves for one color if any is valid then no checkmate
          {
            return false;
          }
        }
      }
    }
  }
  return true;
}

void Board::generate_valid_moves(int r, int c)
{
  Piece *p = board[r][c];

  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      if (pseudo_move(r, c, i, j))
      {
        p->add_move(i * 10 + j);
      }
    }
  }
}

void Board::reset_pieces(Shade s)
{
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      if (board[i][j] != nullptr && board[i][j]->get_color() == s)
      {
        board[i][j]->reset_moves();
      }
    }
  }
}
void Board::flip_turn()
{
  turn = !turn;
}

// public
Board::Board()
{
  // black side setup
  board[0][0] = new Rook(Black);
  board[0][1] = new Horse(Black);
  board[0][2] = new Bishop(Black);
  board[0][3] = new Queen(Black);
  board[0][4] = new King(Black);
  board[0][5] = new Bishop(Black);
  board[0][6] = new Horse(Black);
  board[0][7] = new Rook(Black);
  for (int j = 0; j < 8; j++)
  {
    board[1][j] = new Pawn(Black);
  }

  // making middle empty
  for (int i = 2; i < 6; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      board[i][j] = nullptr;
    }
  }

  // White side setup
  for (int j = 0; j < 8; j++)
  {

    board[6][j] = new Pawn(White);
  }

  board[7][0] = new Rook(White);
  board[7][1] = new Horse(White);
  board[7][2] = new Bishop(White);
  board[7][3] = new Queen(White);
  board[7][4] = new King(White);
  board[7][5] = new Bishop(White);
  board[7][6] = new Horse(White);
  board[7][7] = new Rook(White);

  turn = false;
  check = false;
  moved = false;
  captured = false;
  check_coords = -1;
  game_ended = false;
  winner = "";
}

Piece *Board::get_piece(int i, int j)
{
  return board[i][j];
}

void Board::set_piece(int old_r, int old_c, int new_r, int new_c)
{
  moved = false;
  captured = false;

  if (!is_turn_valid(old_r, old_c))
  {
    return;
  }

  if (!board[old_r][old_c]->search(new_r, new_c))
  {
    return;
  }

  moved = true; // after searching we are sure that piece will will move or not
  if (board[new_r][new_c] != nullptr)
  {
    captured = true;
  }

  delete_piece(board[new_r][new_c]);
  place(old_r, old_c, new_r, new_c);
  board[new_r][new_c]->change_moved_state(); // changing the moved variable in the piece which is moved
  promotion();                               // check if promotion should happen

  check = false; // reseting check here because check resets automatically after a valid move
  check_coords=-1;

  int oppositon_king_coords[2];
  king_finder(static_cast<Shade>(!turn), oppositon_king_coords[0], oppositon_king_coords[1]);
  if (on_check(oppositon_king_coords[0], oppositon_king_coords[1]))
  {
    check = true;
    check_coords = oppositon_king_coords[0] * 10 + oppositon_king_coords[1]; // i*10+j

    if (checkmate(oppositon_king_coords[0], oppositon_king_coords[1]))
    {

      game_ended = true;
      winner = ((turn == 0) ? "White" : "Black");
    }
  }

  reset_pieces(static_cast<Shade>(turn));
  flip_turn();
}

int *Board::get_valid_moves(int r, int c)
{
  if (board[r][c] == nullptr || !is_turn_valid(r, c))
  {
    return nullptr;
  }

  Piece *p = board[r][c];
  if (p->get_moves_count() > 0)
  {
    return p->get_moves();
  }
  else
  {
    generate_valid_moves(r, c);
    return p->get_moves();
  }
}

bool Board::get_check() const
{
  return check;
}
int Board::get_check_coords() const
{
  return check_coords;
}
bool Board::get_game_ended() const
{
  return game_ended;
}
string Board::get_winner() const
{
  return winner;
}
bool Board::get_moved() const
{
  return moved;
}
bool Board::get_captured() const
{
  return captured;
}

Board::~Board()
{
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      delete_piece(board[i][j]);
    }
  }
}