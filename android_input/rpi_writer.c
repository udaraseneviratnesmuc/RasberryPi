// ./adb_commander "adb shell 'cd acct; pwd;ls'"

#include<stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]){
	char * cmd;
	cmd = malloc(sizeof(char)*200);

	strcat(cmd, "adb shell echo '");
	strcat(cmd, argv[1]);
	strcat(cmd, "> /storage/sdcard0/DCIM/test'");

	system(cmd);
}