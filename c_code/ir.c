#include <stdio.h>
#include <dirent.h>
int main(int argc,const char *argv[])
{
	DIR *dp;
	struct dirent *entry;
	
	if((dp = opendir(argv[1])) == NULL) {
		printf("open faild\n");
		return;
	}
	chdir(argv[1]);
	while((entry = readdir(dp)) != NULL) {
		printf("name:%s\n",entry->d_name);
	}
	return 0;
}
