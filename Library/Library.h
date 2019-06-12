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
		printf("Module \"%s\" loaded at %x\n", module = name, handle = GetModuleHandle(name));
		CreateInterface = (CreateInterfaceFn)GetProcAddress(handle, "CreateInterface");
		InterfaceList = *resolve_addr<InterfaceReg**>(0x0, CreateInterface, 3);
			printf(" [+] CreateInterface: %x\n", CreateInterface);
	}
	// Properties
	LPCSTR module;
	HINSTANCE handle;
	InterfaceReg* InterfaceList;
	CreateInterfaceFn CreateInterface;
	// Misc Shit
	void ListInterfaces() {
		for (InterfaceReg* current = InterfaceList; current; current = current->m_pNext)
			printf("\t%s => 0x%llx\n", current->m_pName, current->m_CreateFn());
	};
};

inline class Internal {
public:
	void GetModules() {
		this->client = new Library("client.dll");
		this->engine = new Library("engine2.dll");
		//this->vgui = new Library("vgui2.dll");
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
	// Second Tier
	CGameEntitySystem* entity;
	CGameEventManager* events;
} sdk;

inline class Hooking {
public:
	VMT* events;
	VMT* entity;
	// Helper Functions
	void CreateVMTs() {
		VMT* events = new VMT(sdk.events);
		VMT* entity = new VMT(sdk.entity);
	} void AttachVMs() {
		events->ApplyVMT();
		entity->ApplyVMT();
	}
} vmt;