#include <stdio.h>
#include <SDL.h>
#include <stdlib.h>

int max(int a, int b) {
	int g = a;
	if(b > g) g = b;
	return g;
}

int die() {
	printf("%s\n", SDL_GetError());
	SDL_Quit();
	exit(EXIT_FAILURE);
}

int main() {
	SDL_Window *window;

	SDL_Event event;

	int tick1, tick2;
	tick1 = 0;

	int quit = 0;

	uint32_t rmask, gmask, bmask, amask;

	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
	#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
	#endif

	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = 1;
	rect.h = 1;

	int r, g, b;
	r = 255; g = 0; b = 0;
	int x, y;
	x = 0; y = 0;

	SDL_Event redraw_event;
	redraw_event.type = SDL_USEREVENT;
	redraw_event.user.code = 2;
	redraw_event.user.data1 = NULL;
	redraw_event.user.data2 = NULL;

	SDL_Surface *surface, *wsurface;

	SDL_Init(SDL_INIT_VIDEO) == 0 || die();
	window = SDL_CreateWindow("Hello World!",
								10, 10,
								500, 500,
								SDL_WINDOW_SHOWN);
	window != NULL || die();

	surface = SDL_CreateRGBSurface(0,
									500,
									500,
									32,
									rmask, gmask, bmask, amask);
	surface != NULL || die();
	wsurface = SDL_GetWindowSurface(window);
	while(!quit) {
		while(SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_QUIT:
					quit = 1;
					break;
				case SDL_WINDOWEVENT:
					if(event.window.event == SDL_WINDOWEVENT_EXPOSED) {
						/* redraw the window */
						SDL_PushEvent(&redraw_event);
					}
					break;
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym) {
						case SDLK_UP:
							rect.y -= 2;
							break;
						case SDLK_DOWN:
							rect.y += 2;
							break;
						case SDLK_LEFT:
							rect.x -= 2;
							break;
						case SDLK_RIGHT:
							rect.x += 2;
							break;
					}
					SDL_PushEvent(&redraw_event);
					break;
				case SDL_USEREVENT:
					/* redraw the window */
					SDL_FillRect(surface, &rect, SDL_MapRGB(surface->format, r, g, b));
					SDL_BlitSurface(surface, NULL, wsurface, NULL);
					SDL_UpdateWindowSurface(window);
					printf("window redrawn!\n");
					break;
			}
		}
		SDL_Delay(20);
	}
	SDL_FreeSurface(surface);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
