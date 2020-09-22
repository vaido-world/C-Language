#include <windows.h>

// Refrence: https://docs.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-reggetvaluea




// Main function for retrieving Registered Owner Name of Windows Operating system.
void main(){
	char value[255];
	
	#define BUFFER  8192
	DWORD BufferSize = BUFFER;
	
	HKEY    hkey     = HKEY_LOCAL_MACHINE;
	LPCSTR  lpSubKey = "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion";
	LPCSTR  lpValue  = "RegisteredOwner";
	DWORD   dwFlags  = RRF_RT_ANY;
	LPDWORD pdwType  = NULL;
	PVOID   pvData   = &value;
	LPDWORD pcbData  = ;
	
	RegGetValueA(
		hkey,
		lpSubKey,
		lpValue,
		dwFlags,
		pdwType,
		pvData,
		pcbData
	);
	
	printf("\n%s\n", value);
	return 0;
}

//https://forum.qt.io/topic/86496/unresolved-external-symbol-getregvaluea

//https://stackoverflow.com/questions/59016114/reggetvalue-header-winreg-h-not-working-in-c
