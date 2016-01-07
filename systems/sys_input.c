#include <SDL2/SDL.h>
#include "../components/enum.h"
#include "../sigslot.h"
#include "sys_input.h"

SIGDEF(ButtonDown)
SIGDEF(ButtonUp)
SIGDEF(MouseMove)

/* Implements returns true since all entities may use this system */
static bool Implements(struct tv_Entity *e)
{
  /* all entitie's "implement" this system (it's purely static) */
  return true;
}

/* Update polls for input and stores the input state for the current frame */
static void Update(struct tv_Entity *e)
{
  SDL_Event evt;
  while(SDL_PollEvent(&evt)){
    switch(evt.type){
    case SDL_QUIT:
      break;
    case SDL_KEYDOWN:
      EMIT(ButtonDown, evt.key.keysym.scancode);
      break;
    case SDL_KEYUP:
      EMIT(ButtonUp, evt.key.keysym.scancode);
      break;
    case SDL_MOUSEMOTION:
      EMIT(MouseMove, evt.motion.x, evt.motion.y);
      break;
    default:
      break;
    }
  }
}

/* NewInputSystem creates a new input system */
struct sys_Input * NewInputSystem()
{
  struct tv_System *sys;
  sys = malloc(sizeof(struct sys_Input));
  sys->Implements = Implements;
  sys->Update = Update;
  return (struct sys_Input*)sys;
}
