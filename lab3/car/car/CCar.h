#pragma once
#include "common_libs.h"

class CCar
{
public:
	enum class Direction
	{
		FORWARD,
		BACKWARD,
		ON_THE_SPOT,
	};
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(const int newGear);
	bool SetSpeed(const int newSpeed);

	bool IsEngineTurn() const;
	int GetGear() const;
	int GetSpeed() const;
	Direction GetDirection() const;

private:
	void SetDirection();

private:
	using SpeedInterval = std::vector<int>;
	using SpeedIntervalForGears = std::map<int, SpeedInterval>;
	SpeedInterval GetSpeedIntervalForGear(const int gear) const;
	SpeedIntervalForGears InitSpeedIntervalForGears() const;

	Direction m_direction = Direction::ON_THE_SPOT;
	SpeedIntervalForGears m_speedIntervalForGears = InitSpeedIntervalForGears();

	bool m_isEngineTurn = false;
	int m_speed = 0;
	int m_gear = 0;
	bool m_needStop = false;
};