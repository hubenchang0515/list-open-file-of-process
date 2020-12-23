#ifndef MY_LSOF_PROCESS_H
#define MY_LSOF_PROCESS_H

#include "filelist.h"

typedef struct process_t process_t;

process_t* create_process(int pid);
void delete_process(process_t* process);
int get_process_id(process_t* process);
const char* get_process_name(process_t* process);
file_list_node_t* get_process_open_file_list(process_t* process);

#endif