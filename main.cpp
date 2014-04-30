#include <iostream>
#include <cstdlib>
#include "SDL/SDL.h"

#include "game_loop.hpp"

#define SDL_FLAGS SDL_INIT_EVERYTHING
#define SDL_OGL_FLAGS SDL_OPENGL
#define SDL_WIDTH 1000
#define SDL_HEIGHT 800

using namespace std;

SDL_Surface *init_SDL() {
  const SDL_VideoInfo *vidInfo;
  int res;
  SDL_Surface *surface;

  res = SDL_Init(SDL_FLAGS);
  if (res == -1)
    return NULL;

  vidInfo = SDL_GetVideoInfo();
  if (vidInfo == NULL)
    return NULL;

  surface = SDL_SetVideoMode(SDL_WIDTH, SDL_HEIGHT,
                             vidInfo->vfmt->BitsPerPixel,
                             SDL_OGL_FLAGS);

  if (surface == NULL)
    return NULL;

  // SUCCESS
  return surface;
}

void destroy_SDL() {
  SDL_Quit();
}

int runGame() {
  int res;
  char const* err_msg = NULL;
  SDL_Surface *surface;
  GameLoop *gameloop;

  // Setup

  if (!(surface = init_SDL())) {
    cout << "Failed to initialize SDL. Exiting." << endl;
    return -1;
  }

  try {

    gameloop = new GameLoop(surface);

    res = gameloop->run_game_loop();

    if (res < 0)
      cout << "Game exiting with failure." << endl;

    delete gameloop;

  } catch (char const *msg) {
    err_msg = msg;
  }

  // Cleanup

  destroy_SDL();

  if (err_msg != NULL)
    throw err_msg;
  else
    return 0;
}

/* Top level just prints out any uncaught string error messages */
int main(int argc, char **argv) {
  try {
    return runGame();
  } catch (char const *msg) {
    cout << "Terminating after uncaught exception:\n> " << msg << endl;
    return -1;
  }
}