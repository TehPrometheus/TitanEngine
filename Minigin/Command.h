#pragma once
class Command
{
public:
	Command() = default;
	virtual ~Command() = default;

	Command(Command const& other) = delete;
	Command(Command&& other) = delete;
	Command& operator=(Command const& rhs) = delete;
	Command& operator=(Command&& rhs) = delete;

	virtual void Execute() = 0;

};

