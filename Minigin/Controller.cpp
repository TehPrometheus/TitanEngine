#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <XInput.h>

#include "Controller.h"

using namespace dae;



class Controller::ControllerImpl final
{
public:
	ControllerImpl(int controllerIndex);
	ControllerImpl(ControllerImpl const& other) = delete;
	ControllerImpl(ControllerImpl&& other) = delete;
	ControllerImpl& operator=(ControllerImpl const& rhs) = delete;
	ControllerImpl& operator=(ControllerImpl&& rhs) = delete;

	~ControllerImpl() = default;

	void Update();

	bool IsDownThisFrame(WORD button);
	bool IsUpThisFrame(WORD button);
	bool IsPressed(WORD button);



private:
	int m_ControllerIndex{};

	XINPUT_STATE m_PreviousState{};
	XINPUT_STATE m_CurrentState{};

	WORD m_ButtonsPressedThisFrame{};
	WORD m_ButtonsReleasedThisFrame{};

};


Controller::ControllerImpl::ControllerImpl(int controllerIndex)
	:m_ControllerIndex(controllerIndex)
{
	ZeroMemory(&m_PreviousState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
}

void Controller::ControllerImpl::Update()
{
	CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(m_ControllerIndex, &m_CurrentState);

	auto buttonChanges{ m_CurrentState.Gamepad.wButtons xor m_PreviousState.Gamepad.wButtons };
	m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
	m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
}

bool Controller::ControllerImpl::IsDownThisFrame(WORD button)
{
	return m_ButtonsPressedThisFrame & button;
}

bool Controller::ControllerImpl::IsUpThisFrame(WORD button)
{
	return m_ButtonsReleasedThisFrame & button;
}

bool Controller::ControllerImpl::IsPressed(WORD button)
{
	return m_CurrentState.Gamepad.wButtons & button;
}



















void Controller::Update()
{
	m_pImpl->Update();
}

bool Controller::IsDown(ControllerButton button) const
{
	return m_pImpl->IsDownThisFrame(static_cast<WORD>(button));
}

bool Controller::IsUp(ControllerButton button) const
{
	return m_pImpl->IsUpThisFrame(static_cast<WORD>(button));
}

bool Controller::IsPressed(ControllerButton button) const
{
	return m_pImpl->IsPressed(static_cast<WORD>(button));
}

Controller::Controller(int controllerIndex)
	:m_pImpl(new ControllerImpl(controllerIndex))
{
}

Controller::~Controller()
{
	delete m_pImpl;
}

