// Loader.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "External.h"
#include <iostream>

using namespace std;

int main()
{
	InjectionManager* cheatloader = new InjectionManager();
	cheatloader->LoadPath("C:\\Coding Repos (Home)\\Fucking Windows\\Dotka\\x64\\Debug\\Library.dll");
		delete cheatloader; cout << "[Injector] Init okay!\n"; 
}