#include "stdafx.h"
#include "System.h"
#include <thread>
#include <chrono>

bool isRunning = 1;
bool ThreadIsRunning()
{
	using namespace chrono_literals;
	this_thread::sleep_for(10ms);
	return isRunning;
}

void PostStartupLogic() 
{

	isRunning = false;
}