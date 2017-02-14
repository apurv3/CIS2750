/*==========================================================================

Example using mySQL 

==========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

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
	//printf("%s\n%s\n",msg,mysql_error(mysql));
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


int main(int argc, char *argv[]) {

	MYSQL mysql;
	MYSQL_RES *res;
	MYSQL_ROW row;
	MYSQL_FIELD *field;
	char query[MAX_QUERY];
	int x;
	int i = 0;

	if(argv[1] == NULL)
	{
		return(0);
	}


	//printf("connecting...\n");
	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "mydb");
	if (!mysql_real_connect(&mysql, HOSTNAME, USERNAME, PASSWORD,
		DATABASE, 0, NULL, 0)) {
	   error("Could not connect to host.",&mysql);
	}


	if(strcmp(argv[1],"-reset")==0)
	{
	
		strcpy(query, "DROP TABLE students");

		if(mysql_query(&mysql,query))
	  		error("fail drop 1",&mysql);
	  	printf("Table is deleted\n");
	  	clrstr(query);
	}

	else if(strcmp(argv[1],"-clear")==0)
	{
		strcpy(query,"DELETE FROM students;");
		if(mysql_query(&mysql,query))
	  		error("fail drop 1",&mysql);
		printf("Removed all the rows\n");
		clrstr(query);

	}
	
	else if(strcmp(argv[1],"-show")==0)
	{
		strcpy(query, "select filename, fileSize, dateTime from students order by filename");
	
		if(mysql_query(&mysql, query))
		  error("failed select 1",&mysql);		
		/*
			Store results from query into res structure.
		*/	
		if (!(res = mysql_store_result(&mysql)))
		{
			error("failed store 1",&mysql);
		}
	
		while ((row = mysql_fetch_row(res))) 
		{
			printf("%s %s %s\n", row[0],row[1],row[2]);
		}
		mysql_free_result(res);

	}
	else if(strcmp(argv[1],"-help")==0)
	{
		printf("When used with the -clear flag (e.g. db -clear) the program removes all of the rows from the tables in the database.\n");
		printf("When used with the -reset flag the program deletes the tables from the database.\n");
		printf("When used with the -show flag the program prints out the name, length,and date for all files stored in the database.\n");
		//mysql_free_result(res);
		mysql_close(&mysql);
		mysql_library_end();
		return(0);
	}
	else
	{
		
		return(0);
	}
	mysql_close(&mysql);
	mysql_library_end();
	return(0);
}
