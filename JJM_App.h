#ifndef JJM_LIB_FRAMEWORK
#define JJM_LIB_FRAMEWORK 1

#include <iostream>
#include <iomanip>
#include <initializer_list>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdarg>
#include <ctime>
#include <limits>

using std::cin;
using std::cout;
using std::getchar;
using std::getline;
using std::left;
using std::setw;
using std::string;
using std::streamsize;
using std::numeric_limits;
using std::initializer_list;

// Macros for the AppResult values for easy use in programs.
#define APP_CONTINUE AppResult::CONTINUE
#define APP_QUIT AppResult::QUIT

// Console output control macros for clean presentation.
#define HOLD cout << "Press Enter to continue..."; cin.ignore(numeric_limits<streamsize>().max(), '\n'); getchar()
#define CLEAR system("clear")
#define AWAIT HOLD; CLEAR
#define NWLN cout << '\n'

// Color definitions for text colors in the console
#define BLACK_T "\033[30m"
#define RED_T "\033[31m"
#define GREEN_T "\033[32m"
#define YELLOW_T "\033[33m"
#define BLUE_T "\033[34m"
#define MAGENTA_T "\033[35m"
#define CYAN_T "\033[36m"
#define WHITE_T "\033[37m"
#define BRIGHT_BLACK_T "\033[90m"
#define BRIGHT_RED_T "\033[91m"
#define BRIGHT_GREEN_T "\033[92m"
#define BRIGHT_YELLOW_T "\033[93m"
#define BRIGHT_BLUE_T "\033[94m"
#define BRIGHT_MAGENTA_T "\033[95m"
#define BRIGHT_CYAN_T "\033[96m"
#define BRIGHT_WHITE_T "\033[97m"

// The program result that determines whether to continue operating or to end the program.
// Also is the handler for if an error occurs during program runtime.
enum class AppResult
{
	CONTINUE,
	QUIT,
};

enum class Color
{
	BLACK,
	RED,
	GREEN,
	YELLOW,
	BLUE,
	MAGENTA,
	CYAN,
	WHITE,
	BRIGHT_BLACK,
	BRIGHT_RED,
	BRIGHT_GREEN,
	BRIGHT_YELLOW,
	BRIGHT_BLUE,
	BRIGHT_MAGENTA,
	BRIGHT_CYAN,
	BRIGHT_WHITE
};

// The entry point for all programs implementing the JJM Framework.
// Everything that needs to be done only at the beginning of the program should be included here.
// To continue on to the main loop of the program, return APP_CONTINUE.
AppResult JJMApp_Start(int argc, char* argv[]);

// The main loop of the program where all repeating procedures will be implemented.
// This loop will continue until APP_QUIT is returned.
// If the loop is to continue, return APP_CONTINUE.
// If the loop is to end, thus ending the program, return APP_QUIT.
AppResult JJMApp_Loop();

// The closing point of the program.
// This is called just prior to the final termination of the program.
// Use this for any cleanup procedures that need to take place.
void JJMApp_End();

// Safely clears input buffer, and throws an error message.
void __handle_invalid_selection();

// Outputs a message to the console.
void JJM_Log(const char* message, ...);

// Outputs a message to the console with a specified color.
void JJM_Log(Color color, const char* message, ...);

// Outputs a message to the console.
void JJM_Log(string message, ...);

// Outputs a message to the console with a specified color.
void JJM_Log(Color color, string message, ...);

// Outputs a prominent message for debugging purposes.
void JJM_Debug(const char* message, ...);

const char* __get_enum_color(Color color);

template<typename T>
inline T __get_user_input()
{
	T input{};
	while (true)
	{
		cin >> input;
		if (cin.fail())
		{
			__handle_invalid_selection();
			continue;
		}
		break;
	}
	return input;
}

// Using a user input prompt and data type definition, takes the user's input from the console.
template<typename T>
inline T JJM_Input(const char* prompt, ...)
{
	va_list args;
	va_start(args, prompt);
	vprintf(prompt, args);
	va_end(args);

	return __get_user_input<T>();
}

// Using a user input prompt in a specified color and data type definition, takes the user's input from the console.
template<typename T>
inline T JJM_Input(Color color, const char* prompt, ...)
{
	cout << __get_enum_color(color);
	va_list args;
	va_start(args, prompt);
	vprintf(prompt, args);
	va_end(args);
	cout << WHITE_T;

	return __get_user_input<T>();
}

// Using a user input prompt and data type definition, takes the user's input from the console.
template<typename T>
inline T JJM_Input(string prompt, ...)
{
	va_list args;
	va_start(args, prompt);
	vprintf(prompt.c_str(), args);
	va_end(args);

	return __get_user_input<T>();
}

// Using a user input prompt in a specified color and data type definition, takes the user's input from the console.
template<typename T>
inline T JJM_Input(Color color, string prompt, ...)
{
	cout << __get_enum_color(color);
	va_list args;
	va_start(args, prompt);
	vprintf(prompt.c_str(), args);
	va_end(args);
	cout << WHITE_T;

	return __get_user_input<T>();
}

// Create pre-formatted menus designed to handle input and invalid input handling.
class JJM_Menu
{
	string title;
	string* items;
	size_t menuSize;
	bool multiColumn;
	int colSep;
	Color titleColor;
	Color itemColor;

public:
	// JJM_Menu contrustor the presents the menu in a single column.
	JJM_Menu(string title, initializer_list<string> menuItems);

	// JJM_Menu constructor that structures the menu separated by the column value provided.
	// Entering 0 for the column with arrange the items in a single column.
	JJM_Menu(int column, string title, initializer_list<string> menuItems);

	// JJM_Menu constructor that structures the menu separated by the column value provided, with the title color specified.
	// Entering 0 for the column with arrange the items in a single column.
	JJM_Menu(int column, Color titleColor, string title, initializer_list<string> menuItems);

	// JJM_Menu constructor that structures the menu separated by the column value provided, with the title and item color specified.
	// Entering 0 for the column with arrange the items in a single column.
	JJM_Menu(int column, Color titleColor, Color itemColor, string title, initializer_list<string> menuItems);

	// JJM_Menu destructor that frees the memory used for the menu items.
	~JJM_Menu();

	// Prints out the menu to the console, organized by number in the defined order and format.
	void Display() const;

	// Takes in a user input to select from the menu options.
	// Validates user input against the available menu options only returns if the input is valid.
	int Select();

	// Returns the number of menu options.
	int Size();
};

// Random number generator class with range options for inclusive and exclusive integers and floats.
class JJM_Rand
{
public:
	// Sets the seed for the pseudo-random number generator.
	// This is called automatically upon program start and should not be called manually.
	static void SetSeed();

	// Generates a random integer within an exclusive range between min and max.
	static int RangeEx(int min, int max);

	// Generates a random integer within an inclusive range between min and max.
	static int RangeIn(int min, int max);

	// Generates a random float within an inclusive range between min and max.
	static float Rangef(float min, float max);
};

#endif