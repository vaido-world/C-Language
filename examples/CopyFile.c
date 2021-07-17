// NEEDS ADMINISTRATOR PRIVILEGIES EVERYWHERE to copy anything.
// Checks for a .txt file in the current directory and copy into the speicfied named file in a directory.
// ERRORS to check: https://docs.microsoft.com/en-us/windows/win32/debug/system-error-codes--0-499-
//  Source: https://www.easefilter.com/kb/fileapi-copyfile.htm
// Reference: https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-copyfile

#include <windows.h>  
#include <tchar.h>  
#include <stdio.h>  

void _tmain(int argc, TCHAR* argv[])  
{     
	WIN32_FIND_DATA FileData;     
	HANDLE          hSearch;     
	DWORD           dwAttrs;     
	TCHAR           szNewPath[MAX_PATH];           
	BOOL            fFinished = FALSE;       

	if(argc != 2)     
	{       
		_tprintf(TEXT("Usage: %s <dir>\n"), argv[0]);        
		return;    
	}     

	// Create a new directory.         

	if (!CreateDirectory(argv[1], NULL))      
	{         
		printf("CreateDirectory failed (%d)\n", GetLastError());         
		return;     
	}      

	// Start searching for text files in the current directory.         

	hSearch = FindFirstFile(TEXT("*.txt"), &FileData);      
	if (hSearch == INVALID_HANDLE_VALUE)      
	{         
		printf("No text files found.\n");         
		return;     
	}      

	// Copy each .TXT file to the new directory   
	// and change it to read only, if not already.         

	while (!fFinished)      
	{         
       
	   

	   
		
		if (CopyFile(FileData.cFileName, TEXT("C:\\Users\\Juozas\\Desktop\\cygwin\\cygwins\\test.txt"), FALSE))        
		{            
			dwAttrs = GetFileAttributes(FileData.cFileName);            
			if (dwAttrs==INVALID_FILE_ATTRIBUTES) 
				return;              

			if (!(dwAttrs & FILE_ATTRIBUTE_READONLY))            
			{               
				SetFileAttributes(szNewPath,                   
					dwAttrs | FILE_ATTRIBUTE_READONLY);            
			}         
		}        
		else         
		{            
			printf("Could not copy file ERROR_PATH_NOT_FOUND (%d)\n", GetLastError()); 
			printf(szNewPath);
			printf(FileData.cFileName);
			printf("Could not copy file.\n");            
			return;        
		}            

		if (!FindNextFile(hSearch, &FileData))         
		{           
			if (GetLastError() == ERROR_NO_MORE_FILES)            
			{               
				_tprintf(TEXT("Copied *.txt to %s\n"), argv[1]);               
				fFinished = TRUE;           
			}            
			else            
			{               
				printf("Could not find next file.\n");               
				return;           
			}         
		}     
	}      
	// Close the search handle.         

	FindClose(hSearch);  
}       
        