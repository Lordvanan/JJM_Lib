#include "JJM_Time.h"

steady_clock::time_point JJM_Time::start;
steady_clock::time_point JJM_Time::end;
time_t JJM_Time::waitRef;

char* JJM_Time::Now()
{
	system_clock::time_point today = system_clock::now();
	time_t date = system_clock::to_time_t(today);

	return ctime(&date);
}

void JJM_Time::Wait(int seconds)
{
	waitRef = time(nullptr);
	time_t elapsedSeconds = 0;

	while (elapsedSeconds < seconds)
	{
		time_t timeCheck = time(nullptr);
		elapsedSeconds = timeCheck - waitRef;
	}
}

void JJM_Time::StartElapsedTime()
{
	start = steady_clock::now();
}

double JJM_Time::GetElapsedTime()
{
	end = steady_clock::now();
	return double(duration_cast<nanoseconds>(end - start).count() / 1e9);
}