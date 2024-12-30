#ifndef LIB_H
#define LIB_H

#include <sys/types.h>  
#include <time.h>       

struct mystruct {
    uid_t userID;
    time_t modifyTime;
    off_t fileSize;
};

void createFileWithPermission(const char *path, int permission);
int checkFile(const char *path, int permission);
struct mystruct showFileInfo(const char *path);
void createFileList(const char *dirPath, const char *prefix, const char *ext, int from, int to);

#endif
