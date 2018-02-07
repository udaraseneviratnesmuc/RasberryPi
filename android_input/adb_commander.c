// ./adb_commander "adb shell 'cd acct; pwd;ls'"

#include<stdio.h>

int main(int argc, char const *argv[]){
	FILE *fp = popen(argv[1], "r");
	char *ln = NULL;
	size_t len = 0;

	while (getline(&ln, &len, fp) != -1)
	    fputs(ln, stdout);
	free(ln);
	pclose(fp);
}