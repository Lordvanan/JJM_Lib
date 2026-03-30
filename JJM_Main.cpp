#ifdef USE_JJM_CONTEXT
#include "JJM_App.h"

int main(int argc, char* argv[])
{
	JJM::Rand::SetSeed();

	//Calls the main start function and stores the result.
	AppResult result = JJM::Start(argc, argv);

	// The main program loop.
	while (result == CONTINUE)
	{
		result = JJM::Loop();
	}

	JJM::End();
	return 0;
}
#endif