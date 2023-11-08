#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../car/CCar.h"
#include "../car/CRemoteControl.h"
#include "../car/common_libs.h"

bool ExpectedModify(CCar& car, std::function<void(CCar& car)> method, const int expectedSpeed, const int expectedGear, const CCar::Direction& expectedDirection)
{
	method(car);

	return ((car.GetSpeed() == expectedSpeed) && (car.GetGear() == expectedGear) && (car.GetDirection() == expectedDirection));
}

bool ExpectValues(CCar& car, const int expectedSpeed, const int expectedGear, const CCar::Direction& expectedDirection)
{
	return ((car.GetSpeed() == expectedSpeed) && (car.GetGear() == expectedGear) && (car.GetDirection() == expectedDirection));
}

TEST_CASE("Initial information about the car")
{
	GIVEN("A car")
	{
		CCar car;

		WHEN("engine is off")
		{
			car.TurnOffEngine();

			THEN("gear, speed and direction are initial values")
			{
				REQUIRE(ExpectValues(car, 0, 0, CCar::Direction::ON_THE_SPOT));
				REQUIRE(!ExpectedModify(car, [](CCar& car) { car.SetSpeed(10); }, 10, 0, CCar::Direction::ON_THE_SPOT));
			}
		}

		WHEN("engine is on")
		{
			car.TurnOnEngine();

			THEN("gear, speed and direction are initial values")
			{
				REQUIRE(ExpectValues(car, 0, 0, CCar::Direction::ON_THE_SPOT));
			}
		}
	}
}

TEST_CASE("Unreachable values for gear")
{
	GIVEN("A car")
	{
		CCar car;

		WHEN("engine is on")
		{
			car.TurnOnEngine();

			THEN("gear can't get this values: (gear < -2) && (gear > 6)")
			{
				REQUIRE(ExpectValues(car, 0, 0, CCar::Direction::ON_THE_SPOT));
				REQUIRE(!ExpectedModify(car, [](CCar& car) { car.SetGear(-2); }, 0, -2, CCar::Direction::ON_THE_SPOT));
				REQUIRE(!ExpectedModify(car, [](CCar& car) { car.SetGear(6); }, 0, 6, CCar::Direction::ON_THE_SPOT));
			}
		}
	}
}

TEST_CASE("Unreachable values for speed(negative numbers)")
{
	GIVEN("A car")
	{
		CCar car;

		WHEN("engine is on and gear is 1")
		{
			car.TurnOnEngine();
			car.SetGear(1);

			THEN("speed can't get negative values")
			{
				REQUIRE(ExpectValues(car, 0, 1, CCar::Direction::ON_THE_SPOT));
				REQUIRE(!ExpectedModify(car, [](CCar& car) { car.SetSpeed(-1); }, -1, 1, CCar::Direction::ON_THE_SPOT));
				REQUIRE(!ExpectedModify(car, [](CCar& car) { car.SetSpeed(-500); }, -500, 1, CCar::Direction::ON_THE_SPOT));
			}
		}
	}
}

TEST_CASE("Test different action of car's behavior on gear 0")
{
	GIVEN("A car")
	{
		CCar car;

		WHEN("engine is on and gear is 0")
		{
			car.TurnOnEngine();

			THEN("impossible to increase speed value")
			{
				REQUIRE(ExpectValues(car, 0, 0, CCar::Direction::ON_THE_SPOT));
				REQUIRE(!ExpectedModify(car, [](CCar& car) { car.SetSpeed(12); }, 12, 0, CCar::Direction::ON_THE_SPOT));
			}

			THEN("speed can be change on the same value")
			{
				REQUIRE(ExpectedModify(car, [](CCar& car) { car.SetSpeed(0); }, 0, 0, CCar::Direction::ON_THE_SPOT));
			}
		}

		WHEN("engine is on and gear is -1")
		{
			car.TurnOnEngine();
			car.SetGear(-1);

			THEN("value of direction must not changed")
			{
				REQUIRE(ExpectValues(car, 0, -1, CCar::Direction::ON_THE_SPOT));
			}
		}

		WHEN("engine is on and gear is 1")
		{
			car.TurnOnEngine();
			car.SetGear(1);

			THEN("car can increase speed and change direction on FORWARD")
			{
				REQUIRE(ExpectValues(car, 0, 1, CCar::Direction::ON_THE_SPOT));
				REQUIRE(ExpectedModify(car, [](CCar& car) { car.SetSpeed(12); }, 12, 1, CCar::Direction::FORWARD));

			}
		}

		WHEN("engine is on, gear is 0 and speed 12")
		{
			car.TurnOnEngine();
			car.SetGear(1);
			car.SetSpeed(12);
			car.SetGear(0);

			THEN("car can only decrease speed, or change on the same value")
			{
				REQUIRE(ExpectValues(car, 12, 0, CCar::Direction::FORWARD));
				REQUIRE(!ExpectedModify(car, [](CCar& car) { car.SetSpeed(13); }, 13, 0, CCar::Direction::FORWARD));
				REQUIRE(ExpectedModify(car, [](CCar& car) { car.SetSpeed(10); }, 10, 0, CCar::Direction::FORWARD));

			}
		}
	}
}

TEST_CASE("Test car on gear -1")
{
	GIVEN("A car")
	{
		CCar car;

		WHEN("engine is on, gear is -1, speed 0")
		{
			car.TurnOnEngine();
			car.SetGear(-1);

			THEN("speed and direction are initial values")
			{
				REQUIRE(ExpectValues(car, 0, -1, CCar::Direction::ON_THE_SPOT));
			}

			THEN("speed can't be more than 20")
			{
				REQUIRE(!ExpectedModify(car, [](CCar& car) { car.SetSpeed(21); }, 21, -1, CCar::Direction::BACKWARD));
			}

			THEN("if speed more than 0, direction have to be BACKWARD")
			{
				REQUIRE(ExpectedModify(car, [](CCar& car) { car.SetSpeed(12); }, 12, -1, CCar::Direction::BACKWARD));
			}

			THEN("car can't switch gear on the same(-1)")
			{
				REQUIRE(!ExpectedModify(car, [](CCar& car) { car.SetGear(-1); }, 12, -1, CCar::Direction::BACKWARD));
			}
		}

		WHEN("engine is on, gear is -1, speed 20")
		{
			car.TurnOnEngine();
			car.SetGear(-1);
			car.SetSpeed(20);

			THEN("car cant change gear on 1")
			{
				REQUIRE(ExpectValues(car, 20, -1, CCar::Direction::BACKWARD));
				REQUIRE(!ExpectedModify(car, [](CCar& car) { car.SetGear(1); }, 20, 1, CCar::Direction::BACKWARD));
			}
		}

		WHEN("engine is on, gear is -1, speed 20")
		{
			car.TurnOnEngine();
			car.SetGear(-1);
			car.SetSpeed(20);

			THEN("car change gear on 0, but cant change on 1 after, if speed > 0")
			{
				REQUIRE(ExpectValues(car, 20, -1, CCar::Direction::BACKWARD));
				REQUIRE(ExpectedModify(car, [](CCar& car) { car.SetGear(0); }, 20, 0, CCar::Direction::BACKWARD));
				REQUIRE(!ExpectedModify(car, [](CCar& car) { car.SetGear(1); }, 20, 1, CCar::Direction::FORWARD));
			}

			THEN("change on 1 after stopping")
			{
				REQUIRE(ExpectValues(car, 20, -1, CCar::Direction::BACKWARD));
				REQUIRE(ExpectedModify(car, [](CCar& car) { car.SetSpeed(0); }, 0, -1, CCar::Direction::ON_THE_SPOT));
				REQUIRE(!ExpectedModify(car, [](CCar& car) { car.SetGear(1); }, 0, 1, CCar::Direction::FORWARD));
			}

			THEN("after switching to 0 gear and decrease speed, direction have not be changed")
			{
				REQUIRE(ExpectValues(car, 20, -1, CCar::Direction::BACKWARD));
				REQUIRE(ExpectedModify(car, [](CCar& car) { car.SetGear(0); }, 20, 0, CCar::Direction::BACKWARD));
				REQUIRE(ExpectedModify(car, [](CCar& car) { car.SetSpeed(15); }, 15, 0, CCar::Direction::BACKWARD));
			}
		}
	}
}

TEST_CASE("car on gear upper than 1")
{
	GIVEN("A car")
	{
		CCar car;

		WHEN("engine is on, gear is 1, speed 0")
		{
			car.TurnOnEngine();
			car.SetGear(1);

			THEN("max speed is 30, min - 0")
			{
				REQUIRE(ExpectValues(car, 0, 1, CCar::Direction::ON_THE_SPOT));
				REQUIRE(!ExpectedModify(car, [](CCar& car) { car.SetSpeed(31); }, 31, 1, CCar::Direction::FORWARD));
				REQUIRE(ExpectedModify(car, [](CCar& car) { car.SetSpeed(30); }, 30, 1, CCar::Direction::FORWARD));
				REQUIRE(ExpectedModify(car, [](CCar& car) { car.SetSpeed(0); }, 0, 1, CCar::Direction::ON_THE_SPOT));
			}
		}

		WHEN("engine is on, gear is 2, speed 20")
		{
			car.TurnOnEngine();
			car.SetGear(1);
			car.SetSpeed(20);
			car.SetGear(2);

			THEN("max speed is 50, min - 20")
			{
				REQUIRE(ExpectValues(car, 20, 2, CCar::Direction::FORWARD));
				REQUIRE(!ExpectedModify(car, [](CCar& car) { car.SetSpeed(19); }, 19, 2, CCar::Direction::FORWARD));
				REQUIRE(!ExpectedModify(car, [](CCar& car) { car.SetSpeed(51); }, 51, 2, CCar::Direction::FORWARD));
				REQUIRE(ExpectedModify(car, [](CCar& car) { car.SetSpeed(50); }, 50, 2, CCar::Direction::FORWARD));
			}
		}

		WHEN("engine is on, gear is 3, speed 30")
		{
			car.TurnOnEngine();
			car.SetGear(1);
			car.SetSpeed(20);
			car.SetGear(2);
			car.SetSpeed(30);
			car.SetGear(3);

			THEN("max speed is 60, min - 30")
			{
				REQUIRE(ExpectValues(car, 30, 3, CCar::Direction::FORWARD));
				REQUIRE(!ExpectedModify(car, [](CCar& car) { car.SetSpeed(29); }, 29, 3, CCar::Direction::FORWARD));
				REQUIRE(!ExpectedModify(car, [](CCar& car) { car.SetSpeed(61); }, 61, 3, CCar::Direction::FORWARD));
				REQUIRE(ExpectedModify(car, [](CCar& car) { car.SetSpeed(60); }, 60, 3, CCar::Direction::FORWARD));
			}
		}

		WHEN("engine is on, gear is 4, speed 40")
		{
			car.TurnOnEngine();
			car.SetGear(1);
			car.SetSpeed(20);
			car.SetGear(2);
			car.SetSpeed(30);
			car.SetGear(3);
			car.SetSpeed(40);
			car.SetGear(4);

			THEN("max speed is 90, min - 40")
			{
				REQUIRE(ExpectValues(car, 40, 4, CCar::Direction::FORWARD));
				REQUIRE(!ExpectedModify(car, [](CCar& car) { car.SetSpeed(39); }, 39, 4, CCar::Direction::FORWARD));
				REQUIRE(!ExpectedModify(car, [](CCar& car) { car.SetSpeed(91); }, 91, 4, CCar::Direction::FORWARD));
				REQUIRE(ExpectedModify(car, [](CCar& car) { car.SetSpeed(90); }, 90, 4, CCar::Direction::FORWARD));
			}
		}

		WHEN("engine is on, gear is 5, speed 50")
		{
			car.TurnOnEngine();
			car.SetGear(1);
			car.SetSpeed(20);
			car.SetGear(2);
			car.SetSpeed(30);
			car.SetGear(3);
			car.SetSpeed(40);
			car.SetGear(4);
			car.SetSpeed(50);
			car.SetGear(5);

			THEN("max speed is 150, min - 50")
			{
				REQUIRE(ExpectValues(car, 50, 5, CCar::Direction::FORWARD));
				REQUIRE(!ExpectedModify(car, [](CCar& car) { car.SetSpeed(49); }, 49, 5, CCar::Direction::FORWARD));
				REQUIRE(!ExpectedModify(car, [](CCar& car) { car.SetSpeed(151); }, 151, 5, CCar::Direction::FORWARD));
				REQUIRE(ExpectedModify(car, [](CCar& car) { car.SetSpeed(150); }, 150, 5, CCar::Direction::FORWARD));
				REQUIRE(!ExpectedModify(car, [](CCar& car) { car.SetSpeed(-10); }, -10, 5, CCar::Direction::BACKWARD));
			}
		}

		WHEN("engine is on, gear is 5, speed 50")
		{
			car.TurnOnEngine();
			car.SetGear(1);
			car.SetSpeed(20);
			car.SetGear(2);
			car.SetSpeed(30);
			car.SetGear(3);
			car.SetSpeed(40);
			car.SetGear(4);
			car.SetSpeed(50);
			car.SetGear(5);

			THEN("car can't change gaer on -1 and 1")
			{
				REQUIRE(ExpectValues(car, 50, 5, CCar::Direction::FORWARD));
				REQUIRE(!ExpectedModify(car, [](CCar& car) { car.SetGear(1); }, 50, 1, CCar::Direction::FORWARD));
				REQUIRE(!ExpectedModify(car, [](CCar& car) { car.SetGear(-1); }, 50, -1, CCar::Direction::BACKWARD));
			}

			THEN("car can change gaer on 0")
			{
				REQUIRE(ExpectedModify(car, [](CCar& car) { car.SetGear(0); }, 50, 0, CCar::Direction::FORWARD));
			}

			THEN("car can change gaer on 2")
			{
				REQUIRE(ExpectedModify(car, [](CCar& car) { car.SetGear(2); }, 50, 2, CCar::Direction::FORWARD));
			}

			THEN("car can change gaer on 3")
			{
				REQUIRE(ExpectedModify(car, [](CCar& car) { car.SetGear(3); }, 50, 3, CCar::Direction::FORWARD));
			}

			THEN("car can change gaer on 4")
			{
				REQUIRE(ExpectedModify(car, [](CCar& car) { car.SetGear(4); }, 50, 4, CCar::Direction::FORWARD));
			}

			THEN("car can change gaer on 5")
			{
				REQUIRE(ExpectedModify(car, [](CCar& car) { car.SetGear(5); }, 50, 5, CCar::Direction::FORWARD));
			}
		}
	}
}

TEST_CASE("Test car's remote controller")
{
	CCar car;

	SECTION("Command <Info>")
	{
		std::istringstream iss("Info");
		std::ostringstream oss;

		CRemoteControl remoteController(car, iss, oss);
		remoteController.HandleCommand();

		REQUIRE(oss.str() == "Engine is: off\nSpeed: 0\nGear: 0\nDirection: on the spot\n");
	}

	SECTION("Test car's remote controller. Command <EngineOn>")
	{
		std::istringstream iss("EngineOn\nEngineOn");
		std::ostringstream oss;

		CRemoteControl remoteController(car, iss, oss);
		remoteController.HandleCommand();
		REQUIRE(oss.str() == "Engine is turn on\n");

		remoteController.HandleCommand();
		REQUIRE(oss.str() == "Engine is turn on\nEngine is turn on\n");
	}

	SECTION("Test car's remote controller. Command <EngineOff>")
	{
		std::istringstream iss("EngineOff\nEngineOff");
		std::ostringstream oss;

		CRemoteControl remoteController(car, iss, oss);
		remoteController.HandleCommand();

		REQUIRE(oss.str() == "Engine is turn off\n");

		remoteController.HandleCommand();
		REQUIRE(oss.str() == "Engine is turn off\nEngine is turn off\n");
	}

	SECTION("Test car's remote controller. Command <SetGear>")
	{
		std::istringstream iss("SetGear -1\nSetGear 2");
		std::ostringstream oss;

		CRemoteControl remoteController(car, iss, oss);
		remoteController.HandleCommand();

		REQUIRE(oss.str() == "Set gear -1 succeed\n");
		remoteController.HandleCommand();

		REQUIRE(oss.str() == "Set gear -1 succeed\nThere is some problems with setting new gear\n");
	}

	SECTION("Test car's remote controller. Command <SetSpeed>")
	{
		std::istringstream iss("EngineOn\nSetGear 1\nSetSpeed 31\nSetSpeed 21");
		std::ostringstream oss;

		CRemoteControl remoteController(car, iss, oss);
		remoteController.HandleCommand();
		REQUIRE(oss.str() == "Engine is turn on\n");

		remoteController.HandleCommand();
		REQUIRE(oss.str() == "Engine is turn on\nSet gear 1 succeed\n");

		remoteController.HandleCommand();
		REQUIRE(oss.str() == "Engine is turn on\nSet gear 1 succeed\nThere is some problems with setting new speed\n");

		remoteController.HandleCommand();
		REQUIRE(oss.str() == "Engine is turn on\nSet gear 1 succeed\nThere is some problems with setting new speed\nSet speed 21 succeed\n");
	}

	SECTION("Test car's remote controller. Command <IncomprehensibleNonsense>")
	{
		std::istringstream iss("IncomprehensibleNonsense");
		std::ostringstream oss;

		CRemoteControl remoteController(car, iss, oss);
		remoteController.HandleCommand();

		REQUIRE(oss.str() == "");
	}
}