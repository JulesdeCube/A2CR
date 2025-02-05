#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "pac-man.h"
#include "GTK.h"
#include "ghost.h"

const int pac_man_speed = 6;
const int ghost_speed = 4;

//-------------------------INITIALISATION-------------------------------------
int map[31][28] = {
    // 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  //0
    {0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0},  //1
    {0, 2, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 2, 0},  //2
    {0, 2, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 2, 0},  //3
    {0, 2, 2, 2, 2, 3, 2, 0, 0, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 0, 0, 2, 3, 2, 2, 2, 2, 0},  //4
    {0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0},  //5
    {0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0},  //6
    {0, 2, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 2, 0},  //7
    {0, 2, 0, 0, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2, 0, 0, 2, 0},  //8
    {0, 2, 0, 0, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2, 0, 0, 2, 0},  //9
    {5, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 5},  //10
    {0, 2, 0, 0, 0, 0, 2, 0, 0, 1, 0, 0, 0, 4, 4, 0, 0, 0, 1, 0, 0, 2, 0, 0, 0, 0, 2, 0},  //11
    {0, 2, 0, 0, 0, 0, 2, 0, 0, 1, 0, 4, 4, 4, 4, 4, 4, 0, 1, 0, 0, 2, 0, 0, 0, 0, 2, 0},  //12
    {0, 2, 0, 0, 0, 0, 2, 0, 0, 1, 0, 4, 4, 4, 4, 4, 4, 0, 1, 0, 0, 2, 0, 0, 0, 0, 2, 0},  //13
    {0, 2, 2, 2, 2, 2, 2, 0, 0, 1, 0, 4, 4, 4, 4, 4, 4, 0, 1, 0, 0, 2, 2, 2, 2, 2, 2, 0},  //14
    {0, 1, 0, 0, 0, 0, 2, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 2, 0, 0, 0, 0, 1, 0},  //15
    {0, 1, 0, 0, 0, 0, 2, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 2, 0, 0, 0, 0, 1, 0},  //16
    {0, 1, 1, 1, 0, 0, 2, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 2, 0, 0, 1, 1, 1, 0},  //17
    {0, 0, 0, 1, 0, 0, 2, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 2, 0, 0, 1, 0, 0, 0},  //18
    {0, 0, 0, 1, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 0, 1, 0, 0, 0},  //19
    {5, 1, 1, 1, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 1, 1, 1, 5},  //20
    {0, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1, 0},  //21
    {0, 1, 0, 0, 0, 0, 2, 0, 0, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 0, 0, 2, 0, 0, 0, 0, 1, 0},  //22
    {0, 2, 2, 2, 2, 2, 2, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 2, 2, 2, 2, 2, 2, 0},  //23
    {0, 2, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 2, 0},  //24
    {0, 2, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 2, 0},  //25
    {0, 2, 0, 0, 2, 3, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 3, 2, 0, 0, 2, 0},  //26
    {0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0},  //27
    {0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0},  //28
    {0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0},  //29
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}; //30

int pac_man_open[7][7] = {
    {1, 1, 0, 0, 0, 1, 1},
    {1, 0, 0, 1, 0, 0, 1},
    {0, 0, 0, 0, 0, 1, 1},
    {0, 0, 0, 0, 1, 1, 1},
    {0, 0, 0, 0, 0, 1, 1},
    {1, 0, 0, 0, 0, 0, 1},
    {1, 1, 0, 0, 0, 1, 1}};

int pac_man_closed[7][7] = {
    {1, 1, 0, 0, 0, 1, 1},
    {1, 0, 0, 1, 0, 0, 1},
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 1},
    {1, 1, 0, 0, 0, 1, 1}};

int ghost_pixel_art[7][7] = {
    {0, 0, 1, 1, 1, 0, 0},
    {0, 1, 1, 1, 1, 1, 0},
    {1, 1, 1, 1, 1, 1, 1},
    {1, 1, 0, 1, 0, 1, 1},
    {1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1},
    {1, 0, 1, 0, 1, 0, 1}};

Game game =
    {
        .status = 0, //status 0 = stopped, status 1 = playing
        .map = (int *)map,
        .pac_man_open = (int *)pac_man_open,
        .pac_man_closed = (int *)pac_man_closed,
        .ghost_pixel_art = (int *)ghost_pixel_art,
        .score = 0,
        .live = 3,
        .level = 1,
        .pacgum = 0,
        .chase = 0,
        .open = 0,
        .combo = 200,
        .pac_man =
            {
                .x = 307,
                .y = 377,
                .dir = 'N',
                .reqdir = 'N',
                .color = 'y',
            },
        .blinky =
            {
                .x = 318, //13
                .y = 311, //14
                .dir = 'N',
            },
        .inky =
            {
                .x = 318, //13
                .y = 311, //14
                .dir = 'N',
            },
        .clyde =
            {
                .x = 318, //14
                .y = 311, //13
                .dir = 'N',
            },
        .pinky =
            {
                .x = 318, //13
                .y = 311, //14
                .dir = 'N',
            },
};

//-----------------------FUNCTIONS---------------------------------------------
void *get_game()
{
  return &game;
}

void change_game_status(int status)
{
  game.status = status;
}

void randome_dir(Player *pl)
{
  int boo = 0;
  int X, Y;
  pixel_To_MatCoord(pl->x, pl->y, &X, &Y);
  if (pl->dir == 'N' && map[X - 1][Y] == 0)
    boo = 1;
  if (pl->dir == 'S' && map[X + 1][Y] == 0)
    boo = 1;
  if (pl->dir == 'G' && map[X][Y - 1] == 0)
    boo = 1;
  if (pl->dir == 'D' && map[X + 1][Y + 1] == 0)
    boo = 1;

  if (boo == 1) //change of direction
  {
    srand(time(NULL));
    int ran = rand() % 3;
    char newdir = pl->dir;
    if (pl->dir == 'N')
    {

      if (ran == 0)
        newdir = 'G';
      if (ran == 1)
        newdir = 'D';
      if (ran == 2)
        newdir = 'S';
    }
    if (pl->dir == 'S')
    {

      if (ran == 0)
        newdir = 'G';
      if (ran == 1)
        newdir = 'D';
      if (ran == 2)
        newdir = 'N';
    }
    if (pl->dir == 'G')
    {

      if (ran == 0)
        newdir = 'N';
      if (ran == 1)
        newdir = 'D';
      if (ran == 2)
        newdir = 'S';
    }
    if (pl->dir == 'D')
    {

      if (ran == 0)
        newdir = 'G';
      if (ran == 1)
        newdir = 'N';
      if (ran == 2)
        newdir = 'S';
    }
    pl->dir = newdir;
  }
}

void respawn()
{
  game.pac_man.color = 'y';
  game.pac_man.x = 307;
  game.pac_man.y = 377;
  game.pac_man.dir = 'N';
  game.pac_man.reqdir = 'N';

  game.blinky.x = 318;
  game.blinky.y = 311;

  game.inky.x = 318;
  game.inky.y = 311;

  game.clyde.x = 318;
  game.clyde.y = 311;

  game.pinky.x = 318;
  game.pinky.y = 311;

  sleep(2);
}

void levelup()
{

  game.pacgum = 0;
  game.level = game.level + 1;
  char str[42];
  sprintf(str, "level : %i \n", game.level);
  set_level_label(str);
  for (int x = 0; x < 31; x++)
  {
    for (int y = 0; y < 28; y++)
    {
      if (map[x][y] == 6)
      {
        map[x][y] = 2;
        //cairo_rectangle(cr,X+9,Y+9,5,5);
      }
      if (map[x][y] == 7)
      {
        map[x][y] = 3;
        //cairo_rectangle(cr,X+4,Y+4,10,10);
      }
    }
  }
  respawn();
  draw(0, 0, 637, 760);
}

void restart()
{
  game.status = 0;
  respawn();
  game.live = 3;
  char tmp[42];
  sprintf(tmp, "Lives : %i \n", game.live);
  set_live_label(tmp);

  game.score = 0;
  char str[42];
  sprintf(str, "Score : %i \n", game.score);
  set_score_label(str);
  for (int x = 0; x < 31; x++)
  {
    for (int y = 0; y < 28; y++)
    {
      if (map[x][y] == 6)
      {
        map[x][y] = 2;
        //cairo_rectangle(cr,X+9,Y+9,5,5);
      }
      if (map[x][y] == 7)
      {
        map[x][y] = 3;
        //cairo_rectangle(cr,X+4,Y+4,10,10);
      }
    }
  }
  draw(0, 0, 637, 760);
  on_Pause_clicked();
}

void ghost_kill(int n)
{
  if (n == 1)
  {
    game.blinky.x = 318;
    game.blinky.y = 311;
  }
  if (n == 2)
  {
    game.inky.x = 318;
    game.inky.y = 311;
  }
  if (n == 4)
  {
    game.clyde.x = 318;
    game.clyde.y = 311;
  }
  if (n == 3)
  {
    game.pinky.x = 318;
    game.pinky.y = 311;
  }
  game.score = game.score + game.combo;
  char str[42];
  sprintf(str, "Score : %i \n", game.score);
  set_score_label(str);
  game.combo = game.combo * 2;
}

void is_pac_man_dead()
{
  int boo = 0;
  int X, Y;
  pixel_To_MatCoord(game.pac_man.x, game.pac_man.y, &X, &Y);
  int XB;
  int YB;
  pixel_To_MatCoord(game.blinky.x, game.blinky.y, &XB, &YB);
  if (X == XB && Y == YB)
  {
    boo = 1;
  }
  else
  {
    int XI;
    int YI;
    pixel_To_MatCoord(game.inky.x, game.inky.y, &XI, &YI);
    if (X == XI && Y == YI)
    {
      boo = 2;
    }
    else
    {
      int XP;
      int YP;
      pixel_To_MatCoord(game.pinky.x, game.pinky.y, &XP, &YP);
      if (X == XP && Y == YP)
      {
        boo = 3;
      }
      else
      {
        int XC;
        int YC;
        pixel_To_MatCoord(game.clyde.x, game.clyde.y, &XC, &YC);
        if (X == XC && Y == YC)
        {
          boo = 4;
        }
      }
    }
  }
  if (boo > 0)
  {
    if (game.chase == 0)
    {
      game.live = game.live - 1;
      char str[42];
      sprintf(str, "Lives : %i \n", game.live);
      set_live_label(str);
      respawn();
    }
    else
    {
      ghost_kill(boo);
    }
  }
}

void request_move(char dir)
{
  int X, Y;
  pixel_To_MatCoord(game.pac_man.x, game.pac_man.y, &X, &Y);
  if ((dir == 'N' && map[X - 1][Y] != 0) ||
      (dir == 'S' && map[X + 1][Y] != 0) ||
      (dir == 'G' && map[X][Y - 1] != 0) ||
      (dir == 'D' && map[X][Y + 1] != 0))
  {
    game.pac_man.dir = dir;
    game.pac_man.reqdir = dir;
  }
  else
    game.pac_man.reqdir = dir;
}

//modify the coords of each entity
void move_entity(int *x, int *y, char dir, int speed)
{
  int X_mat, Y_mat;
  pixel_To_MatCoord(*x, *y, &X_mat, &Y_mat);
  if (dir == 'N')
  {
    if (map[X_mat - 1][Y_mat] == 0)
    {
      int x1, y1;
      matCoord_To_Pixel(X_mat - 1, Y_mat, &x1, &y1);
      *y = CLAMP(*y - speed, y1 + 22, 800);
    }
    else
    {
      *y = *y - speed;
    }
  }
  if (dir == 'S')
  {
    if (map[X_mat + 1][Y_mat] == 0)
    {
      int x1, y1;
      matCoord_To_Pixel(X_mat + 1, Y_mat, &x1, &y1);
      *y = CLAMP(*y + speed, 0, y1 - 22);
    }
    else
    {
      *y = *y + speed;
    }
  }
  if (dir == 'G')
  {
    if (map[X_mat][Y_mat - 1] == 0)
    {
      int x1, y1;
      matCoord_To_Pixel(X_mat, Y_mat - 1, &x1, &y1);
      *x = CLAMP(*x - speed, x1 + 22, 800);
    }
    else
    {
      *x = *x - speed;
    }
  }
  if (dir == 'D')
  {
    if (map[X_mat][Y_mat + 1] == 0)
    {
      int x1, y1;
      matCoord_To_Pixel(X_mat, Y_mat + 1, &x1, &y1);
      *x = CLAMP(*x + speed, 0, x1 - 22);
    }
    else
    {
      *x = *x + speed;
    }
  }
}

// execute the pathfinding function for each ghost with parameters
void define_direction(Player *pl, char type)
{
  int X_mat, Y_mat;
  pixel_To_MatCoord(pl->x, pl->y, &X_mat, &Y_mat);
  int X_pm, Y_pm;
  pixel_To_MatCoord(game.pac_man.x, game.pac_man.y, &X_pm, &Y_pm);
  /*
  if(game.chase >0)
    {
      printf("invert coord \n");
      X_pm = 28-X_pm;
      Y_pm = 31-Y_pm;
    }
  */
  if (pl->dir == 'N')
  {
    if (type == 'b')
    {
      pl->dir = blinky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, map, X_mat * 28 + Y_mat + 28);
    }
    else if (type == 'p')
    {
      if (game.pac_man.dir == 'S')
        pl->dir = pinky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm + 28,
                        map, X_mat * 28 + Y_mat + 28);

      if (game.pac_man.dir == 'N')
        pl->dir = pinky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm - 28,
                        map, X_mat * 28 + Y_mat + 28);

      if (game.pac_man.dir == 'D')
        pl->dir = pinky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm + 1,
                        map, X_mat * 28 + Y_mat + 28);

      if (game.pac_man.dir == 'G')
        pl->dir = pinky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm - 1,
                        map, X_mat * 28 + Y_mat + 28);
    }
    else if (type == 'i')
    {
      if (game.pac_man.dir == 'S')
        pl->dir = inky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm + 28,
                       map, X_mat * 28 + Y_mat + 28);

      if (game.pac_man.dir == 'N')
        pl->dir = inky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm - 28,
                       map, X_mat * 28 + Y_mat + 28);

      if (game.pac_man.dir == 'D')
        pl->dir = inky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm + 1,
                       map, X_mat * 28 + Y_mat + 28);

      if (game.pac_man.dir == 'G')
        pl->dir = inky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm - 1,
                       map, X_mat * 28 + Y_mat + 28);
    }
    if (type == 'c')
    {
      pl->dir = clyde(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, map, X_mat * 28 + Y_mat + 28);
    }
  }
  else if (pl->dir == 'S')
  {
    if (type == 'b')
    {
      pl->dir = blinky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, map, X_mat * 28 + Y_mat - 28);
    }
    else if (type == 'p')
    {
      if (game.pac_man.dir == 'S')
        pl->dir = pinky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm + 28,
                        map, X_mat * 28 + Y_mat - 28);

      if (game.pac_man.dir == 'N')
        pl->dir = pinky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm - 28,
                        map, X_mat * 28 + Y_mat - 28);

      if (game.pac_man.dir == 'D')
        pl->dir = pinky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm + 1,
                        map, X_mat * 28 + Y_mat - 28);

      if (game.pac_man.dir == 'G')
        pl->dir = pinky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm - 1,
                        map, X_mat * 28 + Y_mat - 28);
    }
    else if (type == 'i')
    {
      if (game.pac_man.dir == 'S')
        pl->dir = inky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm + 28,
                       map, X_mat * 28 + Y_mat - 28);

      if (game.pac_man.dir == 'N')
        pl->dir = inky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm - 28,
                       map, X_mat * 28 + Y_mat - 28);

      if (game.pac_man.dir == 'D')
        pl->dir = inky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm + 1,
                       map, X_mat * 28 + Y_mat - 28);

      if (game.pac_man.dir == 'G')
        pl->dir = inky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm - 1,
                       map, X_mat * 28 + Y_mat - 28);
    }
    if (type == 'c')
    {
      pl->dir = clyde(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, map, X_mat * 28 + Y_mat - 28);
    }
  }
  else if (pl->dir == 'G')
  {
    if (type == 'b')
    {
      pl->dir = blinky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, map, X_mat * 28 + Y_mat + 1);
    }
    else if (type == 'p')
    {
      if (game.pac_man.dir == 'S')
        pl->dir = pinky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm + 28,
                        map, X_mat * 28 + Y_mat + 1);

      if (game.pac_man.dir == 'N')
        pl->dir = pinky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm - 28,
                        map, X_mat * 28 + Y_mat + 1);

      if (game.pac_man.dir == 'D')

        pl->dir = pinky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm + 1,
                        map, X_mat * 28 + Y_mat + 1);

      if (game.pac_man.dir == 'G')
        pl->dir = pinky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm - 1,
                        map, X_mat * 28 + Y_mat + 1);
    }
    else if (type == 'i')
    {
      if (game.pac_man.dir == 'S')
        pl->dir = inky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm + 28,
                       map, X_mat * 28 + Y_mat + 1);

      if (game.pac_man.dir == 'N')
        pl->dir = inky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm - 28,
                       map, X_mat * 28 + Y_mat + 1);

      if (game.pac_man.dir == 'D')
        pl->dir = inky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm + 1,
                       map, X_mat * 28 + Y_mat + 1);

      if (game.pac_man.dir == 'G')
        pl->dir = inky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm - 1,
                       map, X_mat * 28 + Y_mat + 1);
    }
    if (type == 'c')
    {
      pl->dir = clyde(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, map, X_mat * 28 + Y_mat + 1);
    }
  }
  else if (pl->dir == 'D')
  {
    if (type == 'b')
    {
      pl->dir = blinky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, map, X_mat * 28 + Y_mat - 1);
    }
    else if (type == 'p')
    {
      if (game.pac_man.dir == 'S')
        pl->dir = pinky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm + 28,
                        map, X_mat * 28 + Y_mat - 1);

      if (game.pac_man.dir == 'N')
        pl->dir = pinky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm - 28,
                        map, X_mat * 28 + Y_mat - 1);

      if (game.pac_man.dir == 'D')
        pl->dir = pinky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm + 1,
                        map, X_mat * 28 + Y_mat - 1);

      if (game.pac_man.dir == 'G')
        pl->dir = pinky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm - 1,
                        map, X_mat * 28 + Y_mat - 1);
    }
    else if (type == 'i')
    {
      if (game.pac_man.dir == 'S')
        pl->dir = inky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm + 28,
                       map, X_mat * 28 + Y_mat - 1);

      if (game.pac_man.dir == 'N')
        pl->dir = inky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm - 28,
                       map, X_mat * 28 + Y_mat - 1);

      if (game.pac_man.dir == 'D')
        pl->dir = inky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm + 1,
                       map, X_mat * 28 + Y_mat - 1);

      if (game.pac_man.dir == 'G')
        pl->dir = inky(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, X_pm * 28 + Y_pm - 1,
                       map, X_mat * 28 + Y_mat - 1);
    }
    if (type == 'c')
    {
      pl->dir = clyde(X_mat * 28 + Y_mat, X_pm * 28 + Y_pm, map, X_mat * 28 + Y_mat - 1);
    }
  }
}

gboolean loop()
{

  if (game.status == 0) //break loop if game is in pause status
    return TRUE;
  if (game.pacgum >= 258) //258 = max pac gum
    levelup();
  if (game.chase > 0)
  {
    game.chase = game.chase - 1;
    if (game.chase == 0)
    {
      game.pac_man.color = 'y';
      game.combo = 200;
    }
  }
  request_move(game.pac_man.reqdir);
  move_entity(&game.pac_man.x, &game.pac_man.y, game.pac_man.dir, pac_man_speed); //pac-man

  //---------------------------------GIVE INFOS----------------------------------
  int X, Y;
  pixel_To_MatCoord(game.pac_man.x, game.pac_man.y, &X, &Y);
  /*
  printf("\n---------------------NEW LOOP------------------------------\n");
  int X_mat_blinky;
  int Y_mat_blinky;
  pixel_To_MatCoord(game.blinky.x, game.blinky.y, &X_mat_blinky, &Y_mat_blinky);

  //print current coords
  printf("blinky coord:\n  x :%i(%i);\n  y:%i(%i);\npac man coord\n  x:%i(%i);\n  y:%i(%i);\n",
        X_mat_blinky,game.blinky.x, Y_mat_blinky, game.blinky.y,
        X,game.pac_man.x,Y,game.pac_man.y);
  printf("previous_dir: %c\n",game.blinky.dir);
  */
  if (game.chase == 0) //chase mode
  {
    //----------------------------BLINKY DIRECTION---------------------------------
    define_direction(&game.blinky, 'b');

    //---------------------------CLYDE DIRECTION-----------------------------------
    define_direction(&game.clyde, 'c');

    //---------------------------INKY DIRECTION------------------------------------

    define_direction(&game.inky, 'i');
    //---------------------------PINKY DIRECTION-----------------------------------

    define_direction(&game.pinky, 'p');
    //-----------------------------END-------------------------------------------
  }
  else //flee mode
  {
    randome_dir(&game.blinky);
    randome_dir(&game.clyde);
    randome_dir(&game.inky);
    randome_dir(&game.pinky);
  }

  move_entity(&game.blinky.x, &game.blinky.y, game.blinky.dir, ghost_speed);
  move_entity(&game.clyde.x, &game.clyde.y, game.clyde.dir, ghost_speed);
  move_entity(&game.inky.x, &game.inky.y, game.inky.dir, ghost_speed);
  move_entity(&game.pinky.x, &game.pinky.y, game.pinky.dir, ghost_speed);

  draw(0, 0, 637, 760);
  //---------------SCORE
  if (map[X][Y] == 2)
  {
    game.pacgum = game.pacgum + 1;
    map[X][Y] = 6;
    game.score = game.score + 10;
    char str[42];
    sprintf(str, "Score : %i \n", game.score);

    set_score_label(str);
  }
  if (map[X][Y] == 3)
  {
    game.pacgum = game.pacgum + 1;
    game.pac_man.color = 'b';
    game.chase = game.chase + 125;
    map[X][Y] = 7;
  }

  //----------DEAD or ALIVE
  is_pac_man_dead();
  if (game.live == -1)
    restart();

  //draw(game.pac_man.x - pac_man_speed, game.pac_man.y - pac_man_speed, 22 +
  //    pac_man_speed*2, 22 +pac_man_speed*2);
  //------------------------
  return TRUE;
}
