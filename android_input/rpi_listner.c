#include <stdio.h>
#include <string.h>

void readFile();

int main(int argc, char const *argv[])
{
	while(1){
		readFile();
	}
	
}

char *text = "";

void readFile(){
	char *cmd = "adb shell cat /storage/sdcard0/DCIM/test";
	FILE *fp = popen(cmd, "r");
	char *ln = NULL;
	size_t len = 0;

	while (getline(&ln, &len, fp) != -1){
		
		if (strcmp(text,ln) != 0 )
		{
			text = malloc(strlen(ln) + 1);
			strcpy(text, ln);
			printf("%s\n", text);
		}

	}
	free(ln);
	pclose(fp);
}