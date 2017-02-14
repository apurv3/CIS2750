#include "listio.h"

struct returnStruct *buildHeader()
{
    struct returnStruct *rs = malloc(sizeof(struct returnStruct));

    rs->header = malloc(sizeof(struct dataHeader));
    rs->header->name = NULL;
    rs->header->length = 0; 
    rs->header->next=NULL;   
    return(rs);
}
//Allocates ad sets the name string in the a dataHeader strcuture 
int setName(struct dataHeader *header, char *name)
{
 
    header->name = malloc((sizeof(char)* strlen(name))+1);
    strcpy(header->name,name);
    header->length += strlen(name);
    getName(header);
    return(1);
}

//returns a pointer to the name strign int he dataheader structure 
char *getName(struct dataHeader *header)
{
    return(header->name);
}

//returns the integer value stored in the length variable in the dataHeader structure 
int getLength(struct dataHeader *header)
{
    return(header-> length);
}

//useful for debbing the list, it will print out all the strings
int printString(struct dataHeader *header)
{
    struct dataString *temp;

    temp= header->next;
    printf("%s\n",header->name);
    //printf("%d\n",header->length);
    while(temp != NULL)
    {
        printf("%s\n",temp->string);
        //printf("%d\n",strlen(temp->string));
        temp=temp->next;
    }

	return(1);
}

int addString(struct dataHeader *header, char *str)
{
    
    struct dataString *temp; //= malloc(sizeof(struct dataHeader)+sizeof(struct dataHeader*));
       
 //first time this function is being called
    //add the dataString struct directly to the *next pointer in the header
    if(header->next == NULL)
    {
        header->next = malloc(sizeof(struct dataString));
        header->next->string = malloc(sizeof(char)*strlen(str)+1);
        header->next->next = NULL;
        strcpy(header->next->string,str);
    }
    //you must always traverse the linked list of dataString structures
    //until you reach the end (when the next pointer is equal to NULL) and then you
    //can allocate a new dataString structure and copy the string into that new
    //structure.
    else
    {
        temp=header->next;
        while(temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = malloc(sizeof(struct dataString));
        temp->next->string = malloc(sizeof(char)*strlen(str)+1);
        temp->next->next = NULL;
        strcpy(temp->next->string,str);
    }
    return(1);
}

int processStrings(struct dataHeader *header)
{
    struct dataString *temp;
    char *run;
    char *compile;
    FILE *fp;
    fp = fopen(header->name,"w");
    temp= header->next;
   
    int i = 0;
    
    while(temp != NULL)
    {
		for(i = 0; i < (int) strlen(temp->string);i++)
        {
            if(temp->string[i] == ' ' && temp->string[i+1] == ' ')
            {
                temp->string = spaceTab(temp->string);
              
            }
            if(temp->string[i] == '\t' && temp->string[i+1] == '\t')
            {
                temp->string = spaceTab(temp->string);
                
            }
            if(temp->string[i] == '\n')
            {
                temp->string = lineBreakCarriage(temp->string);
                
            }
            if(temp->string[i] == '\r')
            {
                temp->string = lineBreakCarriage(temp->string);
                
            }

        }
        fprintf(fp,temp->string);
        header->length += strlen(temp->string);      
        temp=temp->next;
    }
    fclose(fp);
    compile = malloc(sizeof(char)*1024);
    run = malloc(sizeof(char)*1024);
    strcpy(compile,"chmod -x a4.py");
    strcpy(run,"python3 a4.py ");
    strcat(run,header->name);
    fp = popen(compile,"w");
    pclose(fp);
    fp = popen(run,"w");
    pclose(fp);
    free(run);
    free(compile);
	return(1);
}

char * spaceTab(char*string)
{
    int t = 0;
    int c = 0;
    int d = 0;
    char *tempString;
    tempString = malloc(sizeof(char)*strlen(string)+1); 
    while(*(string+c) != '\0'){
            if (*(string+c) == ' '||*(string+c) == '\t'){
                t = c+1;
                if((*(string+t) == ' '||(*(string+t)) == '\t' )&& *(string + t) != '\0'){
                    while((*(string+t) == ' '||*(string+t) == '\t') && *(string+t) != '\0'){
                        if((*(string+t) == ' ')|| (*(string+t) == '\t')){
                            c++;
                        }
                        t++;
                    }
                }
            }
            *(tempString+d) = *(string+c);
            c++;
            d++;
        }
        *(tempString+d) = '\0';
        free(string);
    return(tempString);
}

char *lineBreakCarriage(char*string)
{
    int c = 0;
    int j= 0;
    int h = 0;
    char *temp = calloc(strlen(string) + 1 + 1042, sizeof(char));
    char *temp2 = calloc(strlen(string) + 1 + 1042, sizeof(char));

    while(*(string+c)!='\0')
    {
        if(string[c] == '\n'|| string[c] == '\r')
        {
            h = c;
            while((string[h] == '\n'|| string[h] == '\r'))
            {
                j++;
                h++;
                
            }
            if(j>2)
            {
                strcat(temp,"<P>");
                j = 0;
            } 
            else if (j==1)
            {   
                strcat(temp,"<BR>");
                j = 0;
            }
            
        }
        else
        {
            temp2[0] = string[c];
            strcat(temp,temp2);
        }

        c++;
    }
    if(temp2 != NULL)
    {
        free(temp2);
    }

    if(string != NULL)
    {
        free(string);
    }
    return(temp);
}
//start with the header and then move down, you got to disassemble the struct
//during this process, and remember to start with the head of the struct. 
//start this off as a print statment and then use fwrite.
int freeStructure(struct dataHeader *header)
{
  struct dataString *temp;
     struct dataString *next;

    if(header == NULL)
    {
        return 1;
    }

     temp = header->next;

     while(temp!= NULL)
     {
         free(temp->string);
         next = temp->next;
         free(temp);
         temp = next;
     }

     free(header->name);
     free(header);
 
    return 1;
 }



int freeSecondStruct(struct returnStruct * header)
{
	//free(header->header);
	free(header);
	return(1);
}
