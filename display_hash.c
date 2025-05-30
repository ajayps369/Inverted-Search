#include"is.h"

void display_hash_table(m_node*hash[])
{
    printf("=============================================================\n");
    printf("Index | Word        | File count | File Name    | Word count\n");
    printf("=============================================================\n");
    for(int i=0;i<27;i++)
    {
        m_node*main_node=hash[i];
        if(main_node==NULL)
            continue;

        printf("%d\t",i);
        int count1=0;
        while(main_node!=NULL)
        {
            count1++;
            if(count1==1)
            {
                printf("\033[36m%-10s\033[0m\t%-10d\t",main_node->word,main_node->file_count);
            }
            else
            {
                printf("\t\033[36m%-10s\033[0m\t%-10d\t",main_node->word,main_node->file_count);
            }
            s_node*sub_node=main_node->sublink;
            int count2=0;
            while(sub_node!=NULL)
            {
                count2++;
                if(count2==1)
                {
                    printf("\033[32m%-10s\033[0m\t%-10d\n",sub_node->f_name,sub_node->word_count);
                }  
                else
                {
                    printf("\t\t\t\t\t\033[32m%-10s\033[0m\t%-10d\n",sub_node->f_name,sub_node->word_count);
                }
                sub_node=sub_node->sublink;
            }
            main_node=main_node->mainlink;
        }
        printf("-------------------------------------------------------------\n");
    }
}