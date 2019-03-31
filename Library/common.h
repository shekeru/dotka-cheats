#pragma once
#include <cstring>
#include <vector>


struct InterfaceMetaData
{
	const char* name;
	uint32_t numVMs;
	void* interface;
};

//inline std::vector<InterfaceMetaData> requestedInterfaces = {}; // requested but failed
//inline std::vector<InterfaceMetaData> grabbedInterfaces = {}; // grabbed and can be used

typedef void* (*InstantiateInterfaceFn) ();

struct InterfaceReg
{
	InstantiateInterfaceFn m_CreateFn;
	const char *m_pName;
	InterfaceReg *m_pNext;
};

inline void**& getvtable(void* inst, size_t offset = 0)
{
	return *reinterpret_cast<void***>((size_t)inst + offset);
}

inline const void** getvtable(const void* inst, size_t offset = 0)
{
	return *reinterpret_cast<const void***>((size_t)inst + offset);
}

template<typename Fn>
inline Fn getvfunc(const void* inst, size_t index, size_t offset = 0)
{
	return reinterpret_cast<Fn>(getvtable(inst, offset)[index]);
}

inline uintptr_t GetAbsoluteAddress(uintptr_t instruction_ptr, int offset)
{
	return instruction_ptr + *reinterpret_cast<int32_t*>(instruction_ptr + offset) + offset + 4;
};

inline uintptr_t* vmt_slot(void* instance, int offset) {
	return (*(uintptr_t**)instance) + offset;
	//return getvfunc<uintptr_t>(instance, offset);
}

inline uintptr_t* vmt_alloc(void* instance, int number) {
	size_t bytes = sizeof(uintptr_t) * number;
	//uintptr_t* vmt = (uintptr_t*)instance;
	void* source = *(void**)instance;
	(*(uintptr_t*)instance) = (uintptr_t) memcpy(malloc(bytes),
		source, bytes);
	return (uintptr_t*) source;
}

struct CSchemaClassBinding {
	CSchemaClassBinding* parent; // I THINK
	const char* bindingName; // ex: C_World
	const char* dllName; // ex: libclient.so
	const char* libName; // ex: client
};

class TypeDescription;

class Datamap
{
public:
	TypeDescription *dataDesc;
	uint64_t numFields;
	const char *className; // Ex: C_DOTAPlayer
	Datamap *baseMap; // Ex: For C_DOTAPlayer it would be next baseclass C_BasePlayer, can be NULL
};

class TypeDescription
{
public:
	fieldtype_t type;
	const char *fieldName;
	int fieldOffset[TD_OFFSET_COUNT];
	void *_unk[5];
	Datamap * td;
	void *_unk2[5];
};
