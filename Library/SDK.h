#pragma once
// Library Headers
#include "CSource2Client.h"
#include "CEngineClient.h"
#include "IVPanel.h"
// Managers & Systems
#include "CEventManager.h"
#include "CEntitySystem.h"
#include "IClientMode.h"
// Object Headers
#include "CDotaBaseNPC.h"
#include "CDotaPlayer.h"
// Misc Required
#include <stdexcept>
#include <cstdint>
#include <set>
#include <map>

namespace detail
{
	class protect_guard
	{
	public:
		protect_guard(void* base, size_t len, uint32_t flags)
		{
			_base = base;
			_length = len;
			if (!VirtualProtect(base, len, flags, (PDWORD)&_old))
				throw std::runtime_error("Failed to protect region.");
		}
		~protect_guard()
		{
			VirtualProtect(_base, _length, _old, (PDWORD)&_old);
		}

	private:
		void*         _base;
		size_t        _length;
		uint32_t _old;
	};
	inline bool validate(uintptr_t memory) {
		if (!memory || memory > 0x7fffffffffff) return false;
		MEMORY_BASIC_INFORMATION info; VirtualQuery(LPCVOID(memory), 
			&info, sizeof(MEMORY_BASIC_INFORMATION));
		return info.AllocationProtect & PAGE_EXECUTE_WRITECOPY;
	};
};

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
		sdk_vmt = *interface; while (detail::validate(sdk_vmt[method_count]))
			method_count++; vmt = new uintptr_t[method_count + 1]();
		memcpy(vmt, &sdk_vmt[-1], sizeof(uintptr_t) * method_count);
		//printf("VM Total: %p => %d\n", interface, method_count);
	}
	template <typename func>
	void HookVM(func ref, size_t index)
	{
		vmt[index+1] = reinterpret_cast<uintptr_t>(ref);
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
		auto guard = detail::protect_guard{interface,
			sizeof(uintptr_t), PAGE_READWRITE};
		if (interface && *interface && sdk_vmt)
			*this->interface = sdk_vmt;
	}
	void ApplyVMT()
	{
		auto guard = detail::protect_guard{interface,
			sizeof(uintptr_t), PAGE_READWRITE};
		*interface = &vmt[1];
	}
	~VMT() {
		ReleaseVMT();
		delete[] vmt;
	}
	void CheckVMT(int last_known) {
		if (method_count != last_known)
			printf("<VMT ERROR>, for _interface_ with x of y\n");
	}
};