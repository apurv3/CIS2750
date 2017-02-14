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
	
	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "mydb");
	if (!mysql_real_connect(&mysql, HOSTNAME, USERNAME, PASSWORD,
		DATABASE, 0, NULL, 0)) {
	   error("Could not connect to host.",&mysql);
	}

	strcpy(query, "select filename from students order by filename");
	
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
			printf("%s", row[0]);
			printf("\n");
		}

	mysql_free_result(res);
	mysql_close(&mysql);
	mysql_library_end();

return(0);
}