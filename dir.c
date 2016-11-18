#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
void del_dir(char *npath);
int main()
{
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;
	char path[20] = {0};
	strcpy(path,"./abc");
	if ((dp = opendir(path)) == NULL){
		printf("opendir faild.....\n");
		exit(1);
	}
	chdir(path);
	while((entry = readdir(dp)) != NULL){
		lstat(entry->d_name,&statbuf);
		if(strcmp(".",entry->d_name) == 0 ||
				strcmp("..",entry->d_name) == 0)
			continue;
		if(S_ISDIR(statbuf.st_mode)){
			 del_dir(entry->d_name);
			 rmdir(entry->d_name);
		}
	}
	return 0;
}


void del_dir(char *npath)
{
	char pathname[256]={'\0'};
	struct dirent *ent =NULL;
	struct stat statbuf;
	DIR * ptr;
	DIR *dpin;
	if ((ptr = opendir(npath)) == NULL){
		printf("cannot open del_dir_directory:%s",npath);
		return ;	
	}
	while((ent = readdir(ptr)) != NULL)
	{

		printf("ent->d_name:%s",ent->d_name);
		if(strcmp(ent->d_name,".")==0||strcmp(ent->d_name,"..")==0)
			continue;

		lstat(ent->d_name,&statbuf);

		strcpy(pathname,npath);
		strcat(pathname,"/");
		strcat(pathname,ent->d_name);
		if(!S_ISDIR(statbuf.st_mode))
		{
			remove(pathname);
		}else{
			del_dir(pathname);
			remove(pathname);

		}
		if(rmdir(npath) == 0){
			printf("this is file dir del................. :%s",npath);
		}
	}
}
