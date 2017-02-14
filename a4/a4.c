#include "listio.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <mysql/mysql.h>
#include <time.h>



#define MAX_QUERY 512
#define HOSTNAME  "dursley.socs.uoguelph.ca"
/*
	HOSTNAME can be defined with IP or hostname.

	eg: #define HOSTNAME "131.104.49.147"
	    #define HOSTNAME "gradpc-38.cis.uoguelph.ca"
	
*/

#define USERNAME  "aagarwal"
#define PASSWORD  "0832983"
#define DATABASE  "aagarwal"


/*
	standard error clause.
*/
void error(char *msg, MYSQL *mysql){
	printf("%s\n%s\n",msg,mysql_error(mysql));
	mysql_close(mysql);
	mysql_library_end();
	exit(1);
}

/*
	clear the contents of an array of char's
*/
void clrstr(char *buf){
	buf[0] = '\0';
}


int main(int argc, char*argv[])
{
	
	struct returnStruct *hdr;
	FILE *fp;
	char*filename;
	char *filename2;
	int c;
	int len;
	char buff[100];
	char *sqlInsert;
	char dateTime[30];
	char *fc;
	time_t rawtime;
  	struct tm * timeinfo;

  	time ( &rawtime );
  	timeinfo = localtime ( &rawtime );


	MYSQL mysql;
	MYSQL_RES *res;
	MYSQL_ROW row;
	MYSQL_FIELD *field;
	char query[MAX_QUERY];
	int x;
	int i = 0;


	//if the user puts an arugment
	if(argc == 2)
	{
		//filename = malloc(sizeof(char)*strlen(argv[1])+5);
		filename = calloc(strlen(argv[1])+6, sizeof(char));
		filename = strcat(filename,argv[1]);
		filename = strcat(filename,".html");
		printf("%s\n",filename);
		if (access(filename,F_OK)!= -1)
		{
			fp = fopen (filename,"r");
			while((c = getc(fp)) != EOF)
			{
			    printf("%c",c);
			}
			fclose(fp);
			free(filename);
			return(0);
		}	
		else //no file in HTML
		{
			//printf("NO FILE IN HTML\n"); //filename without extention exists
			if (access(argv[1],F_OK)!= -1) //check if there is a file without extention
			{
				
				hdr = buildHeader();
				setName(hdr->header,argv[1]);
				fp = fopen(argv[1],"r");
				fseek(fp,0,SEEK_END);
				len = (int)ftell(fp);
				fclose(fp);
		
				fp = fopen(argv[1],"r");
				while (fgets(buff,1024,fp) != '\0')
				{
					addString(hdr->header,buff);
				}
				fclose(fp);
				processStrings(hdr->header);
				printString(hdr->header);
				freeStructure(hdr->header);
				freeSecondStruct(hdr);
				free(filename);
				return(0);
			}
			else //file in HTML does not exist
			{
				printf("File does not exist at all\n");
				free(filename);
				return(0);
			}
		}	
	
	}
	if(argc == 3) //3 arguments, need this to send the server stuff for 2750 
	{
		
		strcpy(dateTime,asctime (timeinfo));
		filename2 = calloc(strlen(argv[1])+6, sizeof(char));
		filename2 = strcpy(filename2,argv[1]);
		filename2 = strcat(filename2,".html");
		if (access(filename2,F_OK)!= -1)
		{
			char string[100];
			char string2[100000];
			for(i=0;i<=strlen(argv[1])-6;i++)
			{
				string[i] = argv[1][6+i];
				//./files/
			}
			fp = fopen(filename2,"rb");
			fseek(fp, 0, SEEK_END);
			long fsize = ftell(fp);
			fseek(fp, 0, SEEK_SET);  //same as rewind(f);
			fc = malloc(fsize+1);
			fread(fc, fsize, 1, fp);
			fclose(fp);
			fc[fsize] = 0;
		
			//printf("connecting...\n");
			mysql_init(&mysql);
			mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "mydb");
			if (!mysql_real_connect(&mysql, HOSTNAME, USERNAME, PASSWORD,DATABASE, 0, NULL, 0)) {
				free(filename2);
				free(fc);
				//free(sqlInsert);
		   		error("Could not connect to host.",&mysql);
		   	}


			
			clrstr(query);
			strcat(query, "create table if not exists students (filename char(255),");
			strcat(query,"fileContent TEXT,");
			strcat(query, "fileSize int,");
			strcat(query, "dateTime char(30),");
			strcat(query, "primary key(filename) )");
			
			printf("Creating students table.\n");
			/*
				Create students table
			*/
			if(mysql_query(&mysql, query)){
			 	clrstr(query);
			 	free(filename2);
			 	free(fc);
			 	//free(sqlInsert);
				error("Could not create table!",&mysql);
			}
			clrstr(query);
			mysql_real_escape_string(&mysql,string2,fc,strlen(fc));
			sqlInsert = malloc(sizeof(char)*(strlen(string)+strlen(fc)+strlen(dateTime))+100);
		    sprintf(sqlInsert,"insert into students values ('%s','%s','%d','%s')",string,string2,fsize,dateTime);
			char *records[] = {
				sqlInsert
			};
			
			for(x = 0; x < 1; x++){
				if(mysql_query(&mysql, records[x])){
					printf("Failure to insert: %s\n",records[x]);
					free(filename2);
					free(fc);
					free(sqlInsert);
					error("Could not insert record",&mysql);

				}
			}
			clrstr(query);
			free(fc);
			mysql_close(&mysql);
			mysql_library_end();
			free(filename2);
			free(sqlInsert);
			return(0);
		}
		else
		{
			free(filename2);
			return(0);
		}
		
	}
	else
	{
		return(0); //no argument, so just forcequit
	}

	return(0);
	
}
