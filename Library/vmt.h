#pragma once

class VMT
{
public:
	uintptr_t* vmt;
	uintptr_t* sdk_vmt = nullptr;
	uintptr_t** interface = nullptr;
	size_t method_count = 0;
	VMT(void* instance)
	{
		interface = reinterpret_cast<uintptr_t**>(instance);
		sdk_vmt = *interface; while (sdk_vmt[method_count])
		method_count++; vmt = new uintptr_t[method_count + 1]();
		memcpy(vmt, sdk_vmt, sizeof(uintptr_t) * method_count);
	}
	template <typename func>
	void HookVM(func method, size_t methodIndex)
	{
		vmt[methodIndex] = reinterpret_cast<uintptr_t>(method);
	}
	template<typename Fn>
	Fn GetOriginalMethod(size_t index)
	{
		return reinterpret_cast<Fn>(sdk_vmt[index]);
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