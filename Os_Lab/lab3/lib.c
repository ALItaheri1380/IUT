#include "lib.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#include "lib.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

void createFileWithPermission(const char *path, int permission) {
    umask(0);	
    unlink(path);
    int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, permission);
    if (fd < 0) return;
    close(fd);
}

int checkFile(const char *path, int permission) {
    int count = 0;
    if (!access(path,R_OK)) count+=4;
    if (!access(path,W_OK)) count+=2;
    if (!access(path,X_OK)) count+=1;

    int check = ((count & permission) == permission);
    if (check) return -1;
    else return count;

}

struct mystruct showFileInfo(const char *path) {
    struct stat fileStat;
    struct mystruct info;
    if (stat(path, &fileStat) < 0) exit(EXIT_FAILURE);
    info.userID = fileStat.st_uid;
    info.modifyTime = fileStat.st_mtime;
    info.fileSize = fileStat.st_size;
    return info;
}

void createFileList(const char *dirPath, const char *prefix, const char *ext, int from, int to) {
    umask(0);
    char filePath[256];
    for (int i = from; i <= to; ++i) {
        snprintf(filePath, sizeof(filePath), "%s/%s_%d.%s", dirPath, prefix, i, ext);
        createFileWithPermission(filePath, 0755);
        printf("%s\n", filePath);
    }
}
