#include "utils.h"

Menu mainMenu(16, Color::BRIGHT_WHITE, "Main Menu",
{
	"Random Numbers",
	"Quit"
});

Menu randMenu(0, Color::BRIGHT_GREEN, "Random Numbers",
{
	"Generate exclusive int",
	"Generate inclusive int",
	"Generate float",
	"Back"
});

Menu generateMenu("",
{
	"Change range",
	"Generate",
	"Back"
});

void GenerateRandomNumbers()
{
	CLEAR;
	bool goBack{ false };
	int iMin = 0, iMax = 100;
	float fMin = 0.0, fMax = 1.0;
	while (!goBack)
	{
		randMenu.Display();
		switch (randMenu.Select())
		{
		case 0: CLEAR;
			generateMenu.Display();
			switch (generateMenu.Select())
			{
			case 0: CLEAR;

			case 1:
			case 2:
			}

		case 1: CLEAR;
			Print("Number: %d\n", Rand::RangeEx((int)min, (int)max)); break;
		case 2: CLEAR;
			Print("Number: %d\n", Rand::RangeIn((int)min, (int)max)); break;
		case 3: CLEAR;
			Print("Number: %f\n", Rand::Rangef(min, max)); break;
		case 4: CLEAR; goBack = true;
		}
	}
}