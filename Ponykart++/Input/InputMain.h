#ifndef INPUTMAIN_H_INCLUDED
#define INPUTMAIN_H_INCLUDED

#include <vector>
#include <functional>
#include <SDL.h>
#include <OgreFrameListener.h>
#include "Kernel/LKernelObject.h"
#include "Input/ControllerManager.h"


//#define PRINTINPUT ///< uncomment if you want all input to be printed

namespace Ponykart
{
namespace Input
{

template<typename T> using LymphInputEvent1 = typename std::vector<std::function<void (const T &eventArgs)>>;
//template<typename T, typename U> using LymphInputEvent2 = typename std::vector<std::function<void (T eventArg1, U eventArg2)>>;

/// Class that handles all of the input.
/**This acts as a "layer" between the input library and the rest of the program.
// This makes it easier to change libraries and stuff, since you'd only need to change this class instead of everything
// that uses input.
//
// This class does not do anything with the input besides fire off more events.
//
// Other classes (mostly handlers) should only use events fired off from this class and not ones fired off from the
// input library.
**/
class InputMain : public LKernel::LKernelObject, public Ogre::FrameListener // TODO: Finish implementing InputMain
{
public:
	InputMain();
	// Getters
	const Input::ControllerManager* const getInputController();
	// Event handlers
	bool keyPressed(const SDL_KeyboardEvent &ke); ///< Handles key pressing and fires appropriate events
	bool keyReleased(const SDL_KeyboardEvent &ke); ///< Handles key releasing and fires appropriate events
	bool mousePressed(const SDL_MouseButtonEvent &mbe); ///< Handles mouse pressing and fires appropriate events
	bool mouseReleased(const SDL_MouseButtonEvent &mbe); ///< Handles mouse releasing and fires appropriate events
	bool mouseMoved(const SDL_MouseMotionEvent &mme); ///< Handles mouse movement and fires appropriate events
	bool mouseWheelMoved(const SDL_MouseWheelEvent &mwe); ///< Handles mouse movement and fires appropriate events

private:
	void createEventHandlers(); ///< Hook up to OIS's event handlers
	template<typename T> void fireEvent(LymphInputEvent1<T> handler, const T &eventArgs); ///< Fires an event. Helper method so we don't have to check every single event for null.
	//template<typename T, typename U> void fireEvent(LymphInputEvent2<T,U> handler, const T &eventArg1, const U &eventArg2); ///< Fires an event. Helper method so we don't have to check every single event for null.

private:
	bool frameStarted(const Ogre::FrameEvent& evt) override;

private:
	Input::ControllerManager* inputController;

public: // Events
	std::vector<std::function<void (const SDL_KeyboardEvent&)>> onKeyboardPress;
	std::vector<std::function<void (const SDL_KeyboardEvent&)>> onKeyboardRelease;

	std::vector<std::function<void (const SDL_MouseButtonEvent&)>> onMousePress;
	std::vector<std::function<void (const SDL_MouseButtonEvent&)>> onMouseRelease;
	std::vector<std::function<void (const SDL_MouseMotionEvent&)>> onMouseMove;
	std::vector<std::function<void (const SDL_MouseWheelEvent&)>> onMouseWheelMove;
};

} // Input
} // Ponykart
#endif // INPUTMAIN_H_INCLUDED
