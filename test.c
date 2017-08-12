#include<stdio.h>
#include<dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
struct file_info
{
    int file_num;
    int file_size;
    char *file_name;
    char *file_path;
//    char file_md5[32];
    char *file_type;
};


int main(char argc,char *argv[])
{
//    dir(argv[1]);
    DIR *dirptr=NULL;
    int file_index=0;
    struct dirent *entry;
    struct stat buf;
    struct file_info file[1024];

    char *usepath=argv[1];

    if((dirptr = opendir(argv[1]))==NULL)
    {
        printf("opendir failed!");
        return 1;
    }
    else
    {
        while((entry = readdir(dirptr))) {

            if (stat(entry->d_name, &buf) == 0) {
//            chmod(entry->d_name, S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IWGRP|S_IXGRP|S_IROTH|S_IWOTH|S_IXOTH);
                if (!S_ISDIR(buf.st_mode)) {
                    printf("第 %d 个文件\t文件大小为 %d \t文件名为 %s \t \t文件后缀为 %s \t", file_index, buf.st_size, entry->d_name,
                           strrchr(entry->d_name, '.'));
                    file[file_index].file_num = file_index;
                    file[file_index].file_size = buf.st_size;
                    file[file_index].file_name = (entry->d_name);
                    file[file_index].file_path = argv[1];
                    file[file_index].file_type = strrchr(entry->d_name, '.');
                    printf("是文件");
                    file_index++;
                } else {
                    printf("%s是目录", entry->d_name);
                }
                if (access(entry->d_name, R_OK) == 0)
                    printf("READ OK ");
                else
                    printf("can't read ");
                if (access(entry->d_name, W_OK) == 0)
                    printf("WRITE OK ");
                else
                    printf("can't write ");
                if (access(entry->d_name, X_OK) == 0)
                    printf("EXEC OK ");
                else
                    printf("can't exec ");
                if (access(entry->d_name, F_OK) == 0)
                    printf("File exist ");
                else
                    printf("don't exist ");
                printf("\n");
                printf("\n");
            } else
                printf("无法访问%s\n",entry->d_name);
        }

        printf(file[0].file_path);
        printf("目录下总共%d个文件", file_index );
        closedir(dirptr);
    }
    return 0;
}


