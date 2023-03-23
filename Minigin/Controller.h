#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <XInput.h>

namespace dae
{
	
	class Controller final
	{
	public:
		enum class ControllerButton: WORD
		{
			ButtonA			= XINPUT_GAMEPAD_A,
			ButtonB			= XINPUT_GAMEPAD_B,
			ButtonX			= XINPUT_GAMEPAD_X,
			ButtonY			= XINPUT_GAMEPAD_Y,
			ButtonUp		= XINPUT_GAMEPAD_DPAD_UP,
			ButtonLeft		= XINPUT_GAMEPAD_DPAD_LEFT,
			ButtonDown		= XINPUT_GAMEPAD_DPAD_DOWN,
			ButtonRight		= XINPUT_GAMEPAD_DPAD_RIGHT,
			LeftThumb		= XINPUT_GAMEPAD_LEFT_THUMB,
			RightThumb		= XINPUT_GAMEPAD_RIGHT_THUMB,
			LeftShoulder	= XINPUT_GAMEPAD_LEFT_SHOULDER,
			RightShoulder	= XINPUT_GAMEPAD_RIGHT_SHOULDER,
			Back			= XINPUT_GAMEPAD_BACK,
			Start			= XINPUT_GAMEPAD_START,
			None = 65535
		};

		void Update();


		bool IsDown(ControllerButton button) const;
		bool IsUp(ControllerButton button) const;
		bool IsPressed(ControllerButton button) const;

		explicit Controller(int controllerIndex);
		~Controller();

	private:
		class ControllerImpl;
		ControllerImpl* m_pImpl{};

	};
}
