#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <unistd.h>
#include <dirent.h>
#include "filelist.h"
#include "process.h"

struct process_t
{
    int pid;
    char file[PATH_MAX+1];
    file_list_node_t* open_file_list;
};

process_t* create_process(int pid)
{
    /* 创建结构 */
    process_t* process = (process_t*)malloc(sizeof(process_t));
    if(process == NULL)
    {
        fprintf(stderr, "error: %s\n", strerror(errno));
        return process;
    }
    process->pid = pid;

    /* 读取进程可执行文件的路径 */
    char exe_link_path[PATH_MAX+1];
    snprintf(exe_link_path, PATH_MAX, "/proc/%d/exe", pid);
    ssize_t len = readlink(exe_link_path, process->file, PATH_MAX);
    if(len < 0)
    {
        fprintf(stderr, "error: %s\n", strerror(errno));
        return NULL;
    }
    process->file[len] = 0;

    /* 读取进程打开的文件的路径 */
    char fd_dir_path[PATH_MAX+1];
    snprintf(fd_dir_path, PATH_MAX, "/proc/%d/fd", pid);
    DIR* dir = opendir(fd_dir_path);
    struct dirent* node = NULL;
    while((node = readdir(dir)) != NULL)
    {
        char fd_file_path[PATH_MAX+1];
        snprintf(fd_file_path, PATH_MAX, "/proc/%d/fd/%s", pid, node->d_name);
        char open_file[PATH_MAX+1];
        ssize_t len = readlink(fd_file_path, open_file, PATH_MAX);
        if(len < 0)
        {
            continue;
        }
        open_file[len] = 0;
        file_list_node_t* filenode = create_file_list_node(open_file, NULL, process->open_file_list);
        if(filenode != NULL)
        {
            process->open_file_list = filenode;
        }
        
    }
    closedir(dir);

    return process;
}

void delete_process(process_t* process)
{
    assert(process != NULL);

    file_list_node_t* filenode = process->open_file_list;
    while(filenode != NULL)
    {
        file_list_node_t* temp = filenode;
        filenode = get_next_file_list_node(filenode);
        delete_file_list_node(temp);
    }

    free(process);
}

int get_process_id(process_t* process)
{
    assert(process != NULL);

    return process->pid;
}

const char* get_process_name(process_t* process)
{
    assert(process != NULL);

    return process->file;
}

file_list_node_t* get_process_open_file_list(process_t* process)
{
    assert(process != NULL);

    return process->open_file_list;
}