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
	virtual void DESTROY10(); // note: win64 only has 1 destrcutor
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
	virtual void DrawEntityDebugOverlays(OverlayFlags_t flags);
	virtual void Save(ISave &);
	virtual void Restore(IRestore &);
	virtual void OnSave(void);
	virtual void OnRestore(void);
	virtual void ObjectCaps(void);
	virtual int RequiredEdictIndex(void);
	virtual void NetworkStateChanged(void); // 20
	virtual void NetworkStateChanged(unsigned int, int, ChangeAccessorFieldPathIndex_t);
	virtual void AddChangeAccessorPath(CFieldPath const&);
	virtual void ReloadPrivateScripts(void);
};