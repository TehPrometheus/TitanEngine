#pragma once
#include "Singleton.h"
#include "Controller.h"
#include <map>
#include <vector>
#include "Command.h"


namespace dae
{
	class Input final: public Singleton<Input>
	{
	public:
		void AddControllerCommand(unsigned int id, Controller::ControllerButton, Command* pCommand);

	private:
		using ControllerKey = std::pair<unsigned, Controller::ControllerButton>;
		using ControllerCommandsMap = std::map<ControllerKey, std::unique_ptr<Command>>;
		ControllerCommandsMap m_ControllerCommands{};
		std::vector<std::unique_ptr<Controller>> m_Controllers{};
	};

}

