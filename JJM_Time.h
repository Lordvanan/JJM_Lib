#define _CRT_SECURE_NO_WARNINGS

#ifndef JJM_LIB_TIME
#define JJM_LIB_TIME 1

#include <chrono>
#include <ctime>

using std::chrono::system_clock;
using std::chrono::steady_clock;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;

class JJM_Time
{
	static steady_clock::time_point start;
	static steady_clock::time_point end;
	static time_t waitRef;

public:

	/// <summary>
	/// Gets the date and time at the time of being called and returns it as a character string.
	/// </summary>
	/// <returns>The character string of the current date and time formatted in a readable way.</returns>
	static char* Now();

	/// <summary>
	/// Delays the next operation by a number of seconds before continuing.
	/// </summary>
	/// <param name="seconds">The number of seconds to wait.</param>
	static void Wait(int seconds);

	/// <summary>
	/// Stores the current time elapsed from the program start time.
	/// Call this before GetElapsedTime to accurately determine elapsed time between two points.
	/// </summary>
	static void StartElapsedTime();

	/// <summary>
	/// Stores the current time at the time of being called and subtracts the start time determined by StartElapsedTime.
	/// Returns the total elapsed time in seconds from the time StartElapsedTime was called.
	/// </summary>
	/// <returns></returns>
	static double GetElapsedTime();
};

#endif