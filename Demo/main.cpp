#include <JJM_App.h>
#include "utils.h"
using namespace JJM;

AppResult JJM::Start(int argc, char **argv)
{
	Clear();
	Print(Color::BRIGHT_MAGENTA, "WELCOME TO THE JJM LIBRARY\n\n");
	AwaitEnter(true);
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