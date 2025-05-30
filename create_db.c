#include"is.h"

int create_database(f_node*head1,m_node*head2[],s_node*head3,f_node**file_head)
{
    f_node*temp1=head1;
    while(temp1!=NULL)
    {
        f_node*f_temp=*file_head;
        int flag=0;
        while(f_temp!=NULL)
        {
            if(strcmp(f_temp->f_name,temp1->f_name)==0)
            {
                flag=1;
                break;
            }
            f_temp=f_temp->filelink;
        }
        if(flag==1)
        {
            temp1=temp1->filelink;
            continue;
        }
        create_file_list(file_head,temp1->f_name);
        //printf("%s is going to create...\n",temp1->f_name);
        FILE*fp=fopen(temp1->f_name,"r");
        if(fp==NULL)
        {
            printf("\nFAILED TO OPEN \033[31m%s\033[0m\n",temp1->f_name);
            temp1=temp1->filelink;
            continue;
        }
        char word[WORD_SIZE];
        while(fscanf(fp,"%s",word)!=EOF)
        {
            int index=tolower(word[0])-97;
            if(index<0 || index>25)
            {
                index=26;
            }

            if(head2[index]==NULL)
            {
                m_node*m_new=create_mainnode(word);
                s_node*s_new=create_subnode(temp1->f_name);
                m_new->sublink=s_new;
                head2[index]=m_new;
            }
            else
            {
                if(is_word_present(head2[index],word)==FAILURE)
                {
                    m_node*m_new=create_mainnode(word);
                    s_node*s_new=create_subnode(temp1->f_name);
                    m_new->sublink=s_new;
                    m_new->mainlink=head2[index];
                    head2[index]=m_new;
                }
                else
                {
                    m_node*temp2=head2[index];
                    while(temp2!=NULL)
                    {
                        if(strcmp(temp2->word,word)==0)
                        {
                            if(is_file_name_match(temp2->sublink,temp1->f_name)==SUCCESS)
                            {
                                s_node*temp3=temp2->sublink;
                                while(temp3!=NULL)
                                {
                                    if(strcmp(temp3->f_name,temp1->f_name)==0)
                                    {
                                        temp3->word_count++;
                                        break;
                                    }
                                    temp3=temp3->sublink;
                                }
                            }
                            else
                            {
                                s_node*s_new=create_subnode(temp1->f_name);
                                s_new->sublink=temp2->sublink;
                                temp2->sublink=s_new;
                                temp2->file_count++;
                            }
                            break;
                        }
                        temp2=temp2->mainlink;
                    }
                }
            }
        }
        fclose(fp);
        temp1=temp1->filelink;
    }
    return SUCCESS;
}

m_node*create_mainnode(char *word)
{
    m_node*new_main=malloc(sizeof(m_node));
    if(new_main==NULL)
    {
        printf("\nFAILED TO CREATE NEW MAIN NODE\n");
        return NULL;
    }
    strcpy(new_main->word,word);
    new_main->mainlink=NULL;
    new_main->file_count=1;
    new_main->sublink=NULL;
    return new_main;
}

s_node*create_subnode(char *file_name)
{
    s_node*new_sub=malloc(sizeof(s_node));
    if(new_sub==NULL)
    {
        printf("\nFAILED TO CREATE NEW SUB NODE\n");
        return NULL;
    }
    strcpy(new_sub->f_name,file_name);
    new_sub->sublink=NULL;
    new_sub->word_count=1;
    return new_sub;
}

int is_word_present(m_node*head2,char*word)
{
    m_node*temp=head2;
    while(temp!=NULL)
    {
        if(strcmp(temp->word,word)==0)
        {
            return SUCCESS;
        }
        temp=temp->mainlink;
    }
    return FAILURE;
}

int is_file_name_match(s_node*head3,char*file_name)
{
    s_node*temp=head3;
    while(temp!=NULL)
    {
        if(strcmp(temp->f_name,file_name)==0)
        {
            return SUCCESS;
        }
        temp=temp->sublink;
    }
    return FAILURE;
}
