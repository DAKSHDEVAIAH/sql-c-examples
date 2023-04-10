#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sqlite3.h>
 
static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}
// C program to illustrate
// command line arguments
int main(int argc, char* argv[])
{

	if (argc == 1)
		printf("\nNo Extra Command Line Argument Passed "
			"Other Than Program Name");

	if (argc >= 2) {
		printf("Argument passed is : %s\n", argv[1]);
	}
	return 0;
}

