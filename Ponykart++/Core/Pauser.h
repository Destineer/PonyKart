#ifndef PAUSER_H_INCLUDED
#define PAUSER_H_INCLUDED

#include <vector>
#include <functional>
#include <SDL.h>
#include "Kernel/LKernelObject.h"
#include "Misc/eventExtensions.h"

namespace Ponykart
{
namespace Core
{
enum PausingState
{
	Pausing,
	Unpausing
};

class Pauser : public LKernel::LKernelObject
{
public:
	Pauser();
	static void keyInvokePauseEvent(const SDL_KeyboardEvent &ke); ///< Checks to make sure the key pressed matches the pause key (`) then checks to make sure we aren't on the main menu
	static void invokePauseEvent(); ///< Checks to make sure we aren't on the main menu (don't want to unpause that!). This is a separate method so we can call it from e.g. Lua.
	static void pauseWithEvent(); ///< Use this to pause things but it also fires off a pause event, which may cause other things to happen that you don't want.

public:
	/// Setting this to true will pause the spawner, physics engine, level changer, movement managers, etc.
	/** It won't pause animations, UI, scripts, cameras, and so on.
	// I think most things will be fine with just a boolean. */
	static bool isPaused;
	/// An event for things that need it
	static Extensions::EventDelegate<PausingState> pauseEvent;
};

} // Core
} // Ponykart

#endif // PAUSER_H_INCLUDED
