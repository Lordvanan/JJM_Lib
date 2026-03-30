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

void GenerateRandomNumbers()
{
	Clear();
	bool goBack{ false };
	while (!goBack)
	{
		randMenu.Display();
		switch (randMenu.Select())
		{
		case 0: Clear();
			Print("Range[0-100]: %d\n", Rand::RangeEx(0, 100)); break;
		case 1: Clear();
			Print("Range[0-100]: %d\n", Rand::RangeIn(0, 100)); break;
		case 2: Clear();
			Print("Range[0.0-1.0]: %f\n", Rand::Rangef(0.0, 1.0)); break;
		case 3: Clear(); goBack = true;
		}
	}
}