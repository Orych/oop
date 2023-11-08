#include "CCar.h"
#include "CRemoteControl.h"
#include "common_libs.h"

int main()
{
	CCar car;
	CRemoteControl remoteController(car, std::cin, std::cout);
	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << "> ";
		if (!remoteController.HandleCommand())
		{
			std::cout << "Unknown command!" << std::endl;
		}
	}

	return 0;
}