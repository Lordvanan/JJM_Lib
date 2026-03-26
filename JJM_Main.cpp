#ifdef USE_JJM_CONTEXT
#include "JJM_App.h"

int main(int argc, char* argv[])
{
	JJM_Rand::SetSeed();

	// Calls the main start function and stores the result.
	AppResult result = JJMApp_Start(argc, argv);

	// The main program loop.
	while (result == APP_CONTINUE)
	{
		result = JJMApp_Loop();
	}

	JJMApp_End();
	return 0;
}
#endif