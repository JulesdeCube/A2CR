#include <stdio.h>
#include <stdlib.h>
#include "pathfinding3.h"
#include "ghost.h"
// 2 et 6       7 et 9
const int wall = 0;
const int alley = 1;
const int alley_pac_gum = 2;
const int alley_super = 3;
const int fantom_home = 4;
const int tunnel = 5;
const int map_ylen = 31;
const int map_xlen = 28;

int map[31][28] ={
// 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //0
  {0,2,2,2,2,2,2,2,2,2,0,0,2,2,2,2,0,0,2,2,2,2,2,2,2,2,2,0}, //1
  {0,2,0,0,0,0,2,0,0,2,0,0,2,0,0,2,0,0,2,0,0,2,0,0,0,0,2,0}, //2
  {0,2,0,0,0,0,2,0,0,2,0,0,2,0,0,2,0,0,2,0,0,2,0,0,0,0,2,0}, //3
  {0,2,2,2,2,3,2,0,0,2,2,2,2,0,0,2,2,2,2,0,0,2,3,2,2,2,2,0}, //4
  {0,2,0,0,0,0,2,0,0,0,0,0,2,0,0,2,0,0,0,0,0,2,0,0,0,0,2,0}, //5
  {0,2,0,0,0,0,2,0,0,0,0,0,2,0,0,2,0,0,0,0,0,2,0,0,0,0,2,0}, //6
  {0,2,0,0,2,2,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,2,2,0,0,2,0}, //7
  {0,2,0,0,2,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,2,0,0,2,0}, //8
  {0,2,0,0,2,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,2,0,0,2,0}, //9
  {5,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,5}, //10
  {0,2,0,0,0,0,2,0,0,1,0,0,0,4,4,0,0,0,1,0,0,2,0,0,0,0,2,0}, //11
  {0,2,0,0,0,0,2,0,0,1,0,4,4,4,4,4,4,0,1,0,0,2,0,0,0,0,2,0}, //12
  {0,2,0,0,0,0,2,0,0,1,0,4,4,4,4,4,4,0,1,0,0,2,0,0,0,0,2,0}, //13
  {0,2,2,2,2,2,2,0,0,1,0,4,4,4,4,4,4,0,1,0,0,2,2,2,2,2,2,0}, //14
  {0,1,0,0,0,0,2,0,0,1,0,0,0,0,0,0,0,0,1,0,0,2,0,0,0,0,1,0}, //15
  {0,1,0,0,0,0,2,0,0,1,1,1,1,1,1,1,1,1,1,0,0,2,0,0,0,0,1,0}, //16
  {0,1,1,1,0,0,2,0,0,1,0,0,0,0,0,0,0,0,1,0,0,2,0,0,1,1,1,0}, //17
  {0,0,0,1,0,0,2,0,0,1,0,0,0,0,0,0,0,0,1,0,0,2,0,0,1,0,0,0}, //18
  {0,0,0,1,0,0,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,0,0,1,0,0,0}, //19
  {5,1,1,1,0,0,2,0,0,0,0,0,2,0,0,2,0,0,0,0,0,2,0,0,1,1,1,5}, //20
  {0,1,0,0,0,0,2,0,0,0,0,0,2,0,0,2,0,0,0,0,0,2,0,0,0,0,1,0}, //21
  {0,1,0,0,0,0,2,0,0,2,2,2,2,1,1,2,2,2,2,0,0,2,0,0,0,0,1,0}, //22
  {0,2,2,2,2,2,2,0,0,2,0,0,2,0,0,2,0,0,2,0,0,2,2,2,2,2,2,0}, //23
  {0,2,0,0,2,0,0,0,0,2,0,0,2,0,0,2,0,0,2,0,0,0,0,2,0,0,2,0}, //24
  {0,2,0,0,2,0,0,0,0,2,0,0,2,0,0,2,0,0,2,0,0,0,0,2,0,0,2,0}, //25
  {0,2,0,0,2,3,2,2,2,2,0,0,2,2,2,2,0,0,2,2,2,2,3,2,0,0,2,0}, //26
  {0,2,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,2,0}, //27
  {0,2,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,2,0}, //28
  {0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0}, //29
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}}; //30

int main(void)
{
  int ax = 20;
  int ay = 1;
  int bx = 27;
  int by = 1;
  int next;
  next = shortpath((int*)map, ((ax)*28+(ay+1)), (ax*28+ay), (bx*28+by));
  printf("direction = %d\n",next);
  char g1 = clyde(175,685,map,147);
  printf("clyde is going to : %c\n",g1);
  /*char g4 = blinky(430, 122, map, 457);

  printf("blinky is going to : %c\n",g4);


  char g2 = pinky(35,119,147,map,36);
  printf("pinky is going to : %c\n",g2);
  char g3 = inky(382,466,463,map,410);
  printf("inky is going to : %c\n",g3);
  char g5 = inky(382,466,463,map,410);
  printf("inky is going to : %c\n",g5);*/
  return 1;
}
