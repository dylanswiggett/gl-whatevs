#include <iostream>
#include <cstdlib>
#include "SDL2/SDL.h"
// #include "SDL/SDL_opengl.h"

#include "game_loop.hpp"

#define SDL_FLAGS SDL_INIT_EVERYTHING
#define SDL_OGL_FLAGS SDL_WINDOW_OPENGL
#define SDL_WIDTH 1000
#define SDL_HEIGHT 800

using namespace std;

SDL_Window *init_SDL() {
  // const SDL_VideoInfo *vidInfo;
  int res;
  SDL_Window *window;

  res = SDL_Init(SDL_FLAGS);
  if (res == -1)
    return NULL;

  window = SDL_CreateWindow(
    "GL Whatnot", 0, 0, SDL_WIDTH, SDL_HEIGHT,
    SDL_OGL_FLAGS);

  // vidInfo = SDL_GetVideoInfo();
  // if (vidInfo == NULL)
  //   return NULL;

  // res = 0;
  // res |= SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  // res |= SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  // res |= SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  // res |= SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  // res |= SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  // res |= SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
  // if (res != 0)
  //   return NULL;

  // window = SDL_SetVideoMode(SDL_WIDTH, SDL_HEIGHT,
  //                            vidInfo->vfmt->BitsPerPixel,
  //                            SDL_OGL_FLAGS);

  // if (window == NULL)
  //   return NULL;

  // SUCCESS
  return window;
}

void destroy_SDL() {
  SDL_Quit();
}

SDL_GLContext init_GL(SDL_Window *window) {
  return SDL_GL_CreateContext(window);
}

void destroy_GL(SDL_GLContext context) {
  SDL_GL_DeleteContext(context);
}

int runGame() {
  int res;
  char const* err_msg = NULL;
  SDL_Window *window;
  SDL_GLContext glcontext;
  GameLoop *gameloop;

  // Setup

  if (!(window = init_SDL())) {
    cout << "Failed to initialize SDL. Exiting." << endl;
    return -1;
  }

  if (!(glcontext = init_GL(window))) {
    cout << "Failed to initialize openGL. Exiting." << endl;
    destroy_SDL();
    return -1;
  }

  try {

    gameloop = new GameLoop(window);

    res = gameloop->run_game_loop();

    if (res < 0)
      cout << "Game exiting with failure." << endl;

    delete gameloop;

  } catch (char const *msg) {
    err_msg = msg;
  }

  // Cleanup

  destroy_GL(glcontext);
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