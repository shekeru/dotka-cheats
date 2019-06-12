#pragma once
// Fun Macros
#define $(value) \
	*(uint32_t*)value

namespace Utils {
	using namespace std;
	inline struct console {
		HANDLE err, out, in;
	} old, now; void EnableConsole(); void DisableConsole(); char ConsoleReadKey();
	int WaitForModules(int32_t timeout, const initializer_list<string>& modules);
	void BindCrtHandlesToStdHandles(bool bindStdIn, bool bindStdOut, bool bindStdErr);
	void ClearConsole(char fill); template<typename ptr>
	inline void PrintBytes(ptr target, int range = 16) {
		for (auto i = 0; i < range; i++) {
			printf("%hhx ", PUCHAR(target)[i]);
		}; printf("\n");
	};
}

// Store for now
//template< typename ptr = uintptr_t>
//inline uintptr_t GetAbsoluteAddress(ptr instruction_ptr, int offset)
//{
//	return instruction_ptr + *reinterpret_cast<int32_t*>(instruction_ptr + offset) + offset + 4;
//};

template<typename ptr>
inline uintptr_t* vmt_slot(ptr* instance, int offset) {
	return (*(uintptr_t**)instance) + offset;
}

template<typename obj, typename ptr>
inline obj resolve_addr(int offset, ptr src, int width = 3) {
	auto addr_start = uintptr_t(src) + offset + width;
	return *(obj*)(addr_start + $(addr_start) + 4);
}