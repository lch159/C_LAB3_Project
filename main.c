#include<stdio.h>
#include<dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include "md5.c"

//11611423李晨昊
//11611410郑笑典
//小组lab

struct file_info
{
    int file_num;
    int file_size;
    int flag;
    char file_name[40];
    char file_path[1024];
    char file_md5[40];
    };

int file_index=0;
struct file_info file[300000];

//Use recursion to traverse a path to find all files
int dir(char *s)
{
    DIR *dirptr=NULL;
    struct dirent *entry;
    struct stat buf;
    char path[5000];

    if((dirptr = opendir(s))==NULL)
    {
        printf("Open file failed!");
        return 1;
    }
    else {
        while((entry = readdir(dirptr))) {
            if(!strcmp(entry->d_name,".")||!strcmp(entry->d_name,".."))
                continue;

            sprintf(path,"%s/%s",s,entry->d_name);
            if (stat(path, &buf) < 0) {
                printf("Cannot access%s Errno code:%d\n\n",entry->d_name,errno);
            }else if (!S_ISDIR(buf.st_mode)){
                file[file_index].flag=1;
                file[file_index].file_num = file_index;
                file[file_index].file_size = buf.st_size;
                sprintf(file[file_index].file_name,entry->d_name);
                sprintf(file[file_index].file_path,path);
                printf("No.%d %s\tThe file size is: %d byte\tThe path is: %s\n",
                       file_index,file[file_index].file_name,file[file_index].file_size,file[file_index].file_path);
                sprintf(file[file_index].file_md5,getmd5(path));
                file_index++;
            } else {
                    dir(path);
            }
        }
        closedir(dirptr);
    }
    return 0;
}
//find the identical files
int judge(char *s)
{
    for(int i =0;i<file_index-1;i++)
    {
        for(int j = i+1;j<file_index;j++)
        {
             if(strcmp(file[i].file_md5,file[j].file_md5)==0&&file[i].flag!=0)
            {
                printf("\n%s\t%s\n",file[i].file_path+strlen(s)+1,file[j].file_path+strlen(s)+1);
                file[j].flag=0;
            }
        }
    }
    return 0;
}

int main(char argc, char *argv[])
{
    char *s =argv[1];
    dir(s);
    printf("\n");
    printf("\nTotal files:%d\n", file_index );
    judge(s);
    return 0;
}
