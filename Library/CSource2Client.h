#pragma once
#include "IAppSystem.h"
#include "definitions.h"

struct RecvProp;

struct DVariant
{
	union
	{
		float m_Float;
		long m_Int;
		char *m_pString;
		void *m_pData;
		float m_Vector[3];
		int64_t m_Int64;
	};

	int m_Type;
};

struct CRecvProxyData
{
	const RecvProp* m_pRecvProp;
	DVariant m_Value;
	int m_iElement;
	int m_ObjectID;
};

struct RecvTable
{
	RecvProp *m_pProps;
	int m_nProps;
	void *m_pDecoder;
	char *m_pNetTableName;
	bool m_bInitialized;
	bool m_bInMainList;
};

typedef void(*RecvVarProxyFn) (const CRecvProxyData *pData, void *pStruct, void *pOut);

struct RecvProp
{
	char *m_pVarName;
	int m_RecvType;
	int m_Flags;
	int m_StringBufferSize;
	bool m_bInsideArray;
	const void *m_pExtraData;
	RecvProp *m_pArrayProp;
	void *m_ArrayLengthProxy;
	RecvVarProxyFn m_ProxyFn;
	void *m_DataTableProxyFn;
	RecvTable *m_pDataTable;
	int m_Offset;
	int m_ElementStride;
	int m_nElements;
	const char *m_pParentArrayPropName;
};

class ClientClass
{
public:
	char* m_pNetworkName; //0x0000 //EX: CDOTAPlayer
	char* m_pClassName; //0x0008 //EX: C_DOTAPlayer
	ClientClass* m_pNext; //0x0010
	void* m_pCreateFn; //0x0018
	void* m_pCreateEventFn; //0x0020
	void* m_pDestroyFn; //0x0028
	char pad_0030[8]; //0x0030
	char* m_pLibNameAndClassName; //0x0038 //EX: libclient.so!C_DOTAPlayer
	void* Schema; //0x0040
	char pad_0048[20]; //0x0048
	EClassIds m_ClassID; //0x005C
	void* N00000046; //0x0060
	void* N00000047; //0x0068
};

class CSource2Client : IAppSystem
{
public:
	virtual void SetGlobals(void* CGlobalVarsBase);; // 11
	virtual void InstallStringTableCallback(const char *);
	virtual void PlayerInfoChanged(int entIndex); // 13
	virtual void ClearInstancedBaselineFromClientClasses(void); // 14
	virtual void CreateMove(int screenSlot, int, bool); // 15
	virtual void* _16();
	virtual void* _17();
	virtual void SendMove(int screanSlot, int); // 18
	virtual void ProcessInput(int screenSlot, float, bool); // 19
	virtual void WriteUserCmdDeltaToBuffer(int, void*, int, int, bool); // 20
	virtual bool EncodeUserCmdToBuffer(void* CSplitScreenSlot_t, char&, int);
	virtual bool DecodeUserCmdToBuffer(void* CSplitScreenSlot_t, char&, int);
	virtual void GetEntity2Networkable(int entIndex, void* Entity2Networkable_t);
	virtual const char* GetEntity2ClassName(int entIndex);
	virtual void GetNetworkFieldChangeCallbackQueue(void); // 25
	virtual void NotifyShouldTransmit();
	virtual ClientClass* GetAllClasses(); // 27
	virtual void ReceivedServerInfo(void* GameSessionConfiguration_t, void* ILoopModePrerequisiteRegistry);
	virtual void FrameStageNotify(ClientFrameStage_t stage); // 29
};