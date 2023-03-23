#include "Input.h"

void dae::Input::AddControllerCommand(unsigned id, Controller::ControllerButton button, Command* pCommand)
{
	auto pair{ std::make_pair(id,button) };

	m_ControllerCommands.insert({ pair,std::unique_ptr<Command>(pCommand) });
}
