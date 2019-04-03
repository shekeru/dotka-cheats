#pragma once
#include "IAppSystem.h"

class CEngineClient : IAppSystem
{
public:
	typedef struct player_info_s
	{
		int64_t __pad0;
		union {
			int64_t xuid;
			struct {
				int xuidlow;
				int xuidhigh;
			};
		};
		char name[128];
		int userid;
		char guid[33];
		unsigned int friendsid;
		char friendsname[128];
		bool fakeplayer;
		bool ishltv;
		unsigned int customfiles[4];
		unsigned char filesdownloaded;
	} player_info_t;
	virtual bool IsPaused(void) = 0; // 11
	virtual float GetTimeScale(void) = 0;
	virtual void FindOrCreateWorldSession(void) = 0;
	virtual void GetEntityLumpForTemplate(void) = 0;
	virtual void GetStatsAppID(void) = 0;
	virtual void* GetGameClientFactory(void) = 0;
	virtual void* GetSteamUniverse(void) = 0; // Added Late June 2018
	virtual void ServerCmd(int inputCommandSrc, const char* command) = 0;
	virtual void ClientCmd(int inputCommandSrc, const char* command) = 0;
	virtual bool GetPlayerInfo(int iIndex, player_info_t *pInfo) = 0; // 20
	virtual int GetPlayerForUserID(int ID) = 0;
	virtual void* GetLocalPlayer(DWORD* a2, int a3);
	virtual long GetLastTimestamp(void) = 0;
	virtual int GetLastServertick(void) = 0;
	virtual void GetSentence(void) = 0;
	virtual void GetSentenceLength(void) = 0;
	virtual int GetMaxClients(void) = 0;
	virtual bool IsInGame(void) = 0;
	virtual bool IsConnected(void) = 0;
	virtual void ConNPrintf(int unk, const char* str, ...) = 0; // 30
	virtual void ConNXPrintf(void * const printf_options_t, const char* str, ...) = 0;
	virtual void* GetNetChannelInfo(int splitScreenSlot = 0) = 0;
	virtual bool IsPlayingDemo(void) = 0;
	virtual bool IsRecordingDemo(void) = 0;
	virtual bool IsPlayingTimeDemo(void) = 0;
	virtual void ExecuteClientCmd(const char* command) = 0;
	virtual void ClientCmd_Unrestricted(const char* command) = 0;
};