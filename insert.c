#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sqlite3.h>
 
static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}
int main(int argc, char* argv[])
{
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char *sql;
 /* Open database */
    rc = sqlite3_open("test.db", &db);

    if( rc ) {
       printf("Can't open database: %s\n", sqlite3_errmsg(db));
       return(0);
    } 
    else {
       printf("Opened database successfully\n");
    }
   if (argc == 1){
        printf("\nNo Extra Command Line Argument Passed Other Than Program Name");
	return 1;
    } 
    char str[500];
    char sqlstr[500];
    float price;
    FILE *fp;
    if (argc >= 2) {
	for (int i = 0; i < argc; i++){
        	//printf("\nargv[%d]: %s", i, argv[i]);
	}
    }
    fp = fopen(argv[1], "r");
    if(fp == NULL)
    {
        //printf("Error opening file\n");
        exit(1);
    }

    while( fgets(str, 500, fp) != NULL )
    {
	str[strlen(str)-1]='\0';
	char *token = strtok(str, ",");
	char *datet = token;
       	token = strtok(NULL, ",");
	char *namet = token;
       	token = strtok(NULL, ",");
	char *symbolt = token;
       	token = strtok(NULL, ",");
	char *pricet = token;
	price= atof(pricet);		
       	token = strtok(NULL, ",");
	char *rankt = token;
       	token = strtok(NULL, ",");
	//sprintf(sqlstr,"INSERT INTO ZACKS_SNP (DATE,STOCK_NAME,STOCK_SYMBOL,STOCK_PRICE,RANK)  VALUES (\"%s,%s,%s,%f,%s\",datet,namet,symbolt,price,rankt);");
	sprintf(sqlstr,"%s%s,%s,%s,%.2f,%s%s","INSERT INTO ZACKS_SNP (DATE,STOCK_NAME,STOCK_SYMBOL,STOCK_PRICE,RANK) VALUES(",datet,namet,symbolt,price,rankt,");");
        //printf("%s\n", sqlstr);
  	sql =sqlstr; 
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   
        if( rc != SQLITE_OK ){
           printf("SQL error: %s\n", zErrMsg);
           sqlite3_free(zErrMsg);
        }
    }
        fprintf(stdout, "Records created successfully\n");
        sqlite3_close(db);
        return 0;
}
