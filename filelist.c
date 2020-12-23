#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include "filelist.h"

struct file_list_node_t
{
    file_list_node_t* prev;
    file_list_node_t* next;
    char file[PATH_MAX + 1];
};

file_list_node_t* create_empty_file_list_node(void)
{
    file_list_node_t* node = (file_list_node_t*)malloc(sizeof(file_list_node_t));
    if(node == NULL)
    {
        fprintf(stderr, "error: %s\n", strerror(errno));
    }
    
    return node;
}

file_list_node_t* create_file_list_node(const char* file, file_list_node_t* prev, file_list_node_t* next)
{
    assert(file != NULL);

    file_list_node_t* node = (file_list_node_t*)malloc(sizeof(file_list_node_t));
    if(node == NULL)
    {
        fprintf(stderr, "error: %s\n", strerror(errno));
        return node;
    }

    strncpy(node->file, file, PATH_MAX);
    node->prev = prev;
    node->next = next;
    if(prev != NULL)
    {
        prev->next = node;
    }
    if(next != NULL)
    {
        next->prev = node;
    }

    return node;
}

void delete_file_list_node(file_list_node_t* node)
{
    assert(node != NULL);
    
    file_list_node_t* prev = node->prev;
    file_list_node_t* next = node->next;
    if(prev != NULL)
    {
        prev->next = next;
    }

    if(next != NULL)
    {
        next->prev = prev;
    }

    free((void*)node);
}

file_list_node_t* get_prev_file_list_node(file_list_node_t* node)
{
    assert(node != NULL);

    return node->prev;
}

file_list_node_t* get_next_file_list_node(file_list_node_t* node)
{
    assert(node != NULL);

    return node->next;
}

const char* get_file_list_node_name(file_list_node_t* node)
{
    assert(node != NULL);

    return node->file;
}

void set_prev_file_list_node(file_list_node_t* node, file_list_node_t* prev)
{
    assert(node != NULL);

    node->prev = prev;
}

void set_next_file_list_node(file_list_node_t* node, file_list_node_t* next)
{
    assert(node != NULL);

    node->next = next;
}

void set_file_list_node_name(file_list_node_t* node, const char* file)
{
    assert(node != NULL);

    strncpy(node->file, file, PATH_MAX);
}