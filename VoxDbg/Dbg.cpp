#include "Dbg.h"

namespace Vox
{
	HANDLE Dbg::hProc;
	DWORD Dbg::pid;
	std::vector<Module> Dbg::modules;
	ProcessMode Dbg::mode;
	bool Dbg::CPUTabOpen;
	bool Dbg::ModuleTabOpen;

	Dbg::Dbg()
	{
		mode = None;
	}

	void Dbg::ClearModules()
	{
		for (int i = 0; i < modules.size(); i++)
		{
			if (modules[i].data != NULL)
			{
				free(modules[i].data);
				modules[i].data = NULL;
			}
		}
		modules.clear();
	}

	void Dbg::Init()
	{
		if (hProc) CloseHandle(hProc);
		mode = None;
		ClearModules();
		hProc = NULL;
		CPUTabOpen = ModuleTabOpen = false;
	}

	bool Dbg::StartDebugging()
	{
		DebugActiveProcess(pid);
		return true;
	}

	void Dbg::StopDebugging()
	{
		DebugActiveProcessStop(pid);
	}

	bool Dbg::AttachToProcess(DWORD pid)
	{
		Dbg::pid = pid;
		hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
		
		mode = Attach;

		if (!hProc)
		{
			printf("Failed to open process\n");
			return false;
		}

		return true;
	}

	char* Dbg::ModuleNameFromPath(wchar_t* name)
	{
		int len = wcslen(name);
		int i;
		for (i = len - 1; i >= 0; i--)
		{
			if (name[i] == '\\') break;
		}
		char ret[MAX_PATH];
		wcstombs(ret, name + i + 1, MAX_PATH);
		return ret;
	}

	void* Dbg::RPM(DWORD addy, DWORD num)
	{
		if (!hProc) return NULL;
		void* buf = malloc(num);
		SIZE_T ret;
		ReadProcessMemory(hProc, (LPCVOID)addy, buf, num, &ret);
		return buf;
	}

	void Dbg::RPM(DWORD addy, DWORD num, void* dst)
	{
		if (!hProc) return;
		SIZE_T ret;
		ReadProcessMemory(hProc, (LPCVOID)addy, dst, num, &ret);
	}

	char* Dbg::WideToMulti(wchar_t* str)
	{
		char buf[1024];
		wcstombs(buf, str, wcslen(str));
		buf[wcslen(str)] = 0;
		return buf;
	}

	char* Dbg::MakeString(char* fmt, ...)
	{
		va_list args;
		char buf[1024];
		va_start(args, fmt);
		vsprintf(buf, fmt, args);
		va_end(args);
		return buf;
	}

	bool Dbg::EnumModules()
	{
		ClearModules();
		HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
		MODULEENTRY32 me32;
		me32.dwSize = sizeof MODULEENTRY32;
		if (!Module32Next(hSnap, &me32))
		{
			return false;
		}
		do
		{
			modules.push_back(Module(me32));

			int idx = modules.size() - 1;

			DWORD base = (DWORD)me32.modBaseAddr;

			//http://pastebin.com/DKmyLuWj

			//Read in DOS header to get a ptr to the NT headers
			RPM(base, sizeof _IMAGE_DOS_HEADER, &modules[idx].dos_header);
			if (modules[idx].dos_header.e_magic == IMAGE_DOS_SIGNATURE)
			{
				LPBYTE addy = (LPBYTE)base + modules[idx].dos_header.e_lfanew;
				RPM((DWORD)addy, sizeof IMAGE_NT_HEADERS, &modules[idx].nt_header);
				if (modules[idx].nt_header.Signature == IMAGE_NT_SIGNATURE)
				{
					//Valid NT header
					//If it ain't here, Probably a module who detroyed the headers after injection / running
				}
			}
			modules[idx].data = (BYTE*)malloc(me32.modBaseSize);

			RPM(base, me32.modBaseSize, modules[idx].data);

		} while ( Module32Next(hSnap, &me32) );
		return true;
	}

	Dbg::~Dbg()
	{
	}
};