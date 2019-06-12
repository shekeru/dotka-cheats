#include "stdafx.h"
#include "utils.h"

namespace Utils {
	int WaitForModules(int32_t timeout, const initializer_list<string>& modules)
	{
		uint32_t totalSlept = 0;
		bool signaled[32] = { 0 };
		bool success = false;
		// Instant?
		if (timeout == 0) {
			for (auto& mod : modules) {
				if (GetModuleHandle(data(mod)) == NULL)
					return WAIT_TIMEOUT;
			};  return WAIT_OBJECT_0;
		}
		if (timeout < 0)
			timeout = INT32_MAX;
		// Sleep Loop
		while (true) {
			for (auto i = 0u; i < modules.size(); ++i) {
				auto& module = *(modules.begin() + i);
				if (!signaled[i] && GetModuleHandle(data(module)) != NULL) {
					bool done = signaled[i] = true;
					for (auto j = 0u; j < modules.size(); ++j) {
						if (!signaled[j]) {
							done = false;
							break;
						}
					}
					if (done) {
						success = true;
						goto exit;
					}
				}
			}
			// Escape Loop
			if (totalSlept > uint32_t(timeout)) {
				break;
			}; Sleep(10); totalSlept += 10;
		}
	exit:
		return success ? WAIT_OBJECT_0 : WAIT_TIMEOUT;
	}
	void EnableConsole()
	{
		//Save Old Handles
		old.err = GetStdHandle(STD_ERROR_HANDLE);
		old.out = GetStdHandle(STD_OUTPUT_HANDLE);
		old.in = GetStdHandle(STD_INPUT_HANDLE);
		//Enable Console
		::AllocConsole() && ::AttachConsole(GetCurrentProcessId());
		BindCrtHandlesToStdHandles(true, true, true);
		//New Handles
		now.err = GetStdHandle(STD_ERROR_HANDLE);
		now.out = GetStdHandle(STD_OUTPUT_HANDLE);
		now.in = GetStdHandle(STD_INPUT_HANDLE);
		// Output Settings
		SetConsoleMode(now.out,
			ENABLE_PROCESSED_OUTPUT | ENABLE_WRAP_AT_EOL_OUTPUT);
		// Input Settings
		SetConsoleMode(now.in,
			ENABLE_INSERT_MODE | ENABLE_EXTENDED_FLAGS |
			ENABLE_PROCESSED_INPUT | ENABLE_QUICK_EDIT_MODE);
		// Finally Set Title
		SetConsoleTitle("[4-HO-MiPT] Console Window");
	}
	void DisableConsole()
	{
		// Free Console
		if (now.err && now.out && now.in)
			FreeConsole();
		// Free Handles
		if (old.err)
			SetStdHandle(STD_ERROR_HANDLE, old.err);
		if (old.out)
			SetStdHandle(STD_OUTPUT_HANDLE, old.out);
		if (old.in)
			SetStdHandle(STD_INPUT_HANDLE, old.in);
	}
	void BindCrtHandlesToStdHandles(bool bindStdIn, bool bindStdOut, bool bindStdErr)
	{
		// Re-initialize the C runtime "FILE" handles with clean handles bound to "nul". We do this because it has been
		// observed that the file number of our standard handle file objects can be assigned internally to a value of -2
		// when not bound to a valid target, which represents some kind of unknown internal invalid state. In this state our
		// call to "_dup2" fails, as it specifically tests to ensure that the target file number isn't equal to this value
		// before allowing the operation to continue. We can resolve this issue by first "re-opening" the target files to
		// use the "nul" device, which will place them into a valid state, after which we can redirect them to our target
		// using the "_dup2" function.
		if (bindStdIn)
		{
			FILE* dummyFile;
			freopen_s(&dummyFile, "nul", "r", stdin);
		}
		if (bindStdOut)
		{
			FILE* dummyFile;
			freopen_s(&dummyFile, "nul", "w", stdout);
		}
		if (bindStdErr)
		{
			FILE* dummyFile;
			freopen_s(&dummyFile, "nul", "w", stderr);
		}
		// Redirect unbuffered stdin from the current standard input handle
		if (bindStdIn)
		{
			HANDLE stdHandle = GetStdHandle(STD_INPUT_HANDLE);
			if (stdHandle != INVALID_HANDLE_VALUE)
			{
				int fileDescriptor = _open_osfhandle((intptr_t)stdHandle, _O_TEXT);
				if (fileDescriptor != -1)
				{
					FILE* file = _fdopen(fileDescriptor, "r");
					if (file != NULL)
					{
						int dup2Result = _dup2(_fileno(file), _fileno(stdin));
						if (dup2Result == 0)
						{
							setvbuf(stdin, NULL, _IONBF, 0);
						}
					}
				}
			}
		}
		// Redirect unbuffered stdout to the current standard output handle
		if (bindStdOut)
		{
			HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
			if (stdHandle != INVALID_HANDLE_VALUE)
			{
				int fileDescriptor = _open_osfhandle((intptr_t)stdHandle, _O_TEXT);
				if (fileDescriptor != -1)
				{
					FILE* file = _fdopen(fileDescriptor, "w");
					if (file != NULL)
					{
						int dup2Result = _dup2(_fileno(file), _fileno(stdout));
						if (dup2Result == 0)
						{
							setvbuf(stdout, NULL, _IONBF, 0);
						}
					}
				}
			}
		}
		// Redirect unbuffered stderr to the current standard error handle
		if (bindStdErr)
		{
			HANDLE stdHandle = GetStdHandle(STD_ERROR_HANDLE);
			if (stdHandle != INVALID_HANDLE_VALUE)
			{
				int fileDescriptor = _open_osfhandle((intptr_t)stdHandle, _O_TEXT);
				if (fileDescriptor != -1)
				{
					FILE* file = _fdopen(fileDescriptor, "w");
					if (file != NULL)
					{
						int dup2Result = _dup2(_fileno(file), _fileno(stderr));
						if (dup2Result == 0)
						{
							setvbuf(stderr, NULL, _IONBF, 0);
						}
					}
				}
			}
		}
		// Clear the error state for each of the C++ standard stream objects. We need to do this, as attempts to access the
		// standard streams before they refer to a valid target will cause the iostream objects to enter an error state. In
		// versions of Visual Studio after 2005, this seems to always occur during startup regardless of whether anything
		// has been read from or written to the targets or not.
		if (bindStdIn)
		{
			std::wcin.clear();
			std::cin.clear();
		}
		if (bindStdOut)
		{
			std::wcout.clear();
			std::cout.clear();
		}
		if (bindStdErr)
		{
			std::wcerr.clear();
			std::cerr.clear();
		}
	}
	void ClearConsole(char fill = ' ')
	{
		COORD tl = { 0,0 };
		CONSOLE_SCREEN_BUFFER_INFO s;
		GetConsoleScreenBufferInfo(now.out, &s);
		DWORD written, cells = s.dwSize.X * s.dwSize.Y;
		FillConsoleOutputCharacter(now.out, fill, cells, tl, &written);
		FillConsoleOutputAttribute(now.out, s.wAttributes, cells, tl, &written);
		SetConsoleCursorPosition(now.out, tl);
	}
	char ConsoleReadKey()
	{
		// Console Inactive
		if (!now.in)
			return false;
		// Get KeyPress
		auto key = char{ 0 };
		auto keysread = DWORD{ 0 };
		ReadConsole(now.in, &key, 1, &keysread, nullptr);
		return key;
	}
};