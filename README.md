README 

In order for this code to work, the user must compile the files simply by typing make on the terminal and then they can proceed to use the php files. This assignment will only work if there is a 'files' directory in the same directory as the a4 executable. 
Whoever is marking this assignment must create this directory.

Problems:
If there is an HTML file in the folder, and the user wants to add that same file to the server, my program will delete the HTML file from the directory. But it can be added back to the directory with another file conversion. 

Another issue with this program is, that the a4.c executable is made to only run with a4.php and not with the command line. When this program is through the terminal, it causes the program to segfault becuase it’s unable to grab the correct values from the command line arguments and it grabs garbage values which cause errors and the code to crash, this only when trying to convert the file from a no extension file to an html file this problem arises. This happens becuase the command line arguments are slightly different when the code being run from php compared to command line but when the  program is tested through the php server, it runs flawlessly with no issues.

When you update the database, the page MUST be refreshed to view the changes.
For some weird reason, sometimes when the user hits a file and goes back to the main page, an error page pops-up, but if the user-refreshes the page at the point, the original a4.php pops up.

This assignment has been tested on Google Chrome,Google Chrome Canary, and Safari and it works without any problems.

If there are any permission issues with the 'files' directory, this assignment will be unable to send files into that directory.

The following files are necessary for a successful run:
a4.c
a4.php
a4.py
listio.c
listio.h
Makefile
r2.jpg
output.c
db.c
filecontents.c
README.txt
upload.php
output.php
and a 'files' folder in the same directory 
