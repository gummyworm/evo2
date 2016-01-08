#include <SDL2/SDL.h>
#include "debug.h"
#include "draw.h"
#include "engine.h"
#include "entity.h"
#include "input.h"

static bool run;

void tv_EngineQuit();

/* tv_EngineInit initializes the engine.  Call before running the engine. */
int tv_EngineInit()
{
  tv_DrawInit();
  CONNECT(Kill, tv_EngineQuit);
  return 0;
}

/* tv_EngineTick runs one "tick" of the engine by updating all the engine's
 * systems and updating all entities.
 */
void tv_EngineTick()
{
  if(run == false) {
    return;
  }
  tv_DrawStartFrame();
  tv_InputUpdate();
  /* TODO: update systems */
  tv_DrawEndFrame();
}

/* tv_EngineRun runs the engine until it is terminated. */
void tv_EngineRun()
{
  for(run = true; run;){
    tv_EngineTick();
  }
}

/* tv_EngineQuit halts execution of the engine's main loop. */
void tv_EngineQuit()
{
  debug_puts("kill signal detected- qutting...\n");
  run = false;
}

/* tv_EngineRunning returns true if the engine is currently running. */
bool tv_EngineRunning()
{
  return run;
}
