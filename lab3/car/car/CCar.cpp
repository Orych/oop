#include "CCar.h"
#include "common_libs.h"

bool CCar::TurnOnEngine()
{
	m_isEngineTurn = true;
	return m_isEngineTurn;
}

bool CCar::TurnOffEngine()
{
	if (m_gear == 0 && m_speed == 0)
	{
		m_isEngineTurn = false;
	}

	return !m_isEngineTurn;
}

bool CCar::SetSpeed(const int newSpeed)
{
	std::vector speedInterval = GetSpeedIntervalForGear(m_gear);
	int minSpeed = speedInterval[0];
	int maxSpeed = speedInterval[1];
	int absNewSpeed = abs(newSpeed);

	if (!m_isEngineTurn)
	{
		return false;
	}

	if (absNewSpeed == 0 && m_gear == 0)
	{
		m_needStop = false;
	}

	if (m_gear == 0 && absNewSpeed <= abs(m_speed))
	{
		m_speed = absNewSpeed;
		//SetDirection();
		return true;
	}

	if (m_gear != 0 && minSpeed <= absNewSpeed && absNewSpeed <= maxSpeed)
	{
		m_speed = (m_gear == -1) ? ((-1) * absNewSpeed) : absNewSpeed;
		SetDirection();
		return true;
	}

	return false;
}

bool CCar::SetGear(const int newGear)
{
	if (newGear < -1 || newGear > 5)
	{
		return false;
	}

	if (newGear == m_gear && newGear != -1)
	{
		return true;
	}

	if (newGear == -1 && newGear != m_gear)
	{
		if (m_speed == 0)
		{
			m_gear = newGear;
			return true;
		}

		return false;
	}

	if (m_gear == -1 && newGear == 0)
	{
		m_gear = newGear;
		m_needStop = m_speed != 0;
		return true;
	}

	if (m_gear == -1 && newGear == 1 && m_speed == 0)
	{
		m_gear = newGear;
		return true;
	}

	std::vector speedInterval = GetSpeedIntervalForGear(newGear);
	int minSpeed = speedInterval[0];
	int maxSpeed = speedInterval[1];

	if (m_gear != -1 && minSpeed <= m_speed && m_speed <= maxSpeed && !m_needStop)
	{
		m_gear = newGear;
		SetDirection();
		return true;
	}

	return false;
}

void CCar::SetDirection()
{
	if (m_speed > 0)
	{
		m_direction = CCar::Direction::FORWARD;
		return;
	}

	if (m_speed < 0)
	{
		m_direction = CCar::Direction::BACKWARD;
		return;
	}

	m_direction = CCar::Direction::ON_THE_SPOT;
	return;
}

bool CCar::IsEngineTurn() const
{
	return m_isEngineTurn;
}

int CCar::GetGear() const
{
	return m_gear;
}

int CCar::GetSpeed() const
{
	return abs(m_speed);
}

CCar::Direction CCar::GetDirection() const
{
	return m_direction;
}

CCar::SpeedIntervalForGears CCar::InitSpeedIntervalForGears() const
{
	SpeedIntervalForGears speedIntervalForGears;
	speedIntervalForGears[-1] = { 0, 20 };
	speedIntervalForGears[0] = { 0, 150 };
	speedIntervalForGears[1] = { 0, 30 };
	speedIntervalForGears[2] = { 20, 50 };
	speedIntervalForGears[3] = { 30, 60 };
	speedIntervalForGears[4] = { 40, 90 };
	speedIntervalForGears[5] = { 50, 150 };

	return speedIntervalForGears;
}

CCar::SpeedInterval CCar::GetSpeedIntervalForGear(const int gear) const
{
	return m_speedIntervalForGears.find(gear)->second;
}