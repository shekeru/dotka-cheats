#pragma once
#include "IAppSystem.h"

class CEngineClient : IAppSystem
{
public:
	virtual void* _11();
	virtual void* _12();
	virtual void* _13();
	virtual void* _14();
	virtual void* _15();
	virtual void* _16();
	virtual void* _17();
	virtual void* _18();
	virtual void* _19();
	virtual void* _20();
	virtual int GetPlayerForUserID(int ID) = 0;
	virtual void* GetLocalPlayer(DWORD* a2, int a3);
};