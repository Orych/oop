#pragma once
#include "CCar.h"
#include "common_libs.h"

class CRemoteControl
{
public:
	CRemoteControl(CCar& car, std::istream& input, std::ostream& output);
	bool HandleCommand();

private:
	bool EngineOn(const int args);
	bool EngineOff(const int args);
	bool SetGear(const int args);
	bool SetSpeed(const int args);
	bool Info(const int args) const;
	bool Help(const int args) const;

private:
	using Handler = std::function<bool(int args)>;

	using ActionMap = std::map<std::string, Handler>;

	CCar& m_car;
	std::istream& m_input;
	std::ostream& m_output;

	const ActionMap m_actionMap;
};