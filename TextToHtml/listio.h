#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

struct dataHeader{
    char* name;
    int length;
    struct dataString * next;
};
struct dataString{
	char *string;
	struct dataString *next;
};
struct returnStruct{
	int value;
	struct dataHeader *header;
};
struct returnStruct *buildHeader();
int setName(struct dataHeader *header, char *name);
char *getName(struct dataHeader *header);
int getLength(struct dataHeader *header);
int addString(struct dataHeader *header, char *str);
int printString(struct dataHeader *header);
int processStrings(struct dataHeader *header);
int freeStructure(struct dataHeader *header);
char *spaceTab(char *string);
char *lineBreakCarriage(char *string);
int writeStrings(char *filename, struct dataHeader *header);
struct dataHeader *readStrings(char *filename);
int freeSecondStruct(struct returnStruct * header);
