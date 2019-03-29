#pragma once
#include "IAppSystem.h"
#include "IInputSystem.h"
#include "vector.h"
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

class IClientNetworkable;
typedef IClientNetworkable* (*CreateClientClassFn)(int entnum, int serialNum);
typedef IClientNetworkable* (*CreateEventFn)();

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
	virtual void* _11();
	virtual void* _12();
	virtual void PlayerInfoChanged(int entIndex);
	virtual void* _14();
	virtual void* _15();
	virtual void* _16();
	virtual void* _17();
	virtual void* _18();
	virtual void* _19();
	virtual void* _20();
	virtual void* _21();
	virtual void* _22();
	virtual void* _23(); // bool_chr EntityFuckery
	virtual void* _24();
	virtual void* _25();
	virtual void* _26();
	virtual ClientClass* GetAllClasses(); //27
};