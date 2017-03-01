#include "SDL.h"
#include "Sprite.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Block{

private:
  int x,y,color;
  int (*board)[10][20];
  

public:
  Block(int nx, int ny, int nt, int (*nboard)[10][20]){
    x = nx;
    y = ny;
    cout << x << "," << y << endl;
    color = nt;
    board = nboard;
    (*board[x][y]) = color;
  }
  
  bool checkRelative(int rx, int ry){
    return board[x+rx][y+ry];

  }
  void moveRelative(int rx, int ry){
    (*board)[x][y] = 0;
    x += rx;
    y += ry;
    (*board)[x][y] = color;
  }
    

};


class Tetromino{

private:

  int type;
  Block* blocks[4];


public:

  Tetromino(int type, int (*board)[10][20]){
      
      if (type == 0) { //square
	blocks[0] = new Block(0,5,type,board);
	blocks[1] = new Block(0,6,type,board);
	blocks[2] = new Block(1,5,type,board);
	blocks[3] = new Block(1,6,type,board);
      }
      else if (type == 1) { //line
	blocks[0] = new Block(0,4,type,board);
        blocks[1] = new Block(0,5,type,board);
        blocks[2] = new Block(0,6,type,board);
        blocks[3] = new Block(0,7,type,board);
      }
      else if (type == 2) { //J
	blocks[0] = new Block(0,4,type,board);
        blocks[1] = new Block(0,5,type,board);
        blocks[2] = new Block(0,6,type,board);
        blocks[3] = new Block(1,6,type,board);
       }
      else if (type == 3) { //L
	blocks[0] = new Block(1,5,type,board);
        blocks[1] = new Block(0,5,type,board);
        blocks[2] = new Block(0,6,type,board);
        blocks[3] = new Block(0,7,type,board);
      }
      else if (type == 4) { //T
	blocks[0] = new Block(0,4,type,board);
        blocks[1] = new Block(0,5,type,board);
        blocks[2] = new Block(0,6,type,board);
        blocks[3] = new Block(1,5 ,type,board);
      }
      else if (type == 5) { //Z
        blocks[0] = new Block(0,4,type,board);
        blocks[1] = new Block(0,5,type,board);
        blocks[2] = new Block(1,5,type,board);
        blocks[3] = new Block(1,6,type,board);
      }
      else if (type == 6) { //S
	blocks[0] = new Block(1,4,type,board);
        blocks[1] = new Block(1,5,type,board);
        blocks[2] = new Block(0,5,type,board);
        blocks[3] = new Block(0,6,type,board);
      }
    }  
  void moveDown(){
    bool canMove = true;
    for (int i = 0; i < 4; i++){
      if(blocks[i]->checkRelative(0,1)){
	canMove = false;
      }
    }
    if (canMove){
      for(int i = 0; i>4; i++){
	blocks[i]->moveRelative(0,1);
      }
    }
    else{
      for(int i = 0; i<4; i++){
	delete blocks[i];
	delete this;
      }
    }
  }

};

void drawBoard(int board[10][20], int x, int y, int w, int h, SDL_Surface* screen);

int main(){

  srand (time(NULL));
  int window_height = 500;
  int window_width = 500;
  SDL_Init(SDL_INIT_EVERYTHING);

  SDL_Window *window = NULL;
  window = SDL_CreateWindow ("Window",
                             SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED,
                             window_height, window_width,
                             SDL_WINDOW_RESIZABLE);
  if (window == NULL){
    cout << "Something Happened" << endl;
  }





  SDL_Surface *screen = SDL_GetWindowSurface(window);
  
  Uint32 white = SDL_MapRGB(screen->format,255,255,255);
  Uint32 red = SDL_MapRGB(screen->format,255,0,0);
  Uint32 blue = SDL_MapRGB(screen->format,0,0,255);

  Uint32 startingTick;
  SDL_Event event;
  bool running = true;
  int board[10][20];
  for (int i = 0; i < 10; i++){
    for (int j =  0; j < 20; j++){
      board[i][j] = 0;
    }
  }

  Tetromino temp(1,&board);
  cout << board[0][7] << endl;
  cout << board[7][0] << endl;

   while (running == true){
    startingTick = SDL_GetTicks();
    SDL_FillRect(screen,NULL,white);
    drawBoard(board, 0, 0, 250, 500, screen);
    SDL_UpdateWindowSurface(window);

    while (SDL_PollEvent(&event)){

      if (event.type == SDL_QUIT){
        running = false;
        cout << "Goodbye" << endl;
        break;
      }

    }

    if((1000/60)>SDL_GetTicks() - startingTick){
      SDL_Delay(1000/60 - (SDL_GetTicks()-startingTick));

    }

 }

  SDL_DestroyWindow(window);

  SDL_Quit();
}
void drawBoard(int board[10][20], int x, int y, int w, int h, SDL_Surface* screen){
  Uint32 blue = SDL_MapRGB(screen->format,0,0,255);
  int width = w/10;
  int height = h/20;
  for(int i = 0; i<10; i++){
    for(int j = 0; j<20; j++){
      if (board[i][j] != 0){
	Sprite cell(blue,x+width*i,y+height*j,width,height);
	cell.draw(screen);
      }
    }
  }
}
