#pragma once
#define CEntityPrecacheContext char
#define CEntityKeyValues char
#define DataUpdateType_t char
#define EntityDormancyType_t char
#define CFieldPath char
#define ChangeAccessorFieldPathIndex_t char
#define IRestore char
#define ISave char

struct CSchemaClassBinding {
	CSchemaClassBinding* parent; // I THINK
	const char* bindingName; // ex: C_World
	const char* dllName; // ex: libclient.so
	const char* libName; // ex: client
};

class CEntityInstance 
{
public:
	virtual CSchemaClassBinding* SchemaDynamicBinding(void); // 0, 
	virtual void Destroy(); // 1, note: win64, only 1 destructor
	virtual int GetRefEHandle(); // 2, 
	virtual int GetScriptDesc(); // 3, 
	virtual void Connect(); // 4, 
	virtual void Precache(CEntityPrecacheContext const*); // 5, 
	virtual void AddedToEntityDatabase(); // 6, 
	virtual void Spawn(CEntityKeyValues const*); // 7, 
	virtual void PostDataUpdate(DataUpdateType_t); // 8, 
	virtual void Activate(); // 9, 
	virtual void UpdateOnRemove(); // 10, 
	virtual void OnSetDormant(EntityDormancyType_t, EntityDormancyType_t); // 11, 
	virtual void PreDataUpdate(DataUpdateType_t); // 12, 
	virtual void DrawEntityDebugOverlays(OverlayFlags_t flags); // 13, 
	virtual void Save(ISave &); // 14, 
	virtual void Restore(IRestore &); // 15, 
	virtual void OnSave(); // 16, 
	virtual void OnRestore(); // 17, 
	virtual void ObjectCaps(); // 18, 
	virtual void RequiredEdictIndex(); // 19, 
	virtual void NetworkStateChanged(); // 20, 
	virtual void NetworkStateChanged2(unsigned int, int, ChangeAccessorFieldPathIndex_t); // 21, 
	virtual void pad_unk_lwss_ads(); // 22, 
	virtual void AddChangeAccessorPath(CFieldPath const&); // 23, 
	virtual void ReloadPrivateScripts(); // 24, 
	virtual void pad_unk_obc_like(); // 25, 
};