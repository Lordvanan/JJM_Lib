#include "JJM_App.h"
#include <cstring>
#include <limits>

void JJM::Clear()
{
	#ifdef WINDOWS
		system("cls");
	#else
		system("clear");
	#endif
}

void JJM::AwaitEnter(bool clear)
{
	cout << "Press Enter to continue...";
	cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
	if (clear) Clear();
}

void JJM::Print(const char* message, ...)
{
	va_list args;
	va_start(args, message);
	vprintf(message, args);
	va_end(args);
}

void JJM::Print(Color color, const char* message, ...)
{
	cout << JJM::__get_enum_color(color);
	va_list args;
	va_start(args, message);
	vprintf(message, args);
	va_end(args);
	cout << WHITE_T;
}

void JJM::Print(string message, ...)
{
	va_list args;
	va_start(args, message);
	vprintf(message.c_str(), args);
	va_end(args);
}

void JJM::Print(Color color, string message, ...)
{
	cout << JJM::__get_enum_color(color);
	va_list args;
	va_start(args, message);
	vprintf(message.c_str(), args);
	va_end(args);
	cout << WHITE_T;
}

void JJM::Debug(const char* message, ...)
{
	cout << BRIGHT_YELLOW_T << "DEBUG: ";
	va_list args;
	va_start(args, message);
	vprintf(message, args);
	va_end(args);
	cout << WHITE_T << '\n';
}

void JJM::Error(const char* message, ...)
{
	cout << BRIGHT_RED_T << "ERROR: ";
	va_list args;
	va_start(args, message);
	vprintf(message, args);
	va_end(args);
	cout << WHITE_T << '\n';
}

const char* JJM::__get_enum_color(Color color)
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

void JJM::__handle_invalid_selection()
{
	cin.clear();
	cin.ignore(numeric_limits<streamsize>().max(), '\n');
	cout << "Invalid input!\n";
}

JJM::Menu::Menu(string title, initializer_list<string> menuItems)
	: Menu(0, title, menuItems) {
}

JJM::Menu::Menu(int column, string title, initializer_list<string> menuItems)
	: Menu(column, Color::WHITE, Color::WHITE, title, menuItems) {
}

JJM::Menu::Menu(int column, Color titleColor, string title, initializer_list<string> menuItems)
	: Menu(column, titleColor, Color::WHITE, title, menuItems) {
}

JJM::Menu::Menu(int column, Color titleColor, Color itemColor, string title, initializer_list<string> menuItems)
	: colSep{ column }, titleColor{ titleColor }, itemColor{ itemColor }, title{ title }, menuSize{ menuItems.size() }, multiColumn{ false } {
	if (colSep != 0)
		multiColumn = true;

	items = new string[menuSize];
	for (size_t i{ 0 }; i < menuSize; i++)
		items[i] = *(menuItems.begin() + i);
}

JJM::Menu::~Menu()
{
	delete[] items;
}

void JJM::Menu::Display() const
{
	int itemNum{ 0 };
	cout << JJM::__get_enum_color(titleColor) << title << "\n\n" << WHITE_T;

	if (multiColumn)
	{
		for (size_t i{ 0 }; i < menuSize; i++)
		{
			itemNum = i + 1;
			if (i % 2 == 0)
			{
				cout << JJM::__get_enum_color(itemColor) << itemNum << ") " << setw(colSep) << left << items[i] << WHITE_T;
				if (i == menuSize - 1)
				{
					cout << '\n';
				}
			}
			else
			{
				cout << JJM::__get_enum_color(itemColor) << itemNum << ") " << items[i] << '\n' << WHITE_T;
			}
		}
	}
	else
	{
		for (size_t i{ 0 }; i < menuSize; i++)
		{
			itemNum = i + 1;
			cout << JJM::__get_enum_color(itemColor) << itemNum << ") " << items[i] << '\n' << WHITE_T;
		}
	}
}

int JJM::Menu::Select()
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

void JJM::Rand::SetSeed()
{
	time_t seed{ time(nullptr) };
	srand(seed);
}

int JJM::Rand::RangeEx(int min, int max)
{
	return (rand() % (max - min)) + min;
}

int JJM::Rand::RangeIn(int min, int max)
{
	return (rand() % ((max + 1) - min)) + min;
}

float JJM::Rand::Rangef(float min, float max)
{
	float normal = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	return (normal * (max - min)) + min;
}