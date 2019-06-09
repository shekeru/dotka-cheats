// Library Headers
#include "CSource2Client.h"
#include "CEngineClient.h"
// Managers & Systems
#include "CEventManager.h"
#include "CEntitySystem.h"
// Object Headers
#include "CDotaPlayer.h"
// Misc Required
#include <map>

class VMT
{
public:
	uintptr_t* vmt;
	uintptr_t* sdk_vmt = nullptr;
	uintptr_t** interface = nullptr;
	std::map<uintptr_t, size_t> map;
	size_t method_count = 0;
	VMT(void* instance)
	{
		interface = reinterpret_cast<uintptr_t**>(instance);
		sdk_vmt = *interface; while (sdk_vmt[method_count])
			method_count++; vmt = new uintptr_t[method_count + 1]();
		memcpy(vmt, sdk_vmt, sizeof(uintptr_t) * method_count);
	}
	template <typename func>
	void HookVM(func ref, size_t index)
	{
		vmt[index] = reinterpret_cast<uintptr_t>(ref);
		map[(uintptr_t) ref] = index;
	}
	template<typename Fn>
	auto GetOriginalMethod(Fn &ref, size_t index)
	{
		return reinterpret_cast<decltype(&ref)>(sdk_vmt[index]);
	}
	template<typename Fn>
	auto GetOriginalMethod(Fn &ref)
	{
		return GetOriginalMethod(ref, map[(uintptr_t) ref]);
	}
	void ReleaseVMT()
	{
		if (interface && *interface && sdk_vmt)
			*this->interface = sdk_vmt;
	}
	void ApplyVMT()
	{
		*interface = vmt;
	}
	~VMT() {
		ReleaseVMT();
		delete[] vmt;
	}
};
// Store for now
typedef void* (*InstantiateInterfaceFn) ();

struct InterfaceReg
{
	InstantiateInterfaceFn m_CreateFn;
	const char *m_pName;
	InterfaceReg *m_pNext;
};

inline uintptr_t GetAbsoluteAddress(uintptr_t instruction_ptr, int offset)
{
	return instruction_ptr + *reinterpret_cast<int32_t*>(instruction_ptr + offset) + offset + 4;
};

inline uintptr_t* vmt_slot(void* instance, int offset) {
	return (*(uintptr_t**)instance) + offset;
}