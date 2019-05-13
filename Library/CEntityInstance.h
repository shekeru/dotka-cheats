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
	virtual CSchemaClassBinding* SchemaDynamicBinding(void); // 0?
	virtual void DESTROY(); // note: win64 only has 1 destrcutor
	virtual int GetRefEHandle(void);
	virtual int GetScriptDesc(void);
	virtual void Connect(void);
	virtual void Precache(CEntityPrecacheContext const*);
	virtual void AddedToEntityDatabase(void);
	virtual void Spawn(CEntityKeyValues const*);
	virtual void PostDataUpdate(DataUpdateType_t);
	virtual void Activate(void);
	virtual void UpdateOnRemove(void); // 10
	virtual void OnSetDormant(EntityDormancyType_t, EntityDormancyType_t);
	virtual void PreDataUpdate(DataUpdateType_t);
	virtual void DrawEntityDebugOverlays(OverlayFlags_t flags); // 13
	virtual void Save(ISave &); // 14
	virtual void Restore(IRestore &);
	virtual void OnSave(void);
	virtual void OnRestore(void); //
	virtual void ObjectCaps(void);
	virtual int RequiredEdictIndex(void);
	virtual void NetworkStateChanged(void); // 20
	virtual void NetworkStateChanged2(unsigned int, int, ChangeAccessorFieldPathIndex_t);
	virtual void* pad_unk_lwss_ads();
	virtual void AddChangeAccessorPath(CFieldPath const&);
	virtual void ReloadPrivateScripts(void); // 24
	virtual void* pad_unk_obc_like(); // 25
};