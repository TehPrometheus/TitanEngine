#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <XInput.h>

#include <SDL.h>
#include "InputManager.h"

using namespace dae;

class InputManager::InputManagerImpl final
{
public:
	InputManagerImpl();
	InputManagerImpl(InputManager const& other) = delete;
	InputManagerImpl(InputManagerImpl&& other) = delete;
	InputManagerImpl& operator=(InputManagerImpl const& rhs) = delete;
	InputManagerImpl& operator=(InputManagerImpl&& rhs) = delete;
	~InputManagerImpl();

	bool ProcessInput();

private:
	Uint8 const* m_pKeyboardState;

	bool ProcessSDLInput();
	void ProcessKeyboardButtonDown(const SDL_Keycode& e);
};

InputManager::InputManagerImpl::InputManagerImpl()
{
}

InputManager::InputManagerImpl::~InputManagerImpl()
{
}

bool InputManager::InputManagerImpl::ProcessInput()
{


	return ProcessSDLInput();
}

bool InputManager::InputManagerImpl::ProcessSDLInput()
{
	SDL_Event e;
	m_pKeyboardState = SDL_GetKeyboardState(nullptr);
	if(m_pKeyboardState[SDL_SCANCODE_W])
	{
		std::cout << "w is held down\n";

	}
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT) {
			return true;
		}
		if (e.type == SDL_KEYDOWN) {
			ProcessKeyboardButtonDown(e.key.keysym.sym);
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {

		}
		// etc...
	}

	return false;
}

void InputManager::InputManagerImpl::ProcessKeyboardButtonDown(const SDL_Keycode& e)
{
	switch (e)
	{
	case SDLK_w:
		//std::cout << "w is held down\n";
	case SDLK_a:

	case SDLK_s:

	case SDLK_d:
		break;
	}
}


bool InputManager::ProcessInput()
{
	return m_pImpl->ProcessInput();
}

InputManager::InputManager()
	:Singleton<InputManager>(),
	m_pImpl{ new InputManagerImpl() }
{
}

InputManager::~InputManager()
{
	delete m_pImpl;
}

