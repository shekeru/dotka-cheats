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

extern ClientLoader client;
extern EngineLoader engine;

class Internal {
public:
	VMT* events = new VMT(client.events);
	VMT* entity = new VMT(client.entity);
};

extern Internal sdk;

bool ThreadIsRunning();
void PostStartupLogic();

using namespace std;
