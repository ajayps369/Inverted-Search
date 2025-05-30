#include"is.h"

int search_word(m_node*hash[],char *word)
{
    int index=tolower(word[0])-97;
    if(index<0 || index>25)
        index=26;

    m_node*main_node=hash[index];
    while(main_node!=NULL)
    {
        if(strcmp(main_node->word,word)==0)
        {
            printf("WORD \033[36m%s\033[0m FOUND IN THE DATABASE\nFILE COUNT : %d\n",word,main_node->file_count);
            s_node*sub_node=main_node->sublink;
            while(sub_node!=NULL)
            {
                printf("FILE NAME : \033[32m%s\033[0m\nWORD COUNT AT \033[32m%s\033[0m : %d\n",sub_node->f_name,sub_node->f_name,sub_node->word_count);
                sub_node=sub_node->sublink;
            }
            return SUCCESS;
        }
        main_node=main_node->mainlink;
    }
    return DATA_NOT_FOUND;
}