int printf(const char *format, ...); 

void main(int argc, char *argv[]){
char scheduleArgument[]  = "\0";
int index=0;
for (index; index<argc; index++){
	if (scheduleArgument == ""){ printf("yes");}
	if (argv[index][0] == '-'){
		char scheduleArgument[]  = "\0";
		printf(" %i, %c\n", index, argv[index][0]);
	}
}

printf( "Hello World \n" ); 

}
