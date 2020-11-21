#include <stdio.h>

int main(int argc, char* argv[])
{
    char const* const fileName = "C:\\Users\\Juozas\\Desktop\\test.c"; /* should check that argc > 1 */
    FILE* file = fopen(fileName, "r"); /* should check the result */
    char line[256];

    while (fgets(line, sizeof(line), file)) {
        /* note that fgets don't strip the terminating \n, checking its
           presence would allow to handle lines longer that sizeof(line) */
		
			printf(&line[0]);
		
       // printf("%s", line); 
    }
    /* may check feof here to make a difference between eof and io failure -- network
       timeout for instance */

    fclose(file);

    return 0;
}