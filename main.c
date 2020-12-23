#include <stdio.h>
#include <stdlib.h>
#include "process.h"
#include "filelist.h"

static void print_process_pid(int pid);

int main(int argc, char* argv[])
{
    int pid = 0;
    if(argc != 2 || (pid = atoi(argv[1]) == 0))
    {
        printf("Usage: %s <PID>\n", argv[0]);
        return EXIT_FAILURE;
    }

    pid = atoi(argv[1]);
    print_process_pid(pid);
    return EXIT_SUCCESS;
}

static void print_process_pid(int pid)
{
    process_t* process = create_process(pid);
    if(process == NULL)
    {
        return;
    }

    printf("PID: %d  FILE: %s\n", get_process_id(process), get_process_name(process));
    printf("open file list:\n");

    file_list_node_t* filenode = get_process_open_file_list(process);
    while(filenode != NULL)
    {
        const char* file = get_file_list_node_name(filenode);
        if(file[0] == '/')
        {
            printf("\t%s\n", file);
        }
        filenode = get_next_file_list_node(filenode);
    }
    
    delete_process(process);
}