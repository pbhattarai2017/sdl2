#include <SDL.h>
#include <unistd.h>

int die()
{
  printf("%s\n", SDL_GetError());
  SDL_Quit();
  exit(EXIT_FAILURE);
}

int main()
{
  SDL_Window *window;
  
  SDL_Surface *imgSurface, *winSurface;

  SDL_Init(SDL_INIT_VIDEO) == 0 || die();
  window = SDL_CreateWindow("Hello World!",
                            10, 10,
                            800, 500,
                            SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
  window != NULL || die();
  /**
   * @brief load image into surface
   *
   */
  imgSurface = SDL_LoadBMP("./data/screenshot.bmp");
  imgSurface != NULL || die();

  /**
   * @brief blitting the image to window surface
   *
   */
  SDL_SetWindowSize(window, imgSurface->w, imgSurface->h);
  winSurface = SDL_GetWindowSurface(window);
  winSurface != NULL || die();
  // printf("%d %d\n",imgSurface->w, imgSurface->h);
  SDL_BlitSurface(imgSurface, NULL, winSurface, NULL);
  SDL_Event event;
  int shutdown = 0;
  while (shutdown == 0)
  {
    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
      case SDL_QUIT:
        shutdown = 1;
        printf("QUIT REQUESTED\n");
        break;
      case SDL_WINDOWEVENT:
        if (event.window.event == SDL_WINDOWEVENT_EXPOSED)
        {
          SDL_UpdateWindowSurface(window) == 0 || die();
        }
        else if (event.window.event == SDL_WINDOWEVENT_RESIZED)
        {
          winSurface = SDL_GetWindowSurface(window);
          winSurface != NULL || die();
          SDL_BlitSurface(imgSurface, NULL, winSurface, NULL);
          SDL_UpdateWindowSurface(window) == 0 || die();
        }
        break;
      }
    }
    SDL_Delay(20);
  }

  /**
   * @brief deallocate the resources
   *
   */
  SDL_FreeSurface(imgSurface);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
