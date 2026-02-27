#include "JJM_App.h"

int main(int argc, char* argv[])
{
	JJM_Rand::SetSeed();

	// Calls the main start function and stores the result.
	AppResult result = JJMApp_Start(argc, argv);

	// Ends the program early is there is an issue in initialization.
	if (result == APP_ERROR)
	{
		JJM_Log("Failed to initialize program.");
		return 1;
	}

	// The main program loop.
	while (result == APP_CONTINUE)
	{
		result = JJMApp_Loop();
	}

	// Determines how to handle the program termination.
	if (result == APP_QUIT)
	{
		JJMApp_End();
		return 0;
	}
	else
	{
		JJM_Log("Program terminated on an error!");
		return 1;
	}
}