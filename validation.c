#include"is.h"

int read_and_validation(f_node**head,char*argv[])
{
    for(int i=1;argv[i]!=NULL;i++)
    {
        if(check_file_extn(argv[i])==SUCCESS)
        {
            printf("\nEXTENTION OF FILE \033[32m%s\033[0m SUCCESS\n",argv[i]);
            if(check_file_exist_and_empty(argv[i])==SUCCESS)
            {
                printf("\n\033[32m%s\033[0m IS A VALID FILE\n",argv[i]);
                if(check_repetition(head,argv[i])==SUCCESS)
                {
                    printf("\nREPETETION OF \033[32m%s\033[0m FILE NOT EXIST\n",argv[i]);
                    if(create_file_list(head,argv[i])==SUCCESS)
                    {
                        printf("\n\033[32m%s\033[0m STORED TO THE FILE LIST\n",argv[i]);
                    }
                }
            }
        }       
    }
    printf("\nREAD AND VALIDATION SUCCESS\n");
    return SUCCESS;
}

int check_file_extn(char *file_name)
{
    char *str=strchr(file_name,'.');
    if(strcmp(str,".txt")!=0)
    {
        printf("\n\033[31m%s\033[0m IS NOT A TEXT FILE\n",file_name);
        return FAILURE;
    }
    return SUCCESS;
}

int check_file_exist_and_empty(char *file_name)
{
    FILE*fp=fopen(file_name,"r");
    if(fp==NULL)
    {
        printf("\n\033[31m%s\033[0m IS NOT EXIST IN THIS SYSTEM\n",file_name);
        return FAILURE;
    }
    fseek(fp,0,SEEK_END);
    if(ftell(fp)==0)
    {
        fclose(fp);
        printf("\n\033[31m%s\033[0m IS AN EMPTY FILE\n",file_name);
        return FAILURE;
    }
    fclose(fp);
    return SUCCESS;
}

int check_repetition(f_node**head,char *file_name)
{
    f_node *temp=(*head);
    while(temp!=NULL)
    {
        if(strcmp(temp->f_name,file_name)==0)
        {
            printf("\n\033[31m%s\033[0m FILE ALREADY EXIST\n",file_name);
            return FAILURE;
        }
        temp=temp->filelink;
    }
    return SUCCESS;
}

int create_file_list(f_node**head,char *file_name)
{
    f_node*new=malloc(sizeof(f_node));
    if(new==NULL)
    {
        printf("\nFAILED TO CREATE FILE LIST\n");
        return FAILURE;
    }
    strcpy(new->f_name,file_name);
    new->filelink=NULL;
    if(*head==NULL)
    {
        *head=new;
        return SUCCESS;
    }
    f_node*temp=*head;
    while(temp->filelink!=NULL)
    {
        temp=temp->filelink;
    }
    temp->filelink=new;
    return SUCCESS;
}

int print_list(f_node**head)
{
    if(*head==NULL)
    {
        return FAILURE;
    }
    f_node*temp=*head;
    while(temp!=NULL)
    {
        printf(" -> \033[32m%s\033[0m",temp->f_name);
        temp=temp->filelink;
    }
    printf("\n");
    return SUCCESS;
}