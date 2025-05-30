#include"is.h"

int update(m_node*hash[],f_node**file_head)
{
    int flag=1;
    for(int i=0;i<27;i++)
    {
        if(hash[i]!=NULL)
        {
            flag=0;
            break;
        }
    }
    if(flag==0)
    {
        printf("\nDATABASE IS FULL\n");
        return FAILURE;
    }
    char filename[FNAME_SIZE];
    printf("\nENTER THE FILE NAME:");
    scanf("%s",filename);
    if(check_file_extn(filename)==FAILURE)
    {
        //printf("\n\033[31m%s\033[0m EXTENSION IS NOT A TEXT FILE\n",filename);
        return FAILURE;
    }
    printf("\n\033[32m%s\033[0m IS A TEXT FILE\n",filename);
    if(check_backup(filename)==FAILURE)
    {
        printf("\nBACKUP FILE FAILED\n");
        return FAILURE;
    }
    printf("\n\033[32m%s\033[0m IS A VALID BACKUP FILE\n",filename);
    printf("\nUPDATING TO DATABASE START\n");
    FILE*fp=fopen(filename,"r");
    if(fp==NULL)
    {
        printf("\nFAILED TO OPEN FILE FOR UPDATE\n");
        return FAILURE;
    }
    char line[100];
    while(fscanf(fp,"%s",line)!=EOF)
    {
        m_node*main_node=malloc(sizeof(m_node));
        if(main_node==NULL)
        {
            printf("\nFAILED TO CREATE MAIN NODE FOR UPDATEING\n");
            fclose(fp);
            return FAILURE;
        }
        main_node->mainlink=NULL;
        main_node->sublink=NULL;
        //index
        char *token=strtok(line,"#;");
        int index=atoi(token);
        //word
        token=strtok(NULL,"#;");
        strcpy(main_node->word,token);
        //file count
        token=strtok(NULL,"#;");
        main_node->file_count=atoi(token);

        s_node*s_temp=NULL;
        for(int i=0;i<main_node->file_count;i++)
        {
            s_node*sub_node=malloc(sizeof(s_node));
            if(sub_node==NULL)
            {
                printf("\nFAILED TO CREATE SUB NODE FOR UPDATING\n");
                return FAILURE;
            }
            sub_node->sublink=NULL;
            //file name
            token=strtok(NULL,"#;");
            strcpy(sub_node->f_name,token);
            check_file_list(file_head,token);

            //word count
            token=strtok(NULL,"#;");
            sub_node->word_count=atoi(token);
            
            if(s_temp==NULL)
                main_node->sublink=sub_node;
            else
                s_temp->sublink=sub_node;
            s_temp=sub_node;
        }
        main_node->mainlink=hash[index];
        hash[index]=main_node;
    }
    fclose(fp);
    printf("\nDATABASE UPDATED SUCCESSFULL\n");
    return SUCCESS;
}

int check_backup(char*filename)
{
    FILE*fp=fopen(filename,"r");
    if(fp==NULL)
    {
        printf("\nBACKUP FILE OPEN FAILED\n");
        return FAILURE;
    }
    fseek(fp,0,SEEK_SET);
    char start=fgetc(fp);
    fseek(fp,-2,SEEK_END);
    char end=fgetc(fp);
    if(start=='#' && end=='#')
    {
        fclose(fp);
        return SUCCESS;
    }
    fclose(fp);
    printf("\nBACKUP FILE IS NOT VALID\n");
    return FAILURE;
}

int check_file_list(f_node**file_head,char*file_nm)
{
    f_node*temp=*file_head;
    while(temp!=NULL)
    {
        if(strcmp(temp->f_name,file_nm)==0)
        {
            return SUCCESS;
        }
        temp=temp->filelink;
    }
    create_file_list(file_head,file_nm);
}