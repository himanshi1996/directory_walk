/*
	The code prints all the telephone numbers of the format +91-xxxxxxxxxx found 
	in the files under the directory entered by the user.The user must enter full
	path of the directory eg:"C:\\myprog\\test".
*/
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <iostream>
using namespace std;
#define DEBUG 1
//Function to check if the file_path point to a directory or not.Returns True if Yes.
int isDir(const char *file_path)
{
	struct stat s;
	stat(file_path, &s);
	return S_ISDIR(s.st_mode);
}
//Function to recursively walk a directory
void walkDir(char *basedir)
{
	DIR *dir;
	char b[512];
	struct dirent *ent;
	dir = opendir(basedir);
	if(dir != NULL)
	{
		while((ent = readdir(dir)) != NULL)
		{
			char entpath[] = "";
			strcat(entpath, basedir);
			strcat(entpath, "\\");
			strcat(entpath, ent->d_name);
			//Check if the entpath points to a directory.If yes, recursively call the function walkdir for the directory. 
			if(isDir(entpath))
				walkDir(entpath);
			else 
			{
				cout<<"File : "<<ent->d_name;
				FILE *f;
   				char buffer[13];
   				char *pattern = "+91-";
				f = fopen(ent->d_name, "r");
   				while (fgets(buffer, sizeof(buffer), f)) 
				   {
      				if (strstr(buffer, pattern)) 
      					cout<<"Telephone Number : "<<buffer<<endl;
      				
      			   }
      			fclose(f);
			}
		closedir(dir);
		}
	}
}
int main()
{
	char basedir[1001];
	cout<<"Enter Path : ";
	cin>>basedir;
	walkDir(basedir);
	return 0;
}
