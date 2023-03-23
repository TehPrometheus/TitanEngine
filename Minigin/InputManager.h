#pragma once
#include "Singleton.h"

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager();
		InputManager(InputManager const& other) = delete;
		InputManager(InputManager&& other) = delete;
		InputManager& operator=(InputManager const& rhs) = delete;
		InputManager& operator=(InputManager&& rhs) = delete;

		~InputManager() override;

		bool ProcessInput();


	private:

		class InputManagerImpl;
		InputManagerImpl* m_pImpl{ nullptr };


	};

}
