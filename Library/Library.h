#include "stdafx.h"
#include "SDK.h"
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
	CGameEntitySystem* entities;
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
void cycle_fuck();