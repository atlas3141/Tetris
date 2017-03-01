#include "SDL.h"
#include "Sprite.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Tetronimo{

};
class block{

};

void drawBoard(int board[10][20], int x, int y, int w, int h);



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
  Uint32 startingTick;
  SDL_Event event;
  bool running = true;

  while (running == true){
    startingTick = SDL_GetTicks();
    SDL_FillRect(screen,NULL,white)
  }


}
