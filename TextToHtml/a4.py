#!/usr/bin/python

import os, sys

def filework(filename):

	title = filename
	infoFile = filename + ".info"
	with open(title,'r') as myfile:
		fileContents = myfile.readlines()	
	myfile.close()
	iExist = False
	if os.path.isfile(infoFile) == True:
		iExist = True

	header = "<HTML> <HEAD> <TITLE> " + title +" </TITLE> </HEAD> <BODY>"
	
	footer = "</BODY></HTML>"

	if iExist == True:
		with open(infoFile,'r') as myInfoFile:
			infoFileContents = myInfoFile.readlines()
		myInfoFile.close()

		for i in infoFileContents:
			i = i.strip()
			tag = i[0]
			i = i.replace(i[0],"",1)
			i = i.lstrip()
			
			infoFileLine = "<"+tag+">" +i+ "</"+tag+">"

			fileContents[0] = fileContents[0].replace(i,infoFileLine) 

	



	#write it to the HTML file in python
	newTitle = sys.argv[1] +".html"
	f = open(newTitle,'w')
	f.write(header + fileContents[0] + footer)



def main():
	filework(sys.argv[1])
if __name__== "__main__":
	main()
