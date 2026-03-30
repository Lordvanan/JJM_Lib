#include "JJM_Time.h"

steady_clock::time_point JJM::Time::start;
steady_clock::time_point JJM::Time::end;
time_t JJM::Time::waitRef;

char* JJM::Time::Now()
{
	system_clock::time_point today = system_clock::now();
	time_t date = system_clock::to_time_t(today);

	return ctime(&date);
}

void JJM::Time::Wait(int seconds)
{
	waitRef = time(nullptr);
	time_t elapsedSeconds = 0;

	while (elapsedSeconds < seconds)
	{
		time_t timeCheck = time(nullptr);
		elapsedSeconds = timeCheck - waitRef;
	}
}

void JJM::Time::StartElapsedTime()
{
	start = steady_clock::now();
}

double JJM::Time::GetElapsedTime()
{
	end = steady_clock::now();
	return double(duration_cast<nanoseconds>(end - start).count() / 1e9);
}