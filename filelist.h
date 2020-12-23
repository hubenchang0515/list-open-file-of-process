#ifndef MY_LSOF_FILE_LIST_H
#define MY_LSOF_FILE_LIST_H

typedef struct file_list_node_t file_list_node_t;

file_list_node_t* create_empty_file_list_node(void);
file_list_node_t* create_file_list_node(const char* file, file_list_node_t* prev, file_list_node_t* next);
void delete_file_list_node(file_list_node_t* node);
file_list_node_t* get_prev_file_list_node(file_list_node_t* node);
file_list_node_t* get_next_file_list_node(file_list_node_t* node);
const char* get_file_list_node_name(file_list_node_t* node);
void set_prev_file_list_node(file_list_node_t* node, file_list_node_t* prev);
void set_next_file_list_node(file_list_node_t* node, file_list_node_t* next);
void set_file_list_node_name(file_list_node_t* node, const char* file);

#endif