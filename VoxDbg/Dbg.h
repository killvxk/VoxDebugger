#ifndef _VOXDBG_H_
#define _VOXDBG_H_

#define WIN32_LEAN_AND_MEAN
#define BEA_ENGINE_STATIC
#define BEA_USE_STDCALL

#include <Windows.h>
#include "BeaEngine.h"
#include <TlHelp32.h>
#include "Psapi.h"
#include <cstdio>
#include <vector>
#include <varargs.h>
#include <winnt.h>
#include "Winternl.h"
#include "WinBase.h"
//#include "ntundoc.h"

//#define FIELD_OFFSET(a, b) offsetof(a, b)

typedef struct {
	PIMAGE_NT_HEADERS headers;
	unsigned char *codeBase;
	HMODULE *modules;
	int numModules;
	int initialized;
} MEMORYMODULE, *PMEMORYMODULE;



namespace Vox
{
	enum ProcessMode
	{
		None = 0,
		Attach,
		File,
	};

	struct Module
	{
		MODULEENTRY32 me32;
		_IMAGE_DOS_HEADER dos_header;
		IMAGE_NT_HEADERS nt_header;
		BYTE* data;
		Module(MODULEENTRY32 me32) : me32(me32)
		{
			data = NULL;
		}
	};

	class Dbg
	{
	public:
		Dbg();
		~Dbg();
		static HANDLE hProc;
		static DWORD pid;
		static std::vector<Module> modules;
		static bool ModuleTabOpen;
		static bool CPUTabOpen;

		static ProcessMode mode;
		static bool AttachToProcess(DWORD pid);
		static bool StartDebugging();
		static void StopDebugging();
		static void ClearModules();
		static void Init();
		static bool EnumModules();
		static char* ModuleNameFromPath(wchar_t * name);
		static char* WideToMulti(wchar_t* wide);
		static char* MakeString(char* fmt, ...);
		static void* RPM(DWORD addy, DWORD num);
		static void RPM(DWORD addy, DWORD num, void* ptr);
	};
};


#endif