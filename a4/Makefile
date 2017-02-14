all: liblist a4.o a4 db.o db Perm output.o output filecontents.o filecontents

liblist: a4.o
	ar cr liblistio.a a4.o 
a4.o: 
	gcc listio.c -o a4.o -c
a4: a4.c
	gcc a4.c -g -o a4 -llistio -L. -lmysqlclient -L/usr/lib/x86_64-linux-gnu/

db: db.o
	gcc db.o -o db -lmysqlclient -L/usr/lib/x86_64-linux-gnu/

db.o: db.c
	gcc db.c -g -o db.o -c 

output: output.o
	gcc output.o -o output -lmysqlclient -L/usr/lib/x86_64-linux-gnu/

output.o: output.c
	gcc output.c -g -o output.o -c 	

filecontents: filecontents.o
	gcc filecontents.o -o filecontents -lmysqlclient -L/usr/lib/x86_64-linux-gnu/

filecontents.o:
	gcc filecontents.c -g -o filecontents.o -c 	

Perm:
	chmod 777 files a4 a4.py 


clean:
	rm a4.o liblistio.a a4 db db.o output output.o filecontents filecontents.o