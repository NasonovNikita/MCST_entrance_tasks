//
// Created by nosokvkokose on 20.03.26.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>

// AI generated, I'm not typing this manually
char* get_permissions(const mode_t mode) {
    char* res = malloc(11 * sizeof(char));

    // Obj type
    if (S_ISDIR(mode))  res[0] = 'd';
    else if (S_ISLNK(mode)) res[0] = 'l';
    else res[0] = '-';

    // User access
    res[1] = (mode & S_IRUSR) ? 'r' : '-';
    res[2] = (mode & S_IWUSR) ? 'w' : '-';
    res[3] = (mode & S_IXUSR) ? 'x' : '-';

    // Group access
    res[4] = (mode & S_IRGRP) ? 'r' : '-';
    res[5] = (mode & S_IWGRP) ? 'w' : '-';
    res[6] = (mode & S_IXGRP) ? 'x' : '-';

    // Others access
    res[7] = (mode & S_IROTH) ? 'r' : '-';
    res[8] = (mode & S_IWOTH) ? 'w' : '-';
    res[9] = (mode & S_IXOTH) ? 'x' : '-';

    res[10] = '\0';

    return res;
}


int main(const int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 1;
    }

    struct stat file_stat;
    const char* file_path = argv[1];
    if (stat(file_path, &file_stat) == -1) {
        perror("stat");
        return 1;
    }

    if (S_ISDIR(file_stat.st_mode)) {
        printf("Directory: ");
    } else if (S_ISREG(file_stat.st_mode)) {
        printf("File: ");
    } else {
        printf("Other type of file:");
    }
    printf("%s\n", file_path);
    printf("Mode: %s\n", get_permissions(file_stat.st_mode));
    printf("Size: %ld bytes\n", file_stat.st_size);
    printf("UID: %d\n", file_stat.st_uid);
    printf("Blocks: %ld\n", file_stat.st_blocks);
    printf("Block size: %ld\n", file_stat.st_blksize);
    printf("Last change: %s", ctime(&file_stat.st_ctime));
    printf("Last access: %s", ctime(&file_stat.st_atime));


    return 0;
}
