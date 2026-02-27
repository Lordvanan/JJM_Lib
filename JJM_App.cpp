#include "JJM_App.h"
#include <cstring>

void JJM_Log(const char* message, ...)
{
	va_list args;
	va_start(args, message);
	vprintf(message, args);
	va_end(args);
}

void JJM_Log(const char* color, const char* message, ...)
{
	cout << color;
	va_list args;
	va_start(args, message);
	vprintf(message, args);
	va_end(args);
	cout << WHITE_T;
}

void JJM_Log(Color color, const char* message, ...)
{
	cout << __get_enum_color(color);
	va_list args;
	va_start(args, message);
	vprintf(message, args);
	va_end(args);
	cout << WHITE_T;
}

void JJM_Log(string message, ...)
{
	va_list args;
	va_start(args, message);
	vprintf(message.c_str(), args);
	va_end(args);
}

void JJM_Log(const char* color, string message, ...)
{
	cout << color;
	va_list args;
	va_start(args, message);
	vprintf(message.c_str(), args);
	va_end(args);
	cout << WHITE_T;
}

void JJM_Log(Color color, string message, ...)
{
	cout << __get_enum_color(color);
	va_list args;
	va_start(args, message);
	vprintf(message.c_str(), args);
	va_end(args);
	cout << WHITE_T;
}

const char* __get_enum_color(Color color)
{
	switch (color)
	{
	case Color::BLACK: return BLACK_T;
	case Color::RED: return RED_T;
	case Color::GREEN: return GREEN_T;
	case Color::YELLOW: return YELLOW_T;
	case Color::BLUE: return BLUE_T;
	case Color::MAGENTA: return MAGENTA_T;
	case Color::CYAN: return CYAN_T;
	case Color::WHITE: return WHITE_T;
	case Color::BRIGHT_BLACK: return BRIGHT_BLACK_T;
	case Color::BRIGHT_RED: return BRIGHT_RED_T;
	case Color::BRIGHT_GREEN: return BRIGHT_GREEN_T;
	case Color::BRIGHT_YELLOW: return BRIGHT_YELLOW_T;
	case Color::BRIGHT_BLUE: return BRIGHT_BLUE_T;
	case Color::BRIGHT_MAGENTA: return BRIGHT_MAGENTA_T;
	case Color::BRIGHT_CYAN: return BRIGHT_CYAN_T;
	case Color::BRIGHT_WHITE: return BRIGHT_WHITE_T;
	default: return WHITE_T;
	}
}

void __handle_invalid_selection()
{
	cin.clear();
	cin.ignore(numeric_limits<streamsize>().max(), '\n');
	cout << "Invalid input!\n";
}

JJM_Menu::JJM_Menu(string title, initializer_list<string> menuItems)
	: JJM_Menu(0, title, menuItems) {
}

JJM_Menu::JJM_Menu(int column, string title, initializer_list<string> menuItems)
	: colSep{ column }, title{ title }, menuSize{ menuItems.size() }, multiColumn{ false }
{
	if (colSep != 0)
	{
		multiColumn = true;
	}

	items = new string[menuSize];
	for (size_t i{ 0 }; i < menuSize; i++)
	{
		items[i] = *(menuItems.begin() + i);
	}
}

JJM_Menu::~JJM_Menu()
{
	delete[] items;
}

void JJM_Menu::Display() const
{
	int itemNum{ 0 };
	cout << title << "\n\n";

	if (multiColumn)
	{
		for (size_t i{ 0 }; i < menuSize; i++)
		{
			itemNum = i + 1;
			if (i % 2 == 0)
			{
				cout << itemNum << ") " << setw(colSep) << left << items[i];
				if (i == menuSize - 1)
				{
					cout << '\n';
				}
			}
			else
			{
				cout << itemNum << ") " << items[i] << '\n';
			}
		}
	}
	else
	{
		for (size_t i{ 0 }; i < menuSize; i++)
		{
			itemNum = i + 1;
			cout << itemNum << ") " << items[i] << '\n';
		}
	}
}

int JJM_Menu::Select()
{
	int selection;

	while (true)
	{
		cin >> selection;

		if (selection <= 0 || selection > menuSize)
		{
			__handle_invalid_selection();
			continue;
		}

		return selection - 1;
	}
}

int JJM_Menu::Size()
{
	return static_cast<int>(menuSize);
}

void JJM_Rand::SetSeed()
{
	time_t seed{ time(nullptr) };
	srand(seed);
}

int JJM_Rand::RangeEx(int min, int max)
{
	return (rand() % (max - min)) + min;
}

int JJM_Rand::RangeIn(int min, int max)
{
	return (rand() % ((max + 1) - min)) + min;
}

float JJM_Rand::Rangef(float min, float max)
{
	float normal = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	return (normal * (max - min)) + min;
}