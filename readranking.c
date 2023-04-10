#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void removeLeading(char *stra, char *strb)
{
    int idx = 0, j, k = 0;
 
    // Iterate String until last
    // leading space character
    while (stra[idx] == ' ' || stra[idx] == '\t' || stra[idx] == '\n')
    {
        idx++;
    }
 
    // Run a for loop from index until the original
    // string ends and copy the content of str to str1
    for (j = idx; stra[j] != '\0'; j++)
    {
        strb[k] = stra[j];
        k++;
    }
 
    // Insert a string terminating character
    // at the end of new string
    strb[k] = '\0';
 
    // Print the string with no whitespaces
}
 

char* replaceWord(const char* s, const char* oldW,
                const char* newW)
{
    char* result;
    int i, cnt = 0;
    int newWlen = strlen(newW);
    int oldWlen = strlen(oldW);
 
    // Counting the number of times old word
    // occur in the string
    for (i = 0; s[i] != '\0'; i++) {
        if (strstr(&s[i], oldW) == &s[i]) {
            cnt++;
 
            // Jumping to index after the old word.
            i += oldWlen - 1;
        }
    }
 
    // Making new string of enough length
    result = (char*)malloc(i + cnt * (newWlen - oldWlen) + 1);
 
    i = 0;
    while (*s) {
        // compare the substring with the result
        if (strstr(s, oldW) == s) {
            strcpy(&result[i], newW);
            i += newWlen;
            s += oldWlen;
        }
        else
            result[i++] = *s++;
    }
 
    result[i] = '\0';
    return result;
}
 
int main(int argc, char* argv[])
{
 if (argc == 1){
        printf("\nNo Extra Command Line Argument Passed Other Than Program Name");
	return 1;
    } 
    char str[500];
    char symbolstr[50];
    char datestr[50];
    char namestr[100];
    float price;
    char rankstr[50];
    *symbolstr='\0';
    *datestr='\0';
    *namestr='\0';
    *rankstr='\0';
    FILE *fp;
    char *ptr;
    int rankflag=0;
    char* result = NULL;
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

//    printf("Testing fgets() function: \n\n");
//   printf("Reading contents of A.dat: \n\n");

  //  while( fgets(str, 500, fp) != NULL )
   // {
//	str[strlen(str)-1]='\0';
//	printf("%s \n",str);
 //   }
//	return 1;
    while( fgets(str, 500, fp) != NULL )
    {
	str[strlen(str)-1]='\0';
//	printf("%s",str);
	if((ptr = strstr(str, "\"to_date\""))!=NULL){
		result = replaceWord(str, "\"to_date\"","");
		result = replaceWord(result, "\"hidden\"","");
		result =replaceWord(result,"input type","");
		result =replaceWord(result,"value","");
		result =replaceWord(result,"class","");
		result =replaceWord(result,"=","");
		result =replaceWord(result,"<","");
		result =replaceWord(result,"/>","");
		result =replaceWord(result," ","");
		result =replaceWord(result, "\"","");
		strcpy(datestr,result);
	}
	if((ptr = strstr(str, "\"last_price\""))!=NULL){
		result =replaceWord(str, "\"last_price\"","");
		result =replaceWord(result,"span","");
		result =replaceWord(result,"USD","");
		result =replaceWord(result,"p","");
		result =replaceWord(result,"class","");
		result =replaceWord(result,"=","");
		result =replaceWord(result,",","");
		result =replaceWord(result,"<","");
		result =replaceWord(result,">","");
		result =replaceWord(result,"$","");
		result =replaceWord(result,"/","");
		sscanf(result, "%f", &price);
		
	}
	if((ptr = strstr(str, "Earnings Announcement"))!=NULL){
		result =replaceWord(str,"Earnings","");
		result =replaceWord(result,"Announcement","");
		result =replaceWord(result,"name","");
		result =replaceWord(result,":","");
		result =replaceWord(result,",","");
		result =replaceWord(result, "\"","");
		strcpy(namestr,result);
	}
	if((ptr = strstr(str, "var _ticker_string"))!=NULL){
		result =replaceWord(str,"var","");
		result =replaceWord(result,"_","");
		result =replaceWord(result,"=","");
		result =replaceWord(result,"'","");
		result =replaceWord(result,";","");
		result =replaceWord(result,"tickerstring","");
		strcpy(symbolstr,result);
	}
#if 0	
	if((ptr = strstr(str, "/title"))!=NULL){
		result =replaceWord(str,"title","");
		result =replaceWord(str,symbolstr,"");
		result =replaceWord(result,"Stock Price Today","");
		result =replaceWord(result,"Zacks","");
		result =replaceWord(result,"/","");
		result =replaceWord(result,"<","");
		result =replaceWord(result,">","");
		result =replaceWord(result,"-  -","");
		result =replaceWord(result,"-","		");
		strcpy(namestr,result);
	}
#endif
	if((ptr = strstr(str, "1-Strong Buy"))!=NULL){
		strcpy(rankstr,"Strong Buy");
		rankflag=1;
	}
	else if((ptr = strstr(str, "2-Buy"))!=NULL){
		strcpy(rankstr,"Buy");
		rankflag=1;
	}
	else if((ptr = strstr(str, "3-Hold"))!=NULL){
		strcpy(rankstr,"Hold");
		rankflag=1;
	}
	else if((ptr = strstr(str, "4-Sell"))!=NULL){
		strcpy(rankstr,"Sell");
		rankflag=1;
	}
	else if((ptr = strstr(str, "5-Strong Sell"))!=NULL){
		strcpy(rankstr,"Strong Sell");
		rankflag=1;
	}
    	else if(rankflag==0){
	strcpy(rankstr,"No Rank");
    	}	
    }
    removeLeading(datestr, datestr);
    removeLeading(namestr, namestr);
    removeLeading(symbolstr,symbolstr);
    removeLeading(rankstr, rankstr);
    printf("\"");
    printf("%s\",",datestr);
    printf("\"%s\",",namestr);
    printf("\"%s\",",symbolstr);
    printf("%.2f,",price);
    printf("\"%s\" \n",rankstr);
    fclose(fp);
    return 0;
}
