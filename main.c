#include"is.h"

int main(int argc,char*argv[])
{       
    m_node*hash[27]={NULL};
    s_node*sub_head=NULL;
    f_node*file_head=NULL;  
    if(argc==1)
    {
        printf("\nINSUFFICIENT ARGUIMENTS\n");
        return 0;
    }   
    f_node*head=NULL;
    if(read_and_validation(&head,argv)==FAILURE)
    {
        printf("\n\033[31mREAD AND VALIDATION ERROR\033[0m\n");
        return 0;
    }
    printf("\nFILES STORED IN THE LIST ARE");
    print_list(&head);

    int choice;
    char ch;
    char input_word[WORD_SIZE];
    char input_file[FNAME_SIZE];
    do
    {
        printf("\n======================\n\tMENU\n======================\n");
        printf("1.CREATE DATABASE\n2.DISPLAY DATABASE\n3.SEARCH DATABASE\n4.SAVE DATABASE\n5.UPDATE DATABASE\nENTER YOUR CHOICE:");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
            if(create_database(head,hash,sub_head,&file_head)==FAILURE)
            {
                printf("\nDATABASE FAILED TO CREATE\n");
            }
            printf("\nDATABASE CREATED SUCCESS\n");
            break;
            case 2:
            display_hash_table(hash);
            break;
            case 3:
            printf("\nENTER THE WORD THAT YOU WANT TO SEARCH : ");
            scanf("%s",input_word);
            if(search_word(hash,input_word)==SUCCESS)
            {
                printf("\nWORD FOUND SUCCESS\n");
            }
            else
            {
                printf("\nWORD \033[31m%s\033[0m NOT FOUND IN THE DATABASE\n",input_word);
            }
            break;
            case 4:
            printf("\nENTER THE FILENAME YOU WANT TO SAVE :");
            scanf("%s",input_file);
            if(check_file_extn(input_file)==FAILURE)
            {
                //printf("\n\033[31m%s\033[0m IS NOT A TEXT FILE\n",input_file);
                return 0;
            }
            if(save(hash,input_file)==FAILURE)
            {
                printf("\nSAVE DATA TO \033[31m%s\033[0m FILE FAILED\n",input_file);
            }
            printf("\nSAVED DATA TO \033[32m%s\033[0m FILE SUCCESS\n",input_file);
            break;
            case 5:
            if(update(hash,&file_head)==FAILURE)
            {
                printf("\nUPDATE FAILED\n");
            }
            else
            {
                printf("\nUPDATE TO DATA BASE SUCCESS\n");
            }
            break;
            default:printf("\nINVALID CHOICE\n");
        }
        printf("\nDO YOU WANT TO CONTINUE (Y/N):");
        scanf(" %c",&ch);
    }
    while(ch=='y' || ch=='Y');
}