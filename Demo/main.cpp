#include <JJM_App.h>
#include "utils.h"
using namespace JJM;

AppResult JJM::Start(int argc, char **argv)
{
	CLEAR;
	Print(Color::BRIGHT_MAGENTA, "WELCOME TO THE JJM LIBRARY\n\n");
	return CONTINUE;
}

AppResult JJM::Loop()
{
	mainMenu.Display();
	switch (mainMenu.Select())
	{
	case 0: GenerateRandomNumbers(); break;
	case 1: return QUIT;
	}
	return CONTINUE;
}

void JJM::End()
{

}