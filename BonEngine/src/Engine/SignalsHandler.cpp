#include <iostream>
#include <csignal>
#include <BonEngine.h>
#include <Engine/SignalHandler.h>

using namespace std;

// the function to handle signals
void SignalHandler(int signum) 
{
	printf("Got signal %d while engine is in state: %d. App will crash.\n", signum, bon::_GetEngine().CurrentState());
	BON_ELOG("Got signal %d while engine is in state: %d. App will crash.", signum, bon::_GetEngine().CurrentState());
	bon::_GetEngine().Log().Flush();
	exit(signum);
}

// register signals handler
void RegisterSignalsHandler()
{
	BON_DLOG("Register signals handler.");
	signal(SIGINT, SignalHandler);
	signal(SIGILL, SignalHandler);
	signal(SIGFPE, SignalHandler);
	signal(SIGSEGV, SignalHandler);
	signal(SIGTERM, SignalHandler);
	signal(SIGBREAK, SignalHandler);
	signal(SIGABRT, SignalHandler);
}
