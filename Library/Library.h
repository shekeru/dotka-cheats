#pragma once
#include "stdafx.h"
#include "sdk.h"

class Library
{
public:
	template <typename Object>
	Object* LoadInterface(LPCSTR name);
	Library(LPCSTR name)
	{
		printf("Module \"%s\" loaded at %p\n", module = name, handle = GetModuleHandle(name));
		CreateInterface = (CreateInterfaceFn)GetProcAddress(handle, "CreateInterface");
		InterfaceList = resolve_addr<InterfaceReg*>(0x0, CreateInterface, 3);
			printf(" [+] CreateInterface: %p\n", CreateInterface);
	}
	// Properties
	LPCSTR module;
	HINSTANCE handle;
	InterfaceReg* InterfaceList;
	CreateInterfaceFn CreateInterface;
	// Misc Shit
	void ListInterfaces() {
		for (InterfaceReg* current = InterfaceList; current; current = current->m_pNext)
			printf("\t%s => 0x%llx\n", current->m_pName, current->m_CreateFn);
	};
};

inline class Internal {
public:
	void GetModules() {
		this->client = new Library("client.dll");
		this->engine = new Library("engine2.dll");
		this->vgui = new Library("vgui2.dll");
	};  void GetInterfaces();
	// Stuff
	bool isRunning = true;
	Library* client;
	Library* engine;
	Library* vgui;
} cheat;

inline class Interfaces {
public:
	// First Tier
	CSource2Client* client;
	CEngineClient* engine;
	IVPanel* panel;
	// Second Tier
	CGameEntitySystem* entity;
	CGameEventManager* events;
	IClientMode* cmode;
	// My Tier
	std::set<CDotaBaseNPC*> Heroes;
	std::set<CDotaBaseNPC*> Creeps;
	std::set<CDotaBaseNPC*> Wards;
	CDotaPlayer* LocalPlayer;
	CDotaBaseNPC* LocalHero;
} sdk;

inline class Hooking {
public:
	VMT* player;
	VMT* client;
	VMT* events;
	VMT* entity;
	VMT* panel;
	// Helper Functions
	void CreateVMTs() {
		client = new VMT(sdk.client);
		events = new VMT(sdk.events);
		entity = new VMT(sdk.entity);
		panel = new VMT(sdk.panel);
	} void AttachVMs() {
		client->ApplyVMT();
		events->ApplyVMT();
		entity->ApplyVMT();
		panel->ApplyVMT();
	} void UnloadAll() {
		delete events;
		delete entity;
		delete client;
		delete panel;
	}
} vmt;