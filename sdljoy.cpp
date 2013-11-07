#include "SDL.h"

#include <stdio.h>
#include <stdlib.h>

void list_joysticks()
{
  for (int i=0; i<SDL_NumJoysticks(); i++) {
    SDL_Joystick* joy = SDL_JoystickOpen(i);
    if (joy) {
      printf("Joystick %i\n", i);
      printf("Name: %s\n", SDL_JoystickName(i));
      printf("Number of Axes: %d\n", SDL_JoystickNumAxes(joy));
      printf("Number of Buttons: %d\n", SDL_JoystickNumButtons(joy));
      printf("Number of Balls: %d\n", SDL_JoystickNumBalls(joy));
      //SDL_JoystickClose(joy);
    }
  }
}

int main(int argc, char** argv)
{
  // We need to initialize video, otherwise we won't receive joystick events. :(
  // http://stackoverflow.com/questions/4890852/using-sdl-init-joystick-without-sdl-init-video
  if (SDL_Init(SDL_INIT_JOYSTICK | SDL_INIT_VIDEO) < 0 ) {
    fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
    return 1;
  }
  atexit(SDL_Quit);

  list_joysticks();
  SDL_JoystickEventState(SDL_ENABLE);

  SDL_Event event;
  while (1) {
    while(SDL_PollEvent(&event)) {
      switch(event.type) {
      case SDL_JOYAXISMOTION:
        printf("Joystick %d axis %d value %d\n",
               event.jaxis.which, event.jaxis.axis, event.jaxis.value);
        break;
      case SDL_JOYBUTTONDOWN:
      case SDL_JOYBUTTONUP:
        printf("Joystick %d button %d %s\n",
               event.jbutton.which, event.jbutton.button,
               event.jbutton.state == SDL_PRESSED ?
               "pressed" : "released");
        break;
        /*
          case SDL_JOYDEVICEADDED:
          case SDL_JOYDEVICEREMOVED:
          printf("Joystick %s\n",
          event.type == SDL_JOYDEVICEADDED ? "added" : "removed");
          break;
        */
      }
    }
    SDL_Delay(50);
  }

  return 0;
}
