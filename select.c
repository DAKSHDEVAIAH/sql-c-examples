#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h> 

static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
   for(i = 0; i<argc; i++){
	printf("%s",argv[i] ? argv[i] : "NULL");
	if (i != argc-1 ){
 		printf( "|" );	
   	}
   }
   
   printf("\n");
   return 0;
}

int main(int argc, char* argv[]) {
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char *sql;
   const char* data = "";

   if (argc == 1){
        printf("\nNo Extra Command Line Argument Passed "
               "Other Than Program Name");
   } 
   if (argc >= 2){
       /* Open database */
       rc = sqlite3_open("test.db", &db);
       
       if( rc ) {
          fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
          return(0);
       } else {
          fprintf(stderr, "Opened database successfully\n");
       }
    
       /* Create SQL statement */
        strcpy(sql,argv[1]);
       //sql = "SELECT * from ZACKS_SNP WHERE RANK LIKE 'STRONG BUY' ";
    
       /* Execute SQL statement */
       rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
       
       if( rc != SQLITE_OK ) {
          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
       } else {
          fprintf(stdout, "Operation done successfully\n");
       }
       sqlite3_close(db);
       return 0;
    }
}
