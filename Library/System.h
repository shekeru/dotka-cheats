#include "stdafx.h"
#include "Cheat.h"
#pragma once

class ModuleSystem
{
public:
	LPCSTR module;
	HMODULE library;
	uintptr_t CreateInterface;
	InterfaceReg* InterfaceList;
	template <typename interface>
	interface* LoadInterface(LPCSTR name);
	ModuleSystem(LPCSTR module);
	~ModuleSystem();
};

class ClientLoader : ModuleSystem
{
public:
	CSource2Client* client;
	CGameEntitySystem* entity;
	CGameEventManager* events;
	ClientLoader();
};

class EngineLoader : ModuleSystem
{
public:
	CEngineClient* client;
	EngineLoader();
};

class Internal {
public:
	VMT* events;
	VMT* entity;
	Internal();
	~Internal();
};

// Global Externs
extern ClientLoader client;
extern EngineLoader engine;
extern Internal sdk;

using namespace std;
bool ThreadIsRunning();
void PostStartupLogic();
