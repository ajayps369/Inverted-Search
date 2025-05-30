#include"is.h"

int save(m_node*hash[],char *input_file)
{
    FILE*fp=fopen(input_file,"w");
    if(fp==NULL)
    {
        printf("\nCREATED INPUT FILE \033[31m%s\033[0m FAILED\n",input_file);
        return 0;
    }
    for(int i=0;i<27;i++)
    {
        m_node*main_node=hash[i];
        if(main_node==NULL)
            continue;

        while(main_node!=NULL)
        {
            fprintf(fp,"#%d;%s;%d;",i,main_node->word,main_node->file_count);
            s_node*sub_node=main_node->sublink;
            while(sub_node!=NULL)
            {
                fprintf(fp,"%s;%d;",sub_node->f_name,sub_node->word_count);
                sub_node=sub_node->sublink;
            }
            fputc('#',fp);
            fputc('\n',fp);
            main_node=main_node->mainlink;
        }
    }
    fclose(fp);
    return SUCCESS;
}