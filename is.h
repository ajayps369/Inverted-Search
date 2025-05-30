#ifndef IS_H
#define IS_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"ctype.h"
#include"is.h"

#define SUCCESS 0
#define FAILURE -1
#define DATA_NOT_FOUND -2
#define WORD_SIZE 20
#define FNAME_SIZE 10

typedef struct main_node
{
    char word[WORD_SIZE];
    int file_count;
    struct sub_node* sublink;
    struct main_node* mainlink;
}m_node;

typedef struct sub_node
{
    int word_count;
    char f_name[FNAME_SIZE];
    struct sub_node*sublink;
}s_node;

typedef struct file_node
{
    char f_name[FNAME_SIZE];
    struct file_node*filelink;
}f_node;

//validation
int read_and_validation(f_node**head,char*argv[]);
int check_file_extn(char *file_name);
int check_file_exist_and_empty(char *file_name);
int check_repetition(f_node**head,char *file_name);
int create_file_list(f_node**head,char *file_name);
int print_list(f_node**head);
//create data base
int create_database(f_node*head1,m_node*head2[],s_node*head3,f_node**file_head);
m_node*create_mainnode(char *word);
s_node*create_subnode(char *file_name);
int is_word_present(m_node*head2,char*word);
int is_file_name_match(s_node*head3,char*file_name);
//display
void display_hash_table(m_node*hash[]);
//search word
int search_word(m_node*hash[],char *word);
//save
int save(m_node*hash[],char *input_file);
//update
int update(m_node*hash[],f_node**file_head);
int check_backup(char*filename);
int check_file_list(f_node**file_head,char*file_nm);

#endif