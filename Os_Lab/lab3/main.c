#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>   
#include <time.h>        

int main(int argc, char *argv[]) {
    if (argc < 3) return 1;
    if (strcmp(argv[1], "-c") == 0 && argc == 4) createFileWithPermission(argv[2], strtol(argv[3], NULL, 8));
    else if (strcmp(argv[1], "-t") == 0 && argc == 4) {
        int result = checkFile(argv[2], strtol(argv[3], NULL, 8));
        if (result== -1) printf("Yes\n");
	else {
	       	printf("No\n");
		printf("%o",result);
	}
    } 
    else if (strcmp(argv[1], "-s") == 0 && argc == 3) {
        struct mystruct info = showFileInfo(argv[2]);
        printf("%u\n", info.userID);
        printf("%s", ctime(&info.modifyTime));
        printf("%lld\n", (long long)info.fileSize);  
    } 
    else if (strcmp(argv[1], "-m") == 0 && argc == 7) createFileList(argv[2], argv[3], argv[4], atoi(argv[5]), atoi(argv[6])); 
    else return 1;
}


