#include "utils.h"
#include "JJM_App.h"

Menu mainMenu(16, Color::BRIGHT_WHITE, "Main Menu",
{
	"Random Numbers",
	"Time",
	"Files",
	"Quit"
});

Menu randMenu(0, Color::BRIGHT_GREEN, "Random Numbers",
{
	"Generate exclusive int",
	"Generate inclusive int",
	"Generate float",
	"Back"
});

Menu timeMenu(0, Color::BRIGHT_CYAN, "Time",
{
	"Get time/date",
	"Get elapsed time",
	"Countdown",
	"Back"
});

Menu fileMenu(0, Color::BRIGHT_RED, "Files",
{
	"Write to file",
	"Append to file",
	"Clear file",
	"Read from file",
	"Back"
});

void PresentRandomNumbers()
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

void PresentTime()
{
	Clear();
	bool goBack{ false };
	while (!goBack)
	{
		timeMenu.Display();
		switch (timeMenu.Select())
		{
		case 0: Clear();
			Print("%s", Time::Now()); break;
		case 1: Clear();
			Print("Time since app start: %lf seconds\n", Time::GetElapsedTime()); break;
		case 2:
			for (int i{ 5 }; i > 0; i--)
			{
				Clear();
				Print(Color::BRIGHT_YELLOW, "%d\n", i);
				Time::Wait(1);
			}
			Clear();
			Print(Color::BRIGHT_YELLOW, "Countdown complete!\n"); break;
		case 3: Clear(); goBack = true;
		}
	}
}

void PresentFiles()
{
	Clear();
	bool goBack{ false };
	File file{ "sample_file.txt"};
	string contents;
	while (!goBack)
	{
		fileMenu.Display();
		switch (fileMenu.Select())
		{
		case 0: Clear();
			file.Write(InputLine("Enter text: ")); Clear();
			Print("File written to\n"); break;
		case 1: Clear();
			file.Append(InputLine("Enter text: ")); Clear();
			Print("File written to\n"); break;
		case 2: Clear();
			file.Clear();
			Print("File cleared\n"); break;
		case 3: Clear();
			contents = "";
			file.Begin();
			while (file.ReadLine(contents));
			Print("%s\n", contents.c_str()); AwaitEnter(true); break;
		case 4: Clear(); goBack = true;
		}
	}
}