#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 700

#define MAX_VELOCITY 1
#define MIN_SIZE 2
#define MAX_SIZE 5
#define MAX_STARS 1000

#define WHITE 0xedcee4
#define BLACK 0x000000

struct Star {
  double x;
  double y;
  double velocityX;
  double velocityY;
  double size;
};

void clearScreen(SDL_Surface *pSurface) {
  SDL_Rect background = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
  SDL_FillRect(pSurface, &background, BLACK);
}

void recreateStar(struct Star *star) {
  star->x = (double)SCREEN_WIDTH / 2;
  star->y = (double)SCREEN_HEIGHT / 2;

  star->velocityX = (double)rand() / RAND_MAX * 2 * MAX_VELOCITY - MAX_VELOCITY;
  star->velocityY = (double)rand() / RAND_MAX * 2 * MAX_VELOCITY - MAX_VELOCITY;

  star->size = MAX_SIZE;
  star->size = MAX_SIZE;
}

void moveStars(SDL_Surface *pSurface, struct Star *star) {

  if (star->x >= SCREEN_WIDTH || star->x < 0) {
    recreateStar(star);
  }

  if (star->y >= SCREEN_HEIGHT || star->y < 0) {
    recreateStar(star);
  }

  star->x += star->velocityX;
  star->y += star->velocityY;
  star->size += sqrt(pow(star->velocityX, 2) + pow(star->velocityY, 2)) / 75;

  SDL_Rect newStar = {star->x, star->y, star->size, star->size};
  SDL_FillRect(pSurface, &newStar, WHITE);
}

int main() {
  if (SDL_Init(SDL_INIT_VIDEO)) {
    fprintf(stderr, "SDL Init Failed: %s\n", SDL_GetError());
  }

  SDL_Window *pWindow = SDL_CreateWindow("Star Field", SDL_WINDOWPOS_CENTERED,
                                         SDL_WINDOWPOS_CENTERED, 900, 700, 0);

  if (!pWindow) {
    fprintf(stderr, "Failed to create Window");
  }

  SDL_Surface *pSurface = SDL_GetWindowSurface(pWindow);

  if (!pSurface) {
    fprintf(stderr, "Failed to get window surface");
  }

  struct Star stars[MAX_STARS];

  for (int i = 0; i < MAX_STARS; i++) {
    stars[i] = (struct Star){
        (double)SCREEN_WIDTH / 2, (double)SCREEN_HEIGHT / 2,
        (double)rand() / RAND_MAX * 2 * MAX_VELOCITY - MAX_VELOCITY,
        (double)rand() / RAND_MAX * 2 * MAX_VELOCITY - MAX_VELOCITY};
  }

  bool running = true;
  SDL_Event event;

  while (running) {
    while (SDL_PollEvent(&event) > 0) {
      if (event.type == SDL_QUIT) {
        running = false;
      }
    }

    clearScreen(pSurface);

    for (int i = 0; i < MAX_STARS; i++) {
      moveStars(pSurface, &stars[i]);
    }

    SDL_UpdateWindowSurface(pWindow);
    SDL_Delay(5);
  }
}
